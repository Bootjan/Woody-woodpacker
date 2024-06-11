#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define LOWER_BOUND ' '
#define HIGHER_BOUND '~'

static char
generate_random_byte(void)
{
	return (rand() % (HIGHER_BOUND - LOWER_BOUND + 1) + LOWER_BOUND);
}

char*
generate_key(size_t size)
{
	char*	key = malloc(size + 1);
	if (!key)
		return (NULL);
	srand(time(0));
	for (size_t ndx = 0; ndx < size; ndx++)
		key[ndx] = generate_random_byte();
	key[size] = '\0';
	return (key);
}
