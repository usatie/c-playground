#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	err_exit(char *fmt, ...)
{
	va_list	ap;
	va_start(ap, fmt);
	vdprintf(STDERR_FILENO, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

int	main(void)
{
	int		pfd[2];
	
	pipe(pfd);

	// ls
	switch (fork())
	{
		case -1:
			err_exit("fork");
		case 0: // child
			if (close(pfd[0]) < 0)
				err_exit("close 1");
			if (pfd[1] != STDOUT_FILENO)
			{
				if (dup2(pfd[1], STDOUT_FILENO) < 0)
					err_exit("dup2 1");
				if (close(pfd[1]) < 0)
					err_exit("close 2");
			}
			execlp("ls", "ls", NULL);
			err_exit("execlp ls");
		default: // parent
			break ;
	}

	// wc
	switch (fork())
	{
		case -1:
			err_exit("fork");
		case 0: // child
			if (close(pfd[1]) < 0)
				err_exit("close 3");
			if (pfd[0] != STDIN_FILENO)
			{
				if (dup2(pfd[0], STDIN_FILENO) < 0)
					err_exit("dup2 2");
				if (close(pfd[0]) < 0)
					err_exit("close 4");
			}
			execlp("wc", "wc", "-l", NULL);
			err_exit("execlp wc");
		default: // parent
			break ;
	}

	// parent
	if (close(pfd[0]) < 0)
		err_exit("close 5");
	if (close(pfd[1]) < 0)
		err_exit("close 6");
	if (wait(NULL) < 0)
		err_exit("wait 1");
	if (wait(NULL) < 0)
		err_exit("wait 2");
	exit(EXIT_SUCCESS);
}
