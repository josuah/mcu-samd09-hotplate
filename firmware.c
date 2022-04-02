#include "libc.h"
#include "libobui.h"
#include "libdraw.h"
#include "font.h"
#include "registers.h"
#include "functions.h"

/*
 * All tests are done by letting the board heat during 5 min with
 * a thin foil of tin at the top.
 *
 * Tin melting temperature: 231.93 °C
 */

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
 * libobui config
 */
struct obui_param param_heat = {
	.name = "heat",
	.unit = "%",
	.min = 0,
	.max = 100,
	.step = 10,
};
struct obui_mode mode_stop = {
	.name = "Stop",
	.params = (struct obui_param *[]){
		NULL
	},
};
struct obui_mode mode_smt_activate = {
	.name = "SMT Activate Mode",
	.params = (struct obui_param *[]){
		NULL
	},
};
struct obui_mode mode_smt_solder = {
	.name = "SMT Solder Mode",
	.params = (struct obui_param *[]){
		NULL
	},
};
struct obui_mode mode_rework = {
	.name = "Rework Mode",
	.params = (struct obui_param *[]){
		NULL
	},
};
struct obui_mode mode_reflow = {
	.name = "Reflow Mode",
	.params = (struct obui_param *[]){
		NULL
	},
};
struct obui_mode mode_manual = {
	.name = "Manual Mode",
	.params = (struct obui_param *[]){
		&param_heat,
		NULL
	},
};
struct obui_config config = {
	.name = "HootPlate",
	.version = "v0.1",
	.main = &param_heat,
	.modes = (struct obui_mode *[]){
                &mode_stop, &mode_smt_activate, &mode_smt_solder,
                &mode_rework, &mode_manual,
		NULL
	},
};

uint16_t
obui_fn_draw_text_16px(uint16_t x, uint16_t y, char const *text)
{
	return draw_text(x, y, UINT16_MAX, &text, progmem_ascii_13);
}

int
main(void)
{
	power_on_sercom(0);

	clock_init_generator(GCLK_GENCTRL_ID_GCLKGEN0, GCLK_GENCTRL_SRC_OSCULP32K, 1);
	clock_init(GCLK_CLKCTRL_ID_TC1_TC2, GCLK_GENCTRL_ID_GCLKGEN0);

	systick_init(GCLK_GENCTRL_ID_GCLKGEN1);

	pwm_init(TC1_COUNT8, TC_COUNT8_CTRLA_PRESCALER_DIV64);
	pwm_init_counter(4);

	obui_init(&config);

	for (;;) {
		while (obui_get_event() == OBUI_EVENT_NONE);

		if (obui_mode == &mode_stop) {
			pwm_set_duty_cycle(TC1_COUNT8, 0,
			 PWM_OFF);
		} else if (obui_mode == &mode_smt_activate) {
			pwm_set_duty_cycle(TC1_COUNT8, 0,
			 PWM_SMT_ACTIVATE_PASTE);
		} else if (obui_mode == &mode_smt_solder) {
			pwm_set_duty_cycle(TC1_COUNT8, 0,
			 PWM_SMT_SOLDER_PASTE);
		} else if (obui_mode == &mode_rework) {
			pwm_set_duty_cycle(TC1_COUNT8, 0,
			 PWM_OPTIMAL_FOR_REWORK);
		} else if (obui_mode == &mode_reflow) {
			pwm_set_duty_cycle(TC1_COUNT8, 0,
			 PWM_OPTIMAL_FOR_REFLOW);
		} else if (obui_mode == &mode_manual) {
			pwm_set_duty_cycle(TC1_COUNT8, 0,
			 param_heat.value * PWM_LIMIT_MAX / param_heat.max);
		} else {
			pwm_set_duty_cycle(TC1_COUNT8, 0, PWM_OFF);
			assert(!"invalid mode!");
		}
	}
	return 0;
}
