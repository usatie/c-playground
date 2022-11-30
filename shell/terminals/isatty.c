#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include <unistd.h>

void	display_if_terminal(int fd)
{
	if (isatty(fd))
	{
		printf("%d is a terminal.\n", fd);
		printf("name = %s\n", ttyname(fd));
	}
	else
		printf("%d is not a terminal.\n", fd);

}

int	main(void)
{
	int	fd;

	display_if_terminal(STDIN_FILENO);

	fd = open(".", O_RDONLY);
	display_if_terminal(fd);
	close(fd);
}
