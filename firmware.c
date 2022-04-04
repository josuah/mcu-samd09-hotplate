#include "libc.h"
#include "registers.h"
#include "functions.h"

#include "libssd1306.h"
#include "libdraw.h"
#include "libobui.h"
#include "font.h"

#define I2C1_MASTER_SCL		23
#define I2C1_MASTER_SDA		22
#define BUTTON			15
#define PWM			4

/*
 * Let the plate cool down.
 */
#define PWM_OFF							0x00

/*
 * 1st phase of SMT soldering: activate the solder paste
 */
#define PWM_SMT_ACTIVATE_PASTE					0x00	// TODO: untested

/*
 * 2nd phase of SMT soldering: raise the temperature to solder
 */
#define PWM_SMT_SOLDER_PASTE					0x00	// TODO: untested

/*
 * Anything hotter than that might make the tin at the bottom of
 * the board melt without adding hot air.
 */
#define PWM_OPTIMAL_FOR_REWORK					0x15	// TODO: untested

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

static uint8_t heat_current_pwm;
static uint8_t heat_last_pwm;

uint16_t
obui_fn_draw_text_10px(uint16_t x, uint16_t y, char const *text)
{
	return draw_text(x, y, UINT16_MAX, &text, progmem_font_8);
}

uint16_t
obui_fn_draw_text_16px(uint16_t x, uint16_t y, char const *text)
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

void
obui_fn_fmtint(char *buf, size_t sz, uint64_t num)
{
	fmtint(buf, sz, num, 10);
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
	heat_current_pwm = pwm;
	param_heat.value = 100 * pwm / PWM_LIMIT_MAX;
	pwm_set_duty_cycle(TC1_COUNT8, 0, pwm);
}

static inline void
heat_update(void)
{
	if (obui_mode == &mode_smt_activate) {
		heat_set_value_pwm(PWM_SMT_ACTIVATE_PASTE);
	} else if (obui_mode == &mode_smt_solder) {
		heat_set_value_pwm(PWM_SMT_SOLDER_PASTE);
	} else if (obui_mode == &mode_rework) {
		heat_set_value_pwm(PWM_OPTIMAL_FOR_REWORK);
	} else if (obui_mode == &mode_reflow) {
		heat_set_value_pwm(PWM_OPTIMAL_FOR_REFLOW);
	} else if (obui_mode == &mode_manual) {
		heat_set_value_pwm(param_heat.value * PWM_LIMIT_MAX / param_heat.max);
	} else {
		heat_set_value_pwm(PWM_OFF);
		assert(!"invalid mode!");
	}
}

static inline void
heat_play_pause(void)
{
	heat_set_value_pwm(heat_current_pwm == 0 ? heat_last_pwm : 0);
}

static inline void
button_init(void)
{
	PORT->DIRCLR = 1u << BUTTON;
	PORT->PINCFG[BUTTON] = PORT_PINCFG_INEN;
}

int
main(void)
{
	power_on_sercom(1);

	clock_init(GCLK_CLKCTRL_ID_SERCOM1_CORE, GCLK_GENCTRL_ID_GCLKGEN0);
	clock_init(GCLK_CLKCTRL_ID_SERCOMX_SLOW, GCLK_GENCTRL_ID_GCLKGEN2);
	clock_init(GCLK_CLKCTRL_ID_TC1_TC2, GCLK_GENCTRL_ID_GCLKGEN0);

	systick_init();
	i2c_master_init(I2C1_MASTER, 400000, I2C1_MASTER_SCL, I2C1_MASTER_SDA);
	ssd1306_init();
	obui_init(&config);
	ssd1306_init();
	obui_init(&config);
	pwm_init(TC1_COUNT8, TC_COUNT8_CTRLA_PRESCALER_DIV64);
	pwm_init_counter(PWM);
	button_init();

	for (;;) {
		uint8_t button = (PORT->IN >> BUTTON) & 1;

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
	}
	return 0;
}
