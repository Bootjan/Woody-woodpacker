#include <stdio.h>
#include <stdint.h>

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

uint8_t
compute_ring(uint8_t dimension, uint8_t i)
{
	uint8_t	col = i % dimension;
	uint8_t	row = i / dimension;

	uint8_t	smallest = row;
	
	if (col < smallest)
		smallest = col;
	if (dimension - col - 1 < smallest)
		smallest = dimension - col - 1;
	if (dimension - row - 1 < smallest)
		smallest = dimension - row - 1;
	return (smallest);
}

uint8_t
compute_distance(uint8_t i, uint8_t ring, uint8_t direction, uint8_t dimension)
{
	uint8_t	col = i % dimension;
	uint8_t	row = i / dimension;

	switch (direction)
	{
		case RIGHT:	return (dimension - col - 1 - ring);
		case DOWN:	return (dimension - row - 1 - ring);
		case LEFT:	return (col - ring);
		case UP:	return (row - ring - 1);
		default:	return (10);
	}
}

uint8_t
update_direction(uint8_t distance, uint8_t direction)
{
	if (distance == 0)
		return ((direction + 1) % 4);
	return (direction);
}

void
update_i(uint8_t dimension, uint8_t* i, uint8_t* direction)
{
	uint8_t	distance = compute_distance(*i, compute_ring(dimension, *i), *direction, dimension);
	*direction = update_direction(distance, *direction);
	switch (*direction)
	{
		case RIGHT:	*i += 1; return;
		case DOWN:	*i += dimension; return;
		case LEFT:	*i -= 1; return;
		case UP:	*i -= dimension; return;
	}
}

#include <stdbool.h>

bool
done(uint8_t n, uint8_t i, uint8_t direction)
{
	if (n % 2 == 0)
		return (i == n * (n - 3) + 5 - n && direction == UP);
	return (i == n * (n - 3) + 7 - n && direction == UP);
}

int
main(void)
{
	int*	arr[4];
	arr[0] = [ 0, 1, 2, 3 ];
	arr[1] = [ 11, 12, 13, 4 ];
	arr[2] = [ 10, 15, 14, 5 ];
	arr[3] = [ 9, 8, 7, 6 ];
	uint8_t	dimension, i, direction;

	i = 0;
	dimension = 4;
	direction = RIGHT;

	while(!done(dimension, i, direction))
	{
		printf("%i: %i\n", i, arr[i / dimension][i % dimension]);
		update_i(dimension, &i, &direction);
	}
}