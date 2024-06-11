#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

uint8_t*
decrypt_data(uint8_t* data, size_t data_size, uint8_t* key, size_t key_size)
{
	for (size_t ndx = 0; ndx < data_size; ndx++)
		data[ndx] -= key[ndx % key_size];
	return (data);
}

uint8_t*
encrypt_data(uint8_t* data, size_t data_size, uint8_t* key, size_t key_size)
{
	for (size_t ndx = 0; ndx < data_size; ndx++)
		data[ndx] += key[ndx % key_size];
	return (data);
}
