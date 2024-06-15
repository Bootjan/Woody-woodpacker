#ifndef WOODY_H
# define WOODY_H

# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct {
	int			in_fd;
	uint64_t	e_entry;
	uint64_t	e_phoff;
	uint16_t	e_phnum;
	uint16_t	e_phentsize;
	uint64_t	e_shoff;
	uint16_t	e_shnum;
	uint16_t	e_shentsize;
	uint16_t	e_shstrndx;
}	woody_t;

void	quit_program(woody_t* woody, const char* msg, uint8_t exit_status);
void	read_program_header(woody_t* woody);
void	read_file_header(woody_t* woody);

#endif
