#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gcc -g -Wall -o  front1 front1.c
// ./front1.c
// Daniel Huynh, Jesse Chaney CS201
// This program displays the first few lines of input.

#define BUFFER_SIZE  1024
#define MAX_LINES  5

int main(int argc, char *argv[])
{
	FILE * ifile = stdin;
	int line_count =0;
	int max_lines = MAX_LINES;
	char buf[BUFFER_SIZE] = {'\0'};
	char *buf_ptr = NULL;

	buf_ptr = fgets(buf, BUFFER_SIZE, ifile);
	line_count++;
	while((line_count <= max_lines) && (buf_ptr != NULL))
	{
		printf("%s", buf);
		buf_ptr = fgets(buf, BUFFER_SIZE, ifile);
		line_count++;
		
	}


	return EXIT_SUCCESS;
}
