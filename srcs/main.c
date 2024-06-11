#include "woody.h"

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void
quit_program(woody_t* woody, const char* msg, uint8_t exit_status)
{
	if (exit_status == EXIT_FAILURE)
		fprintf(stderr, "Error%s\n", msg ? msg : strerror(errno));
	if (woody->in_fd > 0)
		close(woody->in_fd);
	exit(exit_status);
}

void
woody_woodpack(woody_t* woody)
{
	read_file_header(woody);
	read_program_header(woody);
	quit_program(woody, NULL, EXIT_SUCCESS);
}

int
main(int ac, char* const* av)
{
	woody_t	woody = { -1, 0, 0, 0, 0, 0, 0, 0 };
	if (ac != 2)
		quit_program(&woody, ": give executable name", EXIT_FAILURE);
	woody.in_fd = open(av[1], O_RDONLY);
	if (woody.in_fd == -1)
		quit_program(&woody, NULL, EXIT_FAILURE);
	
	woody_woodpack(&woody);
}
