#include "libc.h"
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
 * Current heat mode, selected from interrupt
 */
volatile enum mode {
	MODE_OFF,
	MODE_SMT_ACTIVATE, MODE_SMT_SOLDER, MODE_REWORK, MODE_REFLOW, MODE_MAX,
	MODE_END
} current_mode;
.
static void
set_mode(enum mode mode)
{
	switch (mode) {
	case MODE_OFF:
		pwm_set_duty_cycle(TC1_COUNT8, 0, PWM_OFF);
		break;
	case MODE_SMT_ACTIVATE:
		pwm_set_duty_cycle(TC1_COUNT8, 0, PWM_SMT_ACTIVATE_PASTE);
		break;
	case MODE_SMT_SOLDER:
		pwm_set_duty_cycle(TC1_COUNT8, 0, PWM_SMT_SOLDER_PASTE);
		break;
	case MODE_REWORK:
		pwm_set_duty_cycle(TC1_COUNT8, 0, PWM_OPTIMAL_FOR_REWORK);
		break;
	case MODE_REFLOW:
		pwm_set_duty_cycle(TC1_COUNT8, 0, PWM_OPTIMAL_FOR_REFLOW);
		break;
	case MODE_MAX:
		pwm_set_duty_cycle(TC1_COUNT8, 0, PWM_LIMIT_MAX);
		break;
	case MODE_END:
		pwm_set_duty_cycle(TC1_COUNT8, 0, PWM_OFF);
		assert(!"mode overflow");
	}
}

void
button_press_interrupt(void)
{
	current_mode++;
	if (current_mode == MODE_END)
		current_mode = MODE_OFF;
}

int
main(void)
{
	power_on_sercom(0);

	clock_init_generator(GCLK_GENCTRL_ID_GCLKGEN0, GCLK_GENCTRL_SRC_OSCULP32K, 1);
	clock_init(GCLK_CLKCTRL_ID_TC1_TC2, GCLK_GENCTRL_ID_GCLKGEN0);

	pwm_init(TC1_COUNT8, TC_COUNT8_CTRLA_PRESCALER_DIV64);
	pwm_init_counter(4);

	for (;;) {
		set_mode(MODE_REWORK);
	}

	return 0;
}
