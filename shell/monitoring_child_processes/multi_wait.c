#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/wait.h>

#define BUF_SIZE 100
char	*current_time(void)
{
	static char	buf[BUF_SIZE];
	time_t	t;
	size_t	s;
	struct tm	*tm;

	t = time(NULL);
	tm = localtime(&t);
	if (tm == NULL)
		return NULL;
	s = strftime(buf, BUF_SIZE, "%c", tm);
	return (s == 0) ? NULL : buf;
}

int	main(int argc, char *argv[])
{
	int		num_dead;
	pid_t	child_pid;
	int		j;

	if (argc < 2)
		exit(1);

	setbuf(stdout, NULL);	/* Disable buffering of stdout */

	for (j = 1; j < argc; j++) {
		switch (fork()) {
		case -1:
			exit(1);
		case 0:
			printf("[%s] child %d started with PID %ld, sleeping %s "
					"seconds\n", current_time(), j, (long) getpid(), argv[j]);
			sleep(atoi(argv[j]));
			_exit(0);
		default:
			break;
		}
	}
	num_dead = 0;
	for (;;) {
		child_pid = wait(NULL);
		if (child_pid == -1) {
			if (errno == ECHILD) {
				printf("No more children - bye!\n");
				exit(EXIT_SUCCESS);
			} else {
				exit(1);
			}
		}
		num_dead++;
		printf("[%s] wait() returned child PID %ld (num_dead=%d)\n",
				current_time(), (long) child_pid, num_dead);
	}
}
