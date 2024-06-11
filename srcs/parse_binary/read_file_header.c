#include "woody.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define FH_LENGTH 64

bool
is_ELF(const char* buff)
{
	if (buff[0] != 0x7F)
		return (false);
	return (strncmp(&(buff[1]), "ELF", 3) == 0);
}

void
check_file_header(woody_t* woody, const char* buff, int r)
{
	if (r != FH_LENGTH)
		quit_program(woody, ": file header is not 64 bytes", EXIT_FAILURE);
	if (is_ELF(buff) == false)
		quit_program(woody, ": binary is not ELF", EXIT_FAILURE);
	if (buff[4] != 2)
		quit_program(woody, ": binary is 32 bit", EXIT_FAILURE);
}

void
obtain_values(woody_t* woody, const char* buff)
{
	memcpy(&(woody->e_phoff), &(buff[0x20]), 8);
	memcpy(&(woody->e_phentsize), &(buff[0x36]), 2);
	memcpy(&(woody->e_phnum), &(buff[0x38]), 2);
	memcpy(&(woody->e_shoff), &(buff[0x28]), 8);
	memcpy(&(woody->e_shentsize), &(buff[0x3A]), 2);
	memcpy(&(woody->e_shnum), &(buff[0x3C]), 2);
	memcpy(&(woody->e_shstrndx), &(buff[0x3E]), 2);
	printf("Entry offset: %lu\nEntry size: %i\nEntry num: %i\n", woody->e_phoff, woody->e_phentsize, woody->e_phnum);
	printf("Section offset: %lu\nSection entry size: %i\nSection entry num: %i\nesh_strndx: %i\n", woody->e_shoff, woody->e_shentsize, woody->e_shnum, woody->e_shstrndx);
}

void
read_file_header(woody_t* woody)
{
	char	buff[FH_LENGTH];
	int		r = 0;

	r = read(woody->in_fd, buff, FH_LENGTH);
	if (r == -1)
		quit_program(woody, NULL, EXIT_FAILURE);
	check_file_header(woody, buff, r);
	obtain_values(woody, buff);
}
