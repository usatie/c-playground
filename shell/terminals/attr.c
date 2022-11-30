#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <termios.h>

/*
struct termios {
	tcflag_t	c_iflag;    // Input flags
	tcflag_t	c_oflag;    // Output flags
	tcflag_t	c_cflag;    // Control flags
	tcflag_t	c_lflag;    // Local modes
	cc_t		c_line;     // Line discipline
	cc_t		c_cc[NCCS]; // Terminal special characters
	speed_t		c_ispeed;   // Input speed
	speed_t		c_ospeed;   // Output speed
}
*/
int	main(void)
{
	char	buf[1024];
	struct termios tp;

	if (tcgetattr(STDIN_FILENO, &tp) == -1)
		exit(1);
	tp.c_lflag &= ~ECHO;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1)
		exit(1);

	read(STDIN_FILENO, buf, 1023);  // Not display the input to the terminal
	exit(EXIT_SUCCESS);
}
