#include <stdlib.h>
#include <stdio.h>

extern char	**environ;

int	main(void)
{
	char	**ep;

	for (ep = environ; *ep != NULL; ep++)
		puts(*ep);

	exit(EXIT_SUCCESS);
}
