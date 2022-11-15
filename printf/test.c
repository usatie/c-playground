#include <stdio.h>

#define F(format, ...) {\
	printf("printf(%s, %s):\n", #format, #__VA_ARGS__);\
	int expected = printf(format __VA_OPT__(,) __VA_ARGS__);\
	int actual = my_printf(format __VA_OPT__(,) __VA_ARGS__);\
	assert_equal(expected, actual);\
}

int	my_printf(const char * restrict format, ...);

void	assert_equal(int expected, int actual)
{
	if (expected == actual)
		printf("OK\n");
	else
		printf("expected: %d, actual: %d\n", expected, actual);
	printf("\n");
}

int	main(void)
{
	F("hello\n");
	F("hello %s\n", "world");
	F("hello %d\n", 42);
	F("hello %d\n", 0);
	F("hello %d\n", -42);
	F("hello %x\n", 42);
	F("hello %x\n", 0);
	F("hello %x\n", -42);
	return (0);
}
