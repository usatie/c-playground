#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/wait.h>

int	main(void)
{
	int	status;

	/* Wait for the child whose pid = 123 */
	waitpid(123, &status, 0);
	/* Wait for any child in the same pgroup */
	waitpid(0, &status, 0);
	/* Wait for any child */
	waitpid(-1, &status, 0);
	/* Wait for any child whose pgroup id = 123 */
	waitpid(-123, &status, 0);

	/* Return when a child is stopped by a signal */
	waitpid(-1, &status, WUNTRACED);
	/* Return stopped children that have been resumed by delivery of a SIGCONT signal */
	waitpid(-1, &status, WCONTINUED);
	/* Non blocking */
	waitpid(-1, &status, WNOHANG);
}
