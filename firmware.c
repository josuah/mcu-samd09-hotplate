#include "libc.h"
#include "registers.h"
#include "functions.h"

#include "libssd1306.h"
#include "libdraw.h"
#include "libobui.h"
#include "font.h"

#define I2C1_MASTER_SCL 23
#define I2C1_MASTER_SDA 22

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
	.long_press_ms = 500,
	.main = &param_heat,
	.modes = (struct obui_mode *[]){
		&mode_stop, &mode_smt_activate, &mode_smt_solder,
		&mode_rework, &mode_manual,
		NULL
	},
};

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

int
main(void)
{
	power_on_sercom(1);

	clock_init(GCLK_CLKCTRL_ID_SERCOM1_CORE, GCLK_GENCTRL_ID_GCLKGEN0);
	clock_init(GCLK_CLKCTRL_ID_SERCOMX_SLOW, GCLK_GENCTRL_ID_GCLKGEN1);

	i2c_master_init(I2C1_MASTER, 400000, I2C1_MASTER_SCL, I2C1_MASTER_SDA);
	ssd1306_init();
	obui_init(&config);
	ssd1306_flush();

	return 0;
}
