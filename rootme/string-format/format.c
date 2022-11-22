#include <stdio.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	char	buf[32] = "Hello\n";

	(void)argc;
	strncpy(buf, argv[1], 32);
	printf(buf);
}
