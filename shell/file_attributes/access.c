#include <stdlib.h>
#include <stdio.h>

#include <unistd.h> // access()

int	main(int argc, char *argv[])
{
	if (argc != 2)
		exit(EXIT_FAILURE);
	if (access(argv[1], F_OK) == -1)
		printf("File doesn't exist.\n");
	else
		printf("File exists.\n");
	if (access(argv[1], R_OK) == -1)
		printf("File can not be read.\n");
	else
		printf("File can be read.\n");
	if (access(argv[1], W_OK) == -1)
		printf("File can not be written.\n");
	else
		printf("File can be written.\n");
	if (access(argv[1], X_OK) == -1)
		printf("File can not be executed.\n");
	else
		printf("File can be executed.\n");


	/*
	 * Time-of-check and time-of-use race condition
	 *
		1. access()
		2. execute_something_on_a_file_as_root()

		If the pathname is a symbolic link, 
		malicious user may change the link to a different file.
		It ends up operating on a file which real user ID does not have permission.


		So it is better to avoid the use of access().

		Instead, change the effective user ID of the process.
	*/
}
