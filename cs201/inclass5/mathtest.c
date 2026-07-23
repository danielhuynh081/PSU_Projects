#include <stdio.h>
#include <stdlib.h>
#include "myutil.h"

// Daniel Huynh, Jesse Chaney CS201
// This program tests the square and cube utility functions.
int main(void)
{
	int i = 5;

	printf("square : %d cube %d \n", squareit(i), cubeit(i));

	return EXIT_SUCCESS;

}

