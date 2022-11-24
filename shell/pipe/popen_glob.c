#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define POPEN_FMT "/bin/ls -d %s 2> /dev/null"
#define PAT_SIZE 50
#define PCMD_BUF_SIZE (sizeof(POPEN_FMT) + PAT_SIZE)

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
	char	pat[PAT_SIZE];
	char	popenCmd[PCMD_BUF_SIZE];
	FILE	*fp;
	bool	badPattern;
	int		len, status, fileCnt, j;
	char	pathName[PATH_MAX];

	while (1)
	{
		printf("pattern:");
		fflush(stdout);
		if (fgets(pat, PAT_SIZE, stdin) == NULL)
			break ;
		len = strlen(pat);
		if (len <= 1) // empty line
			continue ;
		if (pat[len - 1] == '\n') // strip trailing newline
			pat[len - 1] = '\0';
		// Ensure that the pattern contains only valid characters
		for (j = 0, badPattern = false; j < len && !badPattern; j++)
		{
			if (!isalnum((unsigned char)pat[j]) && strchr("_*?[^-].", pat[j]) == NULL)
				badPattern = true;
		}
		if (badPattern)
		{
			printf("Bad pattern character %c\n", pat[j - 1]);
			continue ;
		}
		snprintf(popenCmd, PCMD_BUF_SIZE, POPEN_FMT, pat);
		fp = popen(popenCmd, "r");
		if (fp == NULL)
		{
			printf("popen failed\n");
			continue ;
		}
		fileCnt = 0;
		while (fgets(pathName, PATH_MAX, fp) != NULL)
		{
			printf("%s", pathName);
			fileCnt++;
		}
		status = pclose(fp);
		printf("   %d matching file%s\n", fileCnt, (fileCnt != 1) ? "s" : "");
		printf("   pclose() status = %#x\n", status);
		if (status == -1)
			printf("\t status description for %d is ...\n", status);
	}
	exit(EXIT_SUCCESS);
}
