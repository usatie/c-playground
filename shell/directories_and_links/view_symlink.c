#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>

void	err_exit(char *fmt, ...)
{
	va_list	ap;
	va_start(ap, fmt);
	vdprintf(STDERR_FILENO, fmt, ap);
	dprintf(STDERR_FILENO, "\n");
	va_end(ap);
	exit(EXIT_FAILURE);
}

#define BUF_SIZE PATH_MAX

int	main(int argc, const char *argv[])
{
	struct stat	statbuf;
	char		buf[BUF_SIZE];
	ssize_t		numBytes;

	if (argc != 2)
		err_exit("usage: %s pathname\n", argv[0]);
	if (lstat(argv[1], &statbuf) == -1)
		err_exit("lstat");
	if (!S_ISLNK(statbuf.st_mode))
		err_exit("%s is not a symlink\n", argv[1]);

	// readlink()
	numBytes = readlink(argv[1], buf, BUF_SIZE - 1);
	if (numBytes == -1)
		err_exit("readlink");
	buf[numBytes] = '\0';
	printf("readlink: %s --> %s\n", argv[1], buf);

	// realpath()
	if (realpath(argv[1], buf) == NULL)
		err_exit("realpath");
	printf("realpath: %s --> %s\n", argv[1], buf);
	exit(EXIT_SUCCESS);
}
