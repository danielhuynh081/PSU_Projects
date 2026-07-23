#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gcc -g -Wall -o  front2 front2.c
// ./front3 < front3.c
// ./front3 -f front3.c
// ./front3 -f front3.c -n 3
// ./front3 -n6 -ffront3.c
//
// Daniel Huynh, Jesse Chaney CS201
// This program displays the first specified number of lines using command-line options.

#define BUFFER_SIZE  1024
#define MAX_LINES  5

int main(int argc, char *argv[])
{
	FILE * ifile = stdin;
	int line_count =0;
	int max_lines = MAX_LINES;
	char buf[BUFFER_SIZE] = {'\0'};
	char *buf_ptr = NULL;
	char *file_name = NULL;
	
	int opt =0;

		while ((opt = getopt(argc, argv, "f:n:h")) != -1)
		{
			switch(opt)
			{
				case 'f':
					file_name = optarg;

					ifile= fopen(file_name, "r");
					if(ifile==NULL)
					{
						fprintf(stderr, "could not open file: %s\n", file_name);
						exit(EXIT_FAILURE);
					}
					break;
				case 'n':

				//	max_lines = atoi(optarg);
				//	max_lines = strtoi(optarg, NULL, 10);
					sscanf(optarg, "%d", &max_lines);
					if(max_lines <= 0)
					{
						max_lines = MAX_LINES;
					}
					break;
				case 'h':
					printf("%s [-f file] [-n #] [-h]\n", argv[0]);
					exit(EXIT_SUCCESS);
					break;
				case '?':
					printf("*** eeeek! skipping %c\n", optopt);
					break;
				default:
					exit(EXIT_FAILURE);
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

	if(file_name != NULL)
	{
		fclose(ifile);
	}
	return EXIT_SUCCESS;
}
