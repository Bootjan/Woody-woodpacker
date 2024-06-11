#include "woody.h"

void
read_program_header_entry(woody_t* woody)
{
	char	buff[woody->e_phentsize];
	int		r;

	r = read(woody->in_fd, buff, woody->e_phentsize);
	if (r == -1)
		quit_program(woody, NULL, EXIT_FAILURE);
	if (r != woody->e_phentsize)
		quit_program(woody, ": program header entry size was incorrect", EXIT_FAILURE);
	
}

void
read_program_header(woody_t* woody)
{
	for (int i = 0; i < woody->e_phnum; i++)
		read_program_header_entry(woody);
}
