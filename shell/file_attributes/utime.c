#include <sys/stat.h>
#include <sys/time.h>
#include <utime.h>
#include <stdlib.h>
#include <stdio.h>

void	test_utime(const char *filepath)
{
	struct stat		sbuf;
	struct utimbuf	utbuf;

	if (stat(filepath, &sbuf) == -1)
	{
		printf("stat() error\n");
		exit(EXIT_FAILURE);
	}
	utbuf.actime = sbuf.st_atime;
	utbuf.modtime = sbuf.st_atime;
	if (utime(filepath, &utbuf) == -1)
	{
		printf("utime() error\n");
		exit(EXIT_FAILURE);
	}
}

void	test_utimes(const char *filepath)
{
	struct stat		sbuf;
	struct timeval	tv[2];

	if (stat(filepath, &sbuf) == -1)
	{
		printf("stat() error\n");
		exit(EXIT_FAILURE);
	}
	// file access time
	tv[0].tv_sec = sbuf.st_atime;
	tv[0].tv_usec = 0;
	// file modification time
	tv[1].tv_sec = sbuf.st_atime;
	tv[1].tv_usec = 0;
	if (utimes(filepath, tv) == -1)
	{
		printf("utimes() error\n");
		exit(EXIT_FAILURE);
	}
}
// TODO: try futimes and lutimes
// futimes(fd, tv);
// lutimes(filepath, tv);

int	main(int argc, const char *argv[])
{
	if (argc != 3)
		exit(EXIT_FAILURE);

	test_utime(argv[1]);
	test_utimes(argv[2]);
	return (0);
}
