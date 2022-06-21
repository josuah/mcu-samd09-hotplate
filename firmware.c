#include "libc.h"
#include "libsamd09.h"
#include "libssd1306.h"
#include "libdraw.h"
#include "libobui.h"
#include "libutil.h"
#include "font.h"

#define PIN_I2C1_MASTER_SCL		23
#define PIN_I2C1_MASTER_SDA		22
#define PIN_BUTTON			15
#define PIN_PWM				4

/*
 * Let the plate cool down.
 */
#define PWM_OFF							0x00

/*
 * 1st phase of SMT soldering: activate the solder paste
 */
#define PWM_SMT_ACTIVATE_PASTE					0x18

/*
 * 2nd phase of SMT soldering: raise the temperature to solder
 */
#define PWM_SMT_SOLDER_PASTE					0x24

/*
 * Anything hotter than that might make the tin at the bottom of
 * the board melt without adding hot air.
 */
#define PWM_OPTIMAL_FOR_REWORK					0x20

/*
 * After a long time, the tin foil becomes in-between liquid and
 * solid, even when touching it with more tin, never forming a ball.
 */
#define PWM_LIMIT_TIN_MELTING					0x20

/*
 * The tin foil immediately changes its shape, but not to the point
 * of forming a ball on its own, although touching it with a tin wire
 * makes it become a melted tin shiny ball.
 */
#define PWM_LIMIT_TIN_FLOWING					0x26

/*
 * At this temperature, the tin foil becomes liquid forming a ball
 * on its own, without the need to touch it
 */
#define PWM_OPTIMAL_FOR_REFLOW					0x30

/*
 * At this temperature, the hot plate operates fine, no smoke appears,
 * no bad smell comes-up, the support or plastic do not over-heat.
 */
#define PWM_LIMIT_MAX						0x40	// TODO: untested

/*
 * libobui configuration
 */
static struct obui_param param_heat = {
	.name = "heat",
	.unit = "%",
	.min = 0,
	.max = 100,
	.step = 10,
};
static struct obui_mode mode_smt_activate = {
	.name = "SMT Activate Mode",
	.params = (struct obui_param *[]){
		NULL
	},
};
static struct obui_mode mode_smt_solder = {
	.name = "SMT Solder Mode",
	.params = (struct obui_param *[]){
		NULL
	},
};
static struct obui_mode mode_rework = {
	.name = "Rework Mode",
	.params = (struct obui_param *[]){
		NULL
	},
};
static struct obui_mode mode_reflow = {
	.name = "Reflow Mode",
	.params = (struct obui_param *[]){
		NULL
	},
};
static struct obui_mode mode_manual = {
	.name = "Manual Mode",
	.params = (struct obui_param *[]){
		&param_heat, NULL
	},
};
static struct obui_config config = {
	.name = "IsHotPlate",
	.version = "v0.1",
	.long_press_ms = 50,
	.main = &param_heat,
	.modes = (struct obui_mode *[]){
		&mode_smt_activate, &mode_smt_solder, &mode_rework,
		&mode_manual, NULL
	},
};

static uint8_t heat_paused;
static uint8_t heat_pwm;

uint16_t
obui_fn_draw_text(uint16_t x, uint16_t y, char const *text)
{
	return draw_text(x, y, UINT16_MAX, &text, progmem_font_13);
}

void
obui_fn_flush_screen(void)
{
	ssd1306_flush();
}

void
obui_fn_clear_screen(void)
{
	ssd1306_clear();
}

char *
obui_fn_fmtint(char *buf, size_t sz, int64_t num)
{
	return fmtint(buf, sz, num, 10);
}

int
ssd1306_fn_i2c_write(uint8_t addr, uint8_t const *buf, size_t sz)
{ 
	i2c_master_queue_tx(I2C1_MASTER, addr, buf, sz);
	return i2c_master_wait(I2C1_MASTER);
}

uint8_t
draw_fn_get_font_byte(uint8_t const *ptr)
{
	return *ptr;
}

void
draw_fn_point(uint16_t x, uint16_t y)
{
	ssd1306_draw_point(x, y);
}

static void
heat_set_value_pwm(uint8_t pwm)
{
	heat_pwm = pwm;
	param_heat.value = 100 * heat_pwm / PWM_LIMIT_MAX;
	pwm_set_duty_cycle(TC1_COUNT8, 0, heat_pwm);
}

static inline void
heat_update(void)
{
	uint8_t pwm;

	if (obui_mode == &mode_smt_activate) {
		pwm = PWM_SMT_ACTIVATE_PASTE;
	} else if (obui_mode == &mode_smt_solder) {
		pwm = PWM_SMT_SOLDER_PASTE;
	} else if (obui_mode == &mode_rework) {
		pwm = PWM_OPTIMAL_FOR_REWORK;
	} else if (obui_mode == &mode_reflow) {
		pwm = PWM_OPTIMAL_FOR_REFLOW;
	} else if (obui_mode == &mode_manual) {
		pwm = param_heat.value * PWM_LIMIT_MAX / param_heat.max;
	} else {
		assert(!"invalid mode!");
	}
	heat_set_value_pwm(pwm);
	heat_paused = 0;
}

static inline void
heat_play_pause(void)
{
	static int heat_last_pwm = 0;

	heat_paused = !heat_paused;
	if (heat_paused) {
		heat_last_pwm = heat_pwm;
		heat_set_value_pwm(0);
	} else {
		heat_pwm = heat_last_pwm;
		heat_set_value_pwm(heat_pwm);
	}
}

static inline void
button_init(void)
{
	PORT->DIRCLR = 1u << PIN_BUTTON;
	PORT->PINCFG[PIN_BUTTON] = PORT_PINCFG_INEN;
}

int
main(void)
{
	power_on_sercom(1);

	clock_init(GCLK_CLKCTRL_ID_SERCOM1_CORE, GCLK_GENCTRL_ID_GCLKGEN0);
	clock_init(GCLK_CLKCTRL_ID_SERCOMX_SLOW, GCLK_GENCTRL_ID_GCLKGEN2);
	clock_init(GCLK_CLKCTRL_ID_TC1_TC2, GCLK_GENCTRL_ID_GCLKGEN0);

	systick_init();
	i2c_master_init(I2C1_MASTER, 400000, PIN_I2C1_MASTER_SCL, PIN_I2C1_MASTER_SDA);
	ssd1306_init();
	obui_init(&config);
	pwm_init(TC1_COUNT8, TC_COUNT8_CTRLA_PRESCALER_DIV1024);
	pwm_init_counter(PIN_PWM);
	button_init();

	for (;;) {
		uint8_t button = (PORT->IN >> PIN_BUTTON) & 1;

		switch (obui_get_event(!button, systick_get_runtime_ms())) {
		case OBUI_EVENT_NONE:
			continue;
		case OBUI_EVENT_MODE_SELECTED:
			heat_update();
			break;
		case OBUI_EVENT_QUICK_ACTION:
			heat_play_pause();
			break;
		}
		obui_refresh_screen();
	}
	return 0;
}
