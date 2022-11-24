#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int	main(void)
{
	char	buf[BUF_SIZE];
	int		read_num;
	int		fd;

	fd = open("abc", O_RDWR);
	unlink("abc");
	read_num = read(STDIN_FILENO, buf, BUF_SIZE-1);
	buf[read_num] = '\0';
	if (write(fd, buf, read_num) != read_num)
	{
		printf("write error\n");
		exit(1);
	}
	if (close(fd) < 0)
	{
		printf("close error\n");
		exit(1);
	}
	exit(0);
}
