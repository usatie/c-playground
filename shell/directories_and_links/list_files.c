#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

void	err_exit(char *fmt, ...)
{
	va_list	ap;
	va_start(ap, fmt);
	vdprintf(STDERR_FILENO, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

static void	listFiles(const char *dirpath)
{
	DIR	*dirp;
	struct dirent *ent;
	bool	isCurrent;

	isCurrent = strcmp(dirpath, ".") == 0;
	dirp = opendir(dirpath);
	while ((ent = readdir(dirp)))
	{
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
			continue ;
		if (!isCurrent)
			printf("%s/", dirpath);
		printf("%s\n", ent->d_name);
	}
	closedir(dirp);
}

int	main(int argc, const char *argv[])
{
	if (argc == 1)
		listFiles(".");
	else if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
			listFiles(argv[i]);
	}
	else
		err_exit("usage: %s [path]\n", argv[0]);
}
