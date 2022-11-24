#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <fcntl.h>

void	err_exit(char *fmt, ...)
{
	va_list	ap;
	va_start(ap, fmt);
	vdprintf(STDERR_FILENO, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

void	pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX) == NULL)
		err_exit("getcwd");
	printf("cwd: %s\n", buf);
}

void	comeback_via_fchdir(void)
{
	int	fd = open(".", O_RDONLY); // keep current dir to come back later
								  //
	printf("comeback_via_fchdir\n");
	pwd(); // current dir
	chdir(".."); // change dir
	pwd();
	fchdir(fd); // come back to initial dir
	close(fd);
	pwd();
}

void	comeback_via_chdir(void)
{
	char	buf[PATH_MAX];

	printf("comeback_via_chdir\n");
	if (getcwd(buf, PATH_MAX) == NULL)
		err_exit("getcwd");
	pwd(); // current dir
	chdir(".."); // change dir
	pwd();
	chdir(buf); // come back to initial dir
	pwd();
}

int	main(void)
{
	comeback_via_fchdir();
	comeback_via_chdir();
	exit(EXIT_SUCCESS);
}
