#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

void
print_bytes(char* bytes, size_t size)
{
	for (size_t ndx = 0; ndx < size; ndx++)
	{
		if (ndx > 0)
			printf(" ");
		if (bytes[ndx] == 0)
			printf(".");
		else
			printf("%c", bytes[ndx]);
	}
	printf("\n");
	fflush(stdout);
}

int
main(void)
{
	int	fd = open("test", O_RDWR);
	if (fd == -1)
		exit(EXIT_FAILURE);
	
	off_t	off = lseek(fd, 0x2001, SEEK_SET);
	if (off != 0x2000)
		return (close(fd), EXIT_FAILURE);
	
	
	char	buff[16];
	int		r = read(fd, buff, 16);
	if (r != 16)
		return (close(fd), EXIT_FAILURE);
	
	print_bytes(buff, 16);

	close(fd);
}
