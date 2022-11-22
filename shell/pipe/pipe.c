#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 10

void	err_exit(char *fmt, ...)
{
	va_list	ap;
	va_start(ap, fmt);
	vdprintf(STDERR_FILENO, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	int		pfd[2];
	char	buf[BUF_SIZE];
	ssize_t	num_read;
	
	if (argc != 2)
		err_exit("usage: %s message\n", argv[0]);
	pipe(pfd);
	switch (fork())
	{
		case -1:
			err_exit("fork");
		case 0: // child
			if (close(pfd[1]) < 0)
				err_exit("close - child");
			while (1)
			{
				num_read = read(pfd[0], buf, BUF_SIZE);
				if (num_read < 0)
					err_exit("read");
				if (num_read == 0)
					break ;
				if (write(STDOUT_FILENO, buf, num_read) != num_read)
					err_exit("child partial/failed write");
			}
			write(STDOUT_FILENO, "\n", 1);
			if (close(pfd[0]) < 0)
				err_exit("close - child");
			exit(EXIT_SUCCESS);
		default: // parent
			if (close(pfd[0]) < 0)
				err_exit("close - parent");
			if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
				err_exit("child partial/failed write");
			if (close(pfd[1]) < 0)
				err_exit("close - parent");
			wait(NULL);
			exit(EXIT_SUCCESS);
	}
}
