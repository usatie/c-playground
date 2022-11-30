#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	set_current_ts(const char *pathname)
{
	int	fd;

	fd = open(".", O_RDONLY);
	utimensat(fd, pathname, NULL, 0);  // Set current timestamp
	// utimensat(fd, pathname, NULL, AT_SYMLINNK_NOFOLLOW);  // the symlink itself should be changed
	close(fd);
}

void	set_atime_current_ts(const char *pathname)
{
	struct timespec	times[2];

	times[0].tv_sec = 0;
	times[0].tv_nsec = UTIME_NOW;
	times[1].tv_sec = 0;
	times[1].tv_nsec = UTIME_OMIT;
	utimensat(AT_FDCWD, pathname, times, 0);  // Only set last access time to the current timestamp and leaves the last modification time unchanged
}

void	set_current_ts_futimens(const char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY);
	futimens(fd, NULL);  // Set current timestamp
	close(fd);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		exit(EXIT_FAILURE);
	set_current_ts(argv[1]);
	set_atime_current_ts(argv[1]);
	set_current_ts_futimens(argv[1]);
}
