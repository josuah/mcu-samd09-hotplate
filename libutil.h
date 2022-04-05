#ifndef LIBUTIL_H
#define LIBUTIL_H


/* helper macros to improve readability and avoid mistakes */
#define LEN(x) (sizeof(x) / sizeof(*x))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define SIGN(x) (((x) > 0) - ((x) < 0))

/* to be set to a function that write `s` to the user, such as over an UART */
extern int print(char const *s);

/* parse an unsigned integer up to `max` (included) in base `b` (up to 16)
 * from (*`sp`) and shift the pointer to the end, or set it to NULL on error */
static uint64_t strint(char const **sp, uint64_t max, uint8_t b);

/* format a signed integer `i64` at the end of `s` of size `sz` using base `b`
 * and return the first printable byte of `s` */
static char *fmtint(char *s, size_t sz, int64_t i64, uint8_t b);

/* print each string argument until NULL is encountered */
static int put_(char const *s, ...);

/* safer and easier wrapper around put_() */
#define put(...) put_(__VA_ARGS__, NULL)

/* macros to format integers and print them B(bin), D(dec), X(hex) */
#define fmtb(n) fmtint((char[65]){0}, 65, n, 2)
#define fmtd(n) fmtint((char[21]){0}, 21, n, 10)
#define fmtx(n) fmtint((char[17]){0}, 17, n, 16)
#define fmtc(c) (char[2]){ c, '\0' }


/// POLICE LINE /// DO NOT CROSS ///


static char const *digits = "0123456789ABCDEF";

static uint64_t
strint(char const **sp, uint64_t max, uint8_t b)
{
	uint64_t n;
	char const *s, *p;
	char c;

	n = 0;
	for (s = *sp ;; s++) {
		c = toupper(*s);
		p = strchr(digits, c);
		if (p == NULL || p >= digits + b)
			break;

		if (n > max / b)
			goto err;
		n *= b;

		if (n > max - (p - digits))
			goto err;
		n += p - digits;
	}
	if (*sp == s)
		goto err;
	*sp = s;
	return n;
err:
	*sp = NULL;
	return 0;
}

static char *
fmtint(char *s, size_t sz, int64_t i64, uint8_t b)
{
	assert(b <= strlen(digits));

	s += sz;
	*--s = '\0';

	if (i64 == 0) {
		*--s = digits[0];
		return s;
	}

	for (uint64_t u64 = ABS(i64); u64 > 0; u64 /= b)
		*--s = digits[u64 % b];
	if (i64 < 0)
		*--s = '-';
	return s;
}

static char *
strsep(char **sp, char const *sep)
{
	char *s, *token;

	if (*sp == NULL)
		return NULL;

	token = *sp;
	for (s = *sp; strchr(sep, *s) == NULL; s++);

	if (*s == '\0') {
		*sp = NULL;
	}else{
		*s = '\0';
		*sp = s + 1;
	}
	return token;
}

static int
put_(char const *s, ...)
{
	va_list ap;

	va_start(ap, s);
	do {
		if (print(s) == -1)
			return -1;
	} while((s = va_arg(ap, char *)) != NULL);
	return 0;
}

#endif
