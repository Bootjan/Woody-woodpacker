#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void	quit_program(const char* msg, uint8_t exit_status)
{
	if (exit_status == EXIT_FAILURE)
		fprintf(stderr, "Error%s\n", msg ? msg : strerror(errno));
	exit(exit_status);
}

woody_woodpack(int in_fd)
{
	
}

int	main(int ac, char* const* av)
{
	if (ac != 2)
		quit_program(": give executable name", EXIT_FAILURE);
	int	in_fd = open(av[1], O_RDONLY);
	if (in_fd == -1)
		quit_program(NULL, EXIT_FAILURE);
	
	woody_woodpack(in_fd);
}
