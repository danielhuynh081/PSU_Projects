#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define OPTIONS "k:h" // Option strings for getopt

int main(int argc, char *argv[]) {
  ssize_t bytes = {0};
char buffer[BUF_SIZE] = {0};    
    size_t key_length = {0};
    char * key = "Xerographic";
    unsigned keyi=0;

    // Parse command line arguments
    int opt = 0;            
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'k': // Key
                key = optarg;   
                break;
            case 'h': // Help command
                printf("Usage: ./xor -k <key>\n");
                exit(EXIT_SUCCESS);
                break;
            default:
                fprintf(stderr, "Error processing an option\n");
                exit(EXIT_FAILURE);
                break;
        }               
    }                       

    key_length = strlen(key); // Get the length of the key

    while((bytes = read(STDIN_FILENO, buffer, BUF_SIZE))>0 ){
	    for (int i = 0; i < bytes; ++i, keyi=(keyi+1) % key_length) {
		    buffer[i] ^= key[keyi];
	    }
	    write(STDOUT_FILENO, buffer, bytes);
    }
   memset(buffer, 0, BUF_SIZE);
   key = NULL;


    return 0;                       
}

