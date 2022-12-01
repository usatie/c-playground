#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

void	print_wait_status(const char *msg, int status);

int	main(void)
{
	int		status;
	pid_t	child_pid;

	switch (fork()) {
	case -1: exit(1);
	case 0:
		printf("Child started with PID = %ld\n", (long) getpid());
		for (;;)
			pause();
		exit(1);
	default:
		for (;;) {
			child_pid = waitpid(-1, &status, WUNTRACED | WCONTINUED);
			if (child_pid == -1)
				exit(1);
			printf("waitpid() returned: PID=%ld; status=0x%04x (%d,%d)\n",
					(long) child_pid,
					(unsigned int) status, status >> 8, status & 0xff);
			print_wait_status(NULL, status);
			if (WIFEXITED(status) || WIFSIGNALED(status))
				exit(0);
		}
	}
}
