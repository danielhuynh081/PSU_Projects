// Daniel Huynh, CS333, Jesse Chaney
// This program encrypts and decrypts text using a Caesar cipher with configurable command-line options.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Define Macros
#define BUF_SIZE 1024
#define MIN_SHIFT 0
#define MAX_SHIFT 95
#define BASE 32
#define OPTIONS "eds:h"

//Main
int main(int argc, char *argv[]) {
	//Define Variables
	int shift = 3;
	int doDecrypt = 0;
	char buffer[BUF_SIZE] = {0};
	int opt = 0;            

	//Handle Commands
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
			case 'e': // Encrypt option
				doDecrypt = 0;
				break;
			case 'd': // Decrypt option
				doDecrypt = 1;
				break;
			case 's': // Set shift option
				shift = atoi(optarg);
				//Check Shift Range
				if (shift < MIN_SHIFT || shift > MAX_SHIFT) {
					printf("Error: Shift must be between 0 and 95\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'h': // Help option
				printf("\nUsage: ./caesar (-e | -d) (-s shift) (-h) (< textfile.txt | Keyboard input)\n");
				printf(" -e: Encrypt input\n");
				printf(" -d: Decrypt input\n");
				printf(" -s shift: Set shift amount (default 3)\n");
				printf(" -h: help message\n");
				exit(EXIT_SUCCESS);
				break;
			default:
				printf("Error processing an option\n");
				exit(EXIT_FAILURE);
				break;
		}
	}

	//Process user input
	while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
		if (doDecrypt) {
			//Decrypt Shift
			for (int i = 0; buffer[i] != '\0'; ++i) {
				if (buffer[i] >= 32 && buffer[i] <= 126) {  // Check for printable ASCII Range
					buffer[i] = (buffer[i] - BASE - shift + MAX_SHIFT) % MAX_SHIFT + BASE; 
				}
			}
			fprintf(stdout, "%s", buffer);
		} else {
			//Encrypt Shift
			for (int i = 0; buffer[i] != '\0'; ++i) {
				if (buffer[i] >= 32 && buffer[i] <= 126) {  // Check for printable ASCII Range
					buffer[i] = (buffer[i] - BASE + shift) % MAX_SHIFT + BASE;
				}
			}
			fprintf(stdout, "%s", buffer);
		}
	}

	return 0;
}

