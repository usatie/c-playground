#include <unistd.h>
#include <stdarg.h>

int	my_printf(const char * restrict format, ...);

size_t	my_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

typedef struct s_context {
	int	wc; // write count
	const char *format;
	va_list	ap;
}	t_ctx;

void	print_s(t_ctx *ctx)
{
	char *s;

	s = va_arg(ctx->ap, char *);
	ctx->wc += write(STDOUT_FILENO, s, my_strlen(s));
}

int	put_abs_n(unsigned int x, char *base, int baselen)
{
	int wc;

	if (x == 0)
		return (0);
	// x = 12345
	wc = put_abs_n(x / baselen, base, baselen); // 1234
	wc += write(STDOUT_FILENO, &base[x % baselen], 1); // 5
	return (wc);
}

int	print_int(int x, char *base, int baselen)
{
	int	wc;

	wc = 0;
	if (x == 0)
		wc += write(STDOUT_FILENO, "0", 1);
	else if (x < 0)
	{
		wc += write(STDOUT_FILENO, "-", 1);
		wc += put_abs_n(-x, base, baselen);
	}
	else
		wc += put_abs_n(x, base, baselen);
	return (wc);
}

int	print_uint(unsigned int x, char *base, int baselen)
{
	int	wc;

	wc = 0;
	if (x == 0)
		wc += write(STDOUT_FILENO, "0", 1);
	else
		wc += put_abs_n(x, base, baselen);
	return (wc);
}

void	print_d(t_ctx *ctx)
{
	int	x;

	x = va_arg(ctx->ap, int);
	ctx->wc += print_int(x, "0123456789", 10);
}

void	print_x(t_ctx *ctx)
{
	unsigned int	x;

	x = va_arg(ctx->ap, unsigned int);
	ctx->wc += print_uint(x, "0123456789abcdef", 16);
}

void	print_conversion(t_ctx *ctx)
{
	if (ctx->format[1] == 's')
		print_s(ctx);
	else if (ctx->format[1] == 'd')
		print_d(ctx);
	else if (ctx->format[1] == 'x')
		print_x(ctx);
	else
		ctx->wc += write(STDOUT_FILENO, ctx->format, 2);
	ctx->format += 2;
}

void	print_non_conversion(t_ctx *ctx)
{
	size_t	len;

	len = 0;
	while (ctx->format[len] && ctx->format[len] != '%')
		len++;

	ctx->wc += write(STDOUT_FILENO, ctx->format, len);
	ctx->format += len;
}

int	my_printf(const char * restrict format, ...)
{
	t_ctx	ctx;

	ctx.wc = 0;
	ctx.format = format;
	va_start(ctx.ap, format);
	while (*ctx.format)
	{
		if (*ctx.format == '%')
			print_conversion(&ctx);
		else
			print_non_conversion(&ctx);
	}
	va_end(ctx.ap);
	return (ctx.wc);
}
