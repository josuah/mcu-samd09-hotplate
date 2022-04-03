#ifndef LIBOBUI_H
#define LIBOBUI_H


enum obui_event {
	OBUI_EVENT_NONE,
	OBUI_EVENT_MODE_SELECTED,
	OBUI_EVENT_QUICK_ACTION,
};

enum obui_button {
	OBUI_BUTTON_RELEASED,
	OBUI_BUTTON_PRESSED,
};

struct obui_param {
	char const *name, *unit;
	uint64_t min, max, step, value;
};

struct obui_mode {
	char const *name;
	struct obui_param **params;
};

struct obui_config {
	uint16_t long_press_ms;
	char const *name, *version;
	struct obui_param *main;
	struct obui_mode **modes;
};

/* set to a function clearing the screen buffer */
extern void obui_fn_clear_screen(void);

/* set to a function flushing the screen buffer to the device */
extern void obui_fn_flush_screen(void);

/* set to a function formatting an integer `num` into a buffer `buf` of size `sz` */
extern void obui_fn_fmtint(char *buf, size_t sz, uint64_t num);

/* set to a function printing a text string with a 10px tall line */
extern uint16_t obui_fn_draw_text_10px(uint16_t x, uint16_t y, char const *text);

/* set to a function printing a text string with a 16px tall line */
extern uint16_t obui_fn_draw_text_16px(uint16_t x, uint16_t y, char const *text);

/* next event to be handled, after `obui_mode` and `obui_config` got updated */
static enum obui_event obui_get_event(void);

/* install `config` used by all obui functions and display the intro screen */
static void obui_init(struct obui_config *config);

/* call while a button was pressed to update obui's state machine */
static void obui_set_button_state(enum obui_button state, uint64_t time_ms);


/// POLICE LINE /// DO NOT CROSS ///


enum obui_press {
	OBUI_PRESS_NONE,
	OBUI_PRESS_SHORT,
	OBUI_PRESS_LONG,
};
enum obui_screen {
	OBUI_SCREEN_SELECT_MODE,
	OBUI_SCREEN_SELECT_VALUE,
	OBUI_SCREEN_STATUS,
};

static struct obui_config		*obui_config;
static struct obui_mode			*obui_mode;
static struct obui_param		*obui_param;
static enum obui_press volatile		 obui_press;
static enum obui_screen			 obui_screen;
static size_t				 obui_select_mode;
static size_t				 obui_select_param;
static uint64_t				 obui_select_value;

static inline void
obui_screen_intro(void)
{
	obui_fn_clear_screen();

	obui_fn_draw_text_16px(0, 0, obui_config->name);
	obui_fn_draw_text_10px(0, 16, obui_config->version);

	obui_fn_flush_screen();
}

static inline void
obui_screen_select_mode(void)
{
	uint16_t pos_x = 0;

	obui_fn_clear_screen();

	obui_fn_draw_text_16px(0, 0, obui_mode->name);
	for (size_t i = 0; obui_config->modes[i] != NULL; i++) {
		char const *dot;

		dot = (i == obui_select_mode) ? "." : "o";
		pos_x += obui_fn_draw_text_10px(pos_x, 16, dot) + 5;
	}

	obui_fn_flush_screen();
}

static inline void
obui_screen_select_value(void)
{
	char buf[50];
	uint16_t pos_x;

	obui_fn_clear_screen();

	pos_x = 0;
	pos_x += obui_fn_draw_text_10px(pos_x, 0, "set \"");
	pos_x += obui_fn_draw_text_10px(pos_x, 0, obui_param->name);
	pos_x += obui_fn_draw_text_10px(pos_x, 0, "\":");

	obui_fn_fmtint(buf, sizeof buf, obui_param->value);
	pos_x = 0;
	pos_x += obui_fn_draw_text_10px(pos_x, 0, buf);
	pos_x += obui_fn_draw_text_10px(pos_x, 0, obui_param->unit);

	obui_fn_flush_screen();
}

static inline void
obui_screen_status(void)
{
	char buf[50];
	uint16_t pos_x;

	obui_fn_clear_screen();

	pos_x = 0;
	pos_x += obui_fn_draw_text_10px(pos_x, 0, "set \"");
	pos_x += obui_fn_draw_text_10px(pos_x, 0, obui_param->name);
	pos_x += obui_fn_draw_text_10px(pos_x, 0, "\":");

	obui_fn_fmtint(buf, sizeof buf, obui_param->value);
	pos_x = 32;
	pos_x += obui_fn_draw_text_16px(pos_x, 0, buf);
	pos_x += obui_fn_draw_text_16px(pos_x, 0, obui_config->main->unit);

	obui_fn_flush_screen();
}

