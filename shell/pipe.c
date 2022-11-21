#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

// Returns the NULL or c terminated length of the str.
static size_t	strclen(char *str, char sep)
{
	size_t	cnt;

	cnt = 0;
	while (*str && *str != sep)
	{
		cnt++;
		str++;
	}
	return (cnt);
}

// The strndup() function copies at most n characters from the string s1
// always NUL terminating the copied string.
static char	*ft_strndup(char *src, size_t size)
{
	size_t	len;
	char	*new;

	len = strlen(src);
	if (len > size)
		len = size;
	new = calloc(len + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	memmove(new, src, len);
	return (new);
}

// RETURN VALUE
// 		Size of the array needed to split str with c.
static size_t	get_array_size(char *str, char c)
{
	size_t	array_size;

	array_size = 1;
	while (*str)
	{
		if (strclen(str, c) > 0)
		{
			array_size++;
			str += strclen(str, c);
		}
		else
			str++;
	}
	return (array_size);
}

// RETURN VALUE
// 		The array splitted str with c.
// 		Example1.
//	 		str: "Hello,World,Shun"
// 			c: ','
// 			arr_size: 4
// 			arr: {"Hello", "World", "Shun", NULL}
// 		Example2.
//	 		str: ",,,Continuous,,commas,,,will,,be,,ignored,"
// 			c: ','
// 			arr_size: 6
// 			arr: {"Continuous, "commas", "will", "be", "ignored", NULL}
// 		EXAMPLE3:
// 			str: ""
// 			c: ','
// 			arr_size: 1
// 			arr: {NULL}
//
//
// s: not protected
char	**ft_split(char *s, char c)
{
	char	**arr;
	int		i;

	arr = calloc(get_array_size(s, c), sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (strclen(s, c) > 0)
		{
			arr[i] = ft_strndup(s, strclen(s, c));
			if (arr[i++] == NULL)
			{
				while (i)
					free(arr[--i]);
				free(arr);
				return (NULL);
			}
			s += strclen(s, c);
		}
		else
			s++;
	}
	return (arr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*s;
	char	*ptr;

	len = strlen(s1) + strlen(s2);
	s = malloc(len + 1);
	if (s == NULL)
		return (NULL);
	ptr = s;
	while (*s1)
		*s++ = *s1++;
	while (*s2)
		*s++ = *s2++;
	*s = '\0';
	return (ptr);
}

char	*find_path(char *prog, char *envp[])
{
	char	*path;
	char	**paths;
	struct stat buf;

	while (strncmp("PATH=", *envp, 5))
		envp++;
	paths = ft_split(*envp, ':');
	for (int i = 0; paths[i]; i++)
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, prog);
		if (lstat(path, &buf) == 0 && buf.st_mode & S_IXUSR)
			return (path);
		free(path);
	}
	return (NULL);
}

void	exec(int pipes[10][2], int i, char *argv[], char *envp[])
{
	close(pipes[i-1][1]);
	close(pipes[i][0]);
	dup2(pipes[i-1][0], STDIN_FILENO);
	dup2(pipes[i][1], STDOUT_FILENO);
	execve(find_path(argv[0], envp), argv, envp);
	dprintf(STDERR_FILENO, "error: execve()\n");
	exit(1);
}

void	close_unused_pipes(int pipes[10][2], int i, int numCommand)
{
	for (int j = 1; j < numCommand; j++)
	{
		if (j != i && j != i - 1)
		{
			close(pipes[j][0]);
			close(pipes[j][1]);
		}
	}	
}

int	main(int argc, char *argv[], char *envp[])
{
	// pipe[i] is a pipe between process `i-1` and process `i`
	// process `i-1` writes to pipe[i][1]
	// process `i` reads from pipe[i][0]
	//
	// process `i` writes to pipe[i+1][1]
	//
	// process: 
	// -1 : terminal
	// 0 : parent
	// 1 : child 1
	// 2 : child 2
	// ...
	//

	int		pipes[10][2];
	int		pids[10];
	const int	numCommand = argc - 1;

	pipes[0][0] = STDIN_FILENO;
	pipes[0][1] = STDOUT_FILENO;
	for (int i = 1; i < numCommand; i++)
		pipe(pipes[i]);
	pipes[numCommand][0] = STDIN_FILENO;
	pipes[numCommand][1] = STDOUT_FILENO;
	if (argc < 2)
	{
		dprintf(STDERR_FILENO, "usage: %s cmd1 cmd2...\n", argv[0]);
		exit(1);
	}
	for (int i = 1; i < argc; i++)
	{
		if ((pids[i] = fork()) > 0)
		{
			// parent
			// go next
		}
		else if (pids[i] == 0)
		{
			// child
			close_unused_pipes(pipes, i, numCommand);
			exec(pipes, i, ft_split(argv[i], ' '), envp);
		}
		else
		{
			// error
			dprintf(STDERR_FILENO, "error: fork()\n");
			exit(1);
		}
	}
	for (int i = 1; i < numCommand; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}	
	for (int i = 1; i < argc; i++)
	{
		int	status;
		waitpid(pids[i], &status, WNOHANG);
	}
	return (0);
}
