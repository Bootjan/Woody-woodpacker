#include <stdint.h>
#include <stddef.h>
#define ENCRYPTION_KEY 103

uint8_t*
decrypt_file(uint8_t* file, size_t size)
{
	for (size_t	ndx = 0; ndx < size; ndx++)
		file[ndx] ^= ENCRYPTION_KEY;
	return (file);
}
