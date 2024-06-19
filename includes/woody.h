#ifndef WOODY_H
# define WOODY_H

# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct {
	int			in_fd;
	ssize_t		file_size;
	void*		file_map;
	uint64_t	e_entry;
	uint64_t	e_phoff;
	uint16_t	e_phnum;
	uint16_t	e_phentsize;
	uint64_t	e_shoff;
	uint16_t	e_shnum;
	uint16_t	e_shentsize;
	uint16_t	e_shstrndx;
}	woody_t;



typedef struct {
	void*	data;
	ssize_t	file_size;
	int		file_fd;
}	file_map_t;


void	quit_program(woody_t* woody, const char* msg, uint8_t exit_status);
void	read_program_header(woody_t* woody);
void	read_file_header(woody_t* woody);


int8_t	load_file_map(file_map_t* file_map, const char* file_name);
void	delete_file_map(file_map_t* file_map);

#endif
