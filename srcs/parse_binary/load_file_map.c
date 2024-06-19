#include "woody.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

ssize_t
get_file_size(const char* file_name)
{
	struct stat	st;
	if (stat(file_name, &st) < 0)
		return (-1);
	return (st.st_size);
}

int8_t
load_file_map(file_map_t* file_map, const char* file_name)
{
	memset(file_map, 0, sizeof(file_map_t));

	ssize_t	file_size = get_file_size(file_name);
	if (file_size == -1)
		return (-1);
	
	int		fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	
	void*	data = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (!data)
		return (close(fd), -1);

	file_map->file_fd = fd;
	file_map->file_size = file_size;
	file_map->data = data;
	return (0);
}

void
delete_file_map(file_map_t* file_map)
{
	if (file_map->data)
		munmap(file_map->data, file_map->file_size);
	if (file_map->file_fd)
		close(file_map->file_fd);
}
