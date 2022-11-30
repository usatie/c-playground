#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <termios.h>
#include <sys/ioctl.h>

static void
sigwinchHandler(int sig)
{
	(void)sig;
}

int	main(void)
{
	struct winsize		ws;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigwinchHandler;
	if (sigaction(SIGWINCH, &sa, NULL) == -1)
		exit(1);

	for (;;)
	{
		pause();

		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
			exit(1);
		printf("Caught SIGWINCH, new window size: "
				"%d rows * %d columns\n", ws.ws_row, ws.ws_col);
	}
	if (ioctl(STDOUT_FILENO, TIOCSWINSZ, &ws) == -1)
		exit(1);
	printf("terminal window size is changed.\n");
}
