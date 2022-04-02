#ifndef LIBOBUI_H
#define LIBOBUI_H

enum obui_event {
	OBUI_EVENT_NONE,
	OBUI_EVENT_MODE_SELECTED,
	OBUI_EVENT_QUICK_ACTION,
};

enum obui_press {
	OBUI_PRESS_NONE,
	OBUI_PRESS_SHORT,
	OBUI_PRESS_LONG,
};

enum obui_screen {
	OBUI_SCREEN_MENU,
	OBUI_SCREEN_INPUT,
	OBUI_SCREEN_STATUS,
};

struct obui_param {
	char *name, *unit;
	int64_t min, max, steps, value;
};

struct obui_mode {
	struct obui_param *param_list;
	size_t param_num;
};

struct obui_config {
	char *name, *version;

	uint16_t width_pixel, height_pixel;

	struct obui_mode *mode_list;
	size_t mode_num;
};

static struct obui_config *obui_config;
static struct obui_mode *obui_mode;
static enum obui_press volatile obui_press;
static enum obui_screen obui_screen;
static size_t obui_select_mode;
static size_t obui_select_param;
static int64_t obui_select_value;

static void
obui_screen_intro(void)
{
	obui_fn_clear_screen();
	obui_fn_draw_text_16px(0, 0, obui_config->name);
	obui_fn_draw_text_10px(0, 16, obui_config->version);
	obui_fn_flush_screen();
}

static void
obui_screen_menu(void)
{
	uint16_t pos_x = 0, bot_y;

	bot_y = config->height_pixel - 10;

	obui_fn_clear_screen();
	obui_fn_draw_text_10px(0, 0, obui_mode->name);
	for (size_t i = 0; i < config->mode_num; i++) {
		char *dot = ".";

		if (i == obui_screen_menu_selected)
			dot = "o";
		pos_x += obui_fn_draw_text_10px(pos_x, bot_y, dot) + 5;
	}
	obui_fn_flush_screen();
}

static void
obui_screen_input(void)
{
	;
}

static void
obui_init(struct obui_config *config)
{
	assert(config->name != NULL);
	assert(config->version != NULL);
	assert(config->width_pixel > 50);
	assert(config->height_pixel > 16 + 10);

	obui_config = config;
	obui_screen = OBUI_SCREEN_MENU;
}

static inline enum obui_event
obui_event_menu(enum obui_press press)
{
	switch (press) {
	case OBUI_PRESS_SHORT:
		if (++obui_select_mode > obui_config->mode_num)
			obui_select_mode = 0;
		obui_screen_mode();
		break;
	case OBUI_PRESS_LONG:
		obui_mode = &obui_config->mode_list[obui_select_mode];
		if (obui_mode->param_num > 0) {
			obui_screen = OBUI_SCREEN_INPUT;
			obui_param = &obui_mode->param_list[0];
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
obui_event_input(enum obui_press press)
{
	switch (press) {
	case OBUI_PRESS_SHORT:
		if ((obui_select_value += obui_param->step) > obui_param->max)
			obui_select_value = obui_param->min;
		break;
	case OBUI_PRESS_LONG:
		obui_param->value = obui_select_param;
		if (++obui_select_param > obui_mode->parm_num) {
			obui_screen = OBUI_SCREEN_STATUS;
			return OBUI_EVENT
		} else {
			obui_param = &obui_mode->param_list[obui_select_param];
			obui_select_value = obui_param->min;
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
		return OBUI_EVENT_QUICK_ACTION
	case OBUI_PRESS_LONG:
		obui_screen = OBUI_SCREEN_MENU;
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

	do {
		switch (obui_screen) {
		case OBUI_SCREEN_MENU:
			event = obui_event_menu(press);
			break;
		case OBUI_SCREEN_INPUT:
			event = obui_event_input(press);
			break;
		case OBUI_SCREEN_STATUS:
			event = obui_event_status(press);
			break;
		}
	} while (event == OBUI_EVENT_NONE);

	return event;
}

static inline void
obui_trigger_event(enum obui_press press)
{
	obui_press = press;
}

#endif
