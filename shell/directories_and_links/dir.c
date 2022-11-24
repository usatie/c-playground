#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

int	main(void)
{
	DIR	*dirp;
	struct dirent *ent;

	dirp = opendir(".");
	while ((ent = readdir(dirp)))
		printf("%llu %s %d\n", ent->d_ino, ent->d_name, ent->d_type);
	closedir(dirp);
}
