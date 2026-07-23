#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gcc -g -Wall -o  front2 front2.c
// ./front2 < front2.c
// ./frton2 front2.c
// ./front2 front2.c 7
// Daniel Huynh, Jesse Chaney CS201
// This program displays the first specified number of lines from a file or standard input.

#define BUFFER_SIZE  1024
#define MAX_LINES  5

int main(int argc, char *argv[])
{
	FILE * ifile = stdin;
	int line_count =0;
	int max_lines = MAX_LINES;
	char buf[BUFFER_SIZE] = {'\0'};
	char *buf_ptr = NULL;


	if(argc>1)
	{
		ifile= fopen(argv[1], "r");
		if(ifile==NULL)
		{
			fprintf(stderr, "could not open file: %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}
	if(argc>2)
	{
	//	max_lines = atoi(argv[2]);
	//	max_lines = strtoi(argv[2], NULL, 10);
		sscanf(argv[2], "%d", &max_lines);
		if(max_lines <= 0)
		{
			max_lines = MAX_LINES;
		}
	}



	buf_ptr = fgets(buf, BUFFER_SIZE, ifile);
	line_count++;
	while((line_count <= max_lines) && (buf_ptr != NULL))
	{
		printf("%s", buf);
		buf_ptr = fgets(buf, BUFFER_SIZE, ifile);
		line_count++;

	}

	if(argc >1)
	{
		fclose(ifile);
	}
	return EXIT_SUCCESS;
}
