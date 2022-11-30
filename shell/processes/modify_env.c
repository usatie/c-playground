#include <stdio.h>
#include <stdlib.h>

extern char	**environ;

void	display_env(void)
{
	char	**ep;

	puts("---------------------------\ndisplay_env():\n");
	for (ep = environ; *ep != NULL; ep++)
		puts(*ep);
}


int	main(void)
{
	char	*env;

	env = getenv("PATH");
	puts(env);
	if (putenv("hoge=fuga") < 0)
		exit(1);
	if (setenv("hogehoge", "fugafuga", 0) < 0)
		exit(1);
	display_env();
	unsetenv("hoge");
	display_env();
	exit(EXIT_SUCCESS);
}
