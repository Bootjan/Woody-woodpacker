#include <stdint.h>
#include <stdlib.h>

#define HIGHER_BOUND 255
#define LOWER_BOUND 0

static uint8_t
generate_random_byte(void)
{
	return (rand() % (HIGHER_BOUND - LOWER_BOUND + 1) + LOWER_BOUND);
}

uint8_t*
generate_key(size_t size)
{
	uint8_t*	key = malloc(size);
	if (!key)
		return (NULL);
	for (size_t ndx = 0; ndx < size; ndx++)
		key[ndx] = generate_random_byte();
	return (key);
}
