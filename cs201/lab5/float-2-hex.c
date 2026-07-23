#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
// Daniel Huynh, Jesse Chaney CS201
// This program converts float or double values to their hexadecimal representations.

int main(int argc, char *argv[]) {

	bool doublecheck = false;
	float f;
	double d;
	char input[150];
	int opt;
	while((opt = getopt(argc, argv, "f : d : H")) != -1){
		switch(opt)
		{
			case 'f':
				doublecheck = false;
				break;

			case 'd':
				doublecheck = true;
				break;

			case 'H':
				printf(" -f   convert the input into floats for hex output (this is the default)\n");
				printf(" -d   convert the input into doubles for hex output\n");
				printf(" -H   display this help message and exit\n");
				return 0;
			case '?':
				break;
		}
	}
	while (fgets(input, sizeof(input), stdin) != NULL) {

		input[strlen(input) - 1] = '\0';

		if (doublecheck) {
			if (sscanf(input, "%le", &d) != 1) {
				fprintf(stderr, "Failed to scan value from input <%s>\n", input);
				exit(EXIT_FAILURE);
			}
		} else {
			if (sscanf(input, "%f", &f) != 1) {
				fprintf(stderr, "Failed to scan value from input <%s>\n", input);
				exit(EXIT_FAILURE);
			}
		}

		// Print output
		if (doublecheck) {
			printf("%-40s\t%.16le\t%.16lf\t0x%016lx\n", input, d, d, *(long unsigned int* ) &d);
		} else {
			printf("%-40s\t%.10e\t%.10f\t0x%08x\n", input, f, f, *(int*) &f);
		}
	}

	return 0;
}