static void
obui_refresh_screen(void)
{
	switch (obui_screen) {
	case OBUI_SCREEN_SELECT_MODE:
		obui_screen_select_mode();
		break;
	case OBUI_SCREEN_SELECT_VALUE:
		obui_screen_select_value();
		break;
	case OBUI_SCREEN_STATUS:
		obui_screen_status();
		break;
	}
}

static inline enum obui_event
obui_event_select_mode(enum obui_press press)
{
	switch (press) {
	case OBUI_PRESS_SHORT:
		if (obui_config->modes[++obui_select_mode] == NULL)
			obui_select_mode = 0;
		break;
	case OBUI_PRESS_LONG:
		obui_mode = obui_config->modes[obui_select_mode];
		if (obui_mode->params[0] != NULL) {
			obui_screen = OBUI_SCREEN_SELECT_VALUE;
			obui_select_param = 0;
			obui_param = obui_mode->params[0];
		} else {
			obui_screen = OBUI_SCREEN_STATUS;
			return OBUI_EVENT_MODE_SELECTED;
		}
		break;
	case OBUI_PRESS_NONE:
		break;
	}
	return OBUI_EVENT_NONE;
}

static inline enum obui_event
obui_event_select_value(enum obui_press press)
{
	switch (press) {
	case OBUI_PRESS_SHORT:
		if ((obui_select_value += obui_param->step) > obui_param->max)
			obui_select_value = obui_param->min;
		break;
	case OBUI_PRESS_LONG:
		obui_param->value = obui_select_value;
		if (obui_mode->params[++obui_select_param] == NULL) {
			obui_param = obui_mode->params[obui_select_param];
			obui_select_value = obui_param->min;
		} else {
			obui_screen = OBUI_SCREEN_STATUS;
			return OBUI_EVENT_MODE_SELECTED;
		}
		break;
	case OBUI_PRESS_NONE:
		break;
	}
	return OBUI_EVENT_NONE;
}

static inline enum obui_event
obui_event_status(enum obui_press press)
{
	switch (press) {
	case OBUI_PRESS_SHORT:
		return OBUI_EVENT_QUICK_ACTION;
	case OBUI_PRESS_LONG:
		obui_screen = OBUI_SCREEN_SELECT_MODE;
		obui_select_mode = 0;
		break;
	case OBUI_PRESS_NONE:
		break;
	}
	return OBUI_EVENT_NONE;
}

static enum obui_event
obui_get_event(void)
{
	enum obui_event event;

	switch (obui_screen) {
	case OBUI_SCREEN_SELECT_MODE:
		event = obui_event_select_mode(obui_press);
		break;
	case OBUI_SCREEN_SELECT_VALUE:
		event = obui_event_select_value(obui_press);
		break;
	case OBUI_SCREEN_STATUS:
		event = obui_event_status(obui_press);
		break;
	}
	if (event != OBUI_EVENT_NONE)
		obui_refresh_screen();
	return event;
}

static void
obui_set_button_state(enum obui_button state, uint64_t time_ms)
{
	static uint64_t last_pressed_ms = 0;
	static enum obui_button last_state = OBUI_BUTTON_RELEASED;

	switch (state) {
	case OBUI_BUTTON_PRESSED:
		if (last_state == OBUI_BUTTON_PRESSED)
			return;
		last_pressed_ms = time_ms;
		break;
	case OBUI_BUTTON_RELEASED:
		if (last_state == OBUI_BUTTON_RELEASED)
			return;
		if (time_ms - last_pressed_ms >= obui_config->long_press_ms)
			obui_press = OBUI_PRESS_LONG;
		else
			obui_press = OBUI_PRESS_SHORT;
		break;
	}
	last_state = state;
}

static void
obui_init(struct obui_config *config)
{
	assert(config->name != NULL);
	assert(config->version != NULL);
	assert(config->modes[0] != NULL);
	assert(config->main != NULL);
	assert(config->long_press_ms > 0);

	PORT->DIRSET = 1u << 27;
	PORT->OUTSET = 1u << 27;

	obui_config = config;
	obui_mode = config->modes[0];
	obui_screen_intro();
}

#endif
