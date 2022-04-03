#ifndef LIBDRAW_H
#define LIBDRAW_H


/* set to a function printint one pixel at (`x`, `y`) */
extern void draw_fn_point(uint16_t x, uint16_t y);

/* set to a function that reads one byte at `ptr` from ROM */
extern uint8_t draw_fn_get_font_byte(uint8_t const *ptr);

/* draw a line between point (`x0`, `y0`) and (`x1`, `y1) */
static void draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

/* draw *`sp` with `font` at (`x`, `y`) until `max` and update `sp` */
static uint16_t draw_text(uint16_t x, uint16_t y, uint16_t max, char const **sp, uint8_t const *font);


/// POLICE LINE /// DO NOT CROSS ///


struct draw_glyph {
	uint8_t width, height;
	uint8_t const *bitmap;
};

static inline struct draw_glyph
draw_get_glyph(uint8_t const *font, char c)
{
	uint8_t const *p = font;
	struct draw_glyph g;

	assert(c >= ' ' || c <= '~');

	g.height = draw_fn_get_font_byte(p++);
	for (char i = ' '; i <= c; i++) {
		g.width = draw_fn_get_font_byte(p++);
		g.bitmap = p;
		p += (g.width * g.height + 7) / 8;
	}
	return g;
}

static void
draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	int16_t debt, d, dx, dy, sx, sy;

#define DISTANCE(x, y) ((x) > (y) ? (x) - (y) : (y) - (x))
#define DIRECTION(x, y) ((x) < (y) ? 1 : (x) > (y) ? -1 : 0)
	sx = DIRECTION(x0, x1);
	sy = DIRECTION(y0, y1);
	dx = DISTANCE(x0, x1);
	dy = DISTANCE(y0, y1);
#undef DISTANCE
#undef DIRECTION
	debt = ((dx > dy) ? dx : -dy) / 2;
	while (x0 != x1 || y0 != y1) {
		d = debt;
		if (d > -dx) {
			x0 += sx;
			debt -= dy;  /* debt toward y after we wrote toward x */
		}
		if (d < dy) {
			y0 += sy;
			debt += dx;  /* debt toward x after we wrote toward y */
		}
		draw_fn_point(x0, y0);
	}
}

static inline void
draw_glyph(uint16_t x, uint16_t y, struct draw_glyph g)
{
	uint16_t x0 = 0, y0 = 0;

	for (x0 = 0; x0 < g.width; x0++) {
		for (y0 = 0; y0 < g.height; y0++) {
			uint8_t byte;
			size_t i;

			i = y0 * g.width + x0;
			byte = draw_fn_get_font_byte(g.bitmap + i / 8);
			if (byte & 1<<i%8)
				draw_fn_point(x + x0, y + y0);
		}
	}
}

static uint16_t
draw_text(uint16_t x, uint16_t y, uint16_t max, char const **sp, uint8_t const *font)
{
	char const *s;

	for (s = *sp; *s != '\0'; s++) {
		struct draw_glyph g;

		g = draw_get_glyph(font, isprint(*s) ? *s : '?');
		if (x + g.width > max)
			break;
		draw_glyph(x, y, g);
		x += g.width + 1;
	}
	*sp = s;
	return x;
}

#endif
