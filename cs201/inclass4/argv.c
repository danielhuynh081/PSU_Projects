#include <stdio.h>
#include <stdlib.h>
//gcc -Wall -g -o argc argc.c
//./argv
// Daniel Huynh, Jesse Chaney CS201
// This program demonstrates how command-line arguments are passed to a C program.

//./argv arg1 arg2 arg3 arg4
//./argv a b c d e f g h i j k l m 
//./argv *.c 


int main(int argc, char *argv[])
{
	printf("the value of argc is : %d\n", argc);

	printf("the value of argv[0] is : %s\n\n", argv[0]);

	for(int i =1; i < argc; ++i)
	{
		printf("\tThe value of argv[%d} is %s\n", i, argv[i]);
	}

	return EXIT_SUCCESS;




}
