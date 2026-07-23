#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "push_pop.h"

// Daniel Huynh, Jesse Chaney CS201
// This program simulates stack push and pop operations using registers and memory.

// The valid commands:
//   status
//   push %reg
//   push $val
//   pop %reg

int is_verbose = 0;
FILE *ofile = NULL;

static unsigned long stack_bot = DEF_STACK_BOT; // the high address for the stack
static unsigned long stack_limit = DEF_STACK_LIMIT; // the low address for the stack
static unsigned long rsp = DEF_RSP; // the initial value for the rsp register
static unsigned long *stack = NULL; // points to the bytes for the stack
static unsigned long registers[REG_RDX + 1] = { // the general purpose registers
												// These are just some default values.
	 REG_RAX + 20
	, REG_RBX + 30
	, REG_RCX + 40
	, REG_RDX + 50
};

static void pop(char *);
static void push_reg(char *);
static void push_value(char *);

static void
pop(char *reg)
{
	if (reg == NULL)
	{
		fprintf(stderr, "\nError: Null argument passed!\n");
		return;
	}

	if (rsp == stack_bot)
	{
		fprintf(stderr, "\nError: Stack is empty!\n");
		return;
	}

	char* token = strtok(reg, " ");
	if (token[0] != '%')
	{
		fprintf(stderr, "\nError: Invalid format of register argument!\n");
		return;
	}

	if (strncmp(token, "%rax", 4) == 0)
	{
		registers[REG_RAX] = stack[(rsp - stack_limit) / 8];
		rsp = rsp + 8;
	}
	else if (strncmp(token, "%rbx", 4) == 0)
	{
		registers[REG_RBX] = stack[(rsp - stack_limit) / 8];
		rsp = rsp + 8;
	}
	else if (strncmp(token, "%rcx", 4) == 0)
	{
		registers[REG_RCX] = stack[(rsp - stack_limit) / 8];
		rsp = rsp + 8;
	}
	else if (strncmp(token, "%rdx", 4) == 0)
	{
		registers[REG_RDX] = stack[(rsp - stack_limit) / 8];
		rsp = rsp + 8;
	}
	else
	{
		fprintf(stderr, "\nError: Invalid format of register argument!\n");
		return;
	}

	fprintf(ofile, "\nPop on register: %s", reg);
}

static void
push_reg(char *reg)
{
	if (reg == NULL)
	{
		fprintf(stderr, "\nError: Null argument passed!\n");
		return;
	}

	if (rsp == stack_limit)
	{
		fprintf(stderr, "\nError: Stack Full!\n");
		return;
	}

	if (strncmp(reg, "%rax", 4) == 0)
	{
		stack[(rsp - stack_limit) / 8] = registers[REG_RAX];
		rsp = rsp - 8;
	}
	else if (strncmp(reg, "%rbx", 4) == 0)
	{
		stack[(rsp - stack_limit) / 8] = registers[REG_RBX];
		rsp = rsp - 8;
	}
	else if (strncmp(reg, "%rcx", 4) == 0)
	{
		stack[(rsp - stack_limit) / 8] = registers[REG_RCX];
		rsp = rsp - 8;
	}
	else if (strncmp(reg, "%rdx", 4) == 0)
	{
		stack[(rsp - stack_limit) / 8] = registers[REG_RDX];
		rsp = rsp - 8;
	}
	else
	{
		fprintf(stderr, "\nError: Invalid format of register argument!\n");
		return;
	}

	fprintf(ofile, "\nPush register: %s on stack", reg);
}

static void
push_value(char *reg)
{
	if (reg == NULL)
	{
		fprintf(stderr, "\nError: Null argument passed!\n");
		return;
	}

	if (rsp == stack_limit)
	{
		fprintf(stderr, "\nError: Stack Full!\n");
		return;
	}

	char *ptr, temp[20];
	int i = 1;
	for (; i < 20 && i < strlen(reg); i++)
	{
		temp[i - 1] = reg[i];
	}
	temp[i] = '\0';

	// if(token[1]=='0' && token[2] == 'x')
	{
		stack[(rsp - stack_limit) / 8] = strtol(temp, &ptr, 16);
		rsp = rsp - 8;
	}
	fprintf(ofile, "\nPush value: %s on stack", reg);
}

int
main(int argc, char *argv[])
{
	FILE *ifile = stdin;

	ofile = stdout;
	int flag = 0;
	char bottom[20];
	char limit[20];
	char beginning[20], *ptr;

	{
		int opt = 0;
		int res_count = 0;

		// Do not begin processing input until AFTER you have completely
		// processed the command line using getopt() .

		while ((opt = getopt(argc, argv, GETOPT_STRING)) != -1)
		{
			switch (opt)
			{
				// Do not begin processing input until AFTER you have completely
				// processed the command line using getopt() .
				// #error stuff goes in here
			case 'i':
			{
				if ((ifile = fopen(optarg, "r")) == NULL)
				{
					fprintf(stderr, "\nError: could not open file for reading!\n");
					return EXIT_FAILURE;
				}
				break;
			}
			case 'o':
			{
				if ((ofile = fopen(optarg, "w")) == NULL)
				{
					fprintf(stderr, "\nError: could not open file for writing!\n");
					return EXIT_FAILURE;
				}
				break;
			}
			case 'b':
			{
				if (optarg == NULL)
				{
					fprintf(stderr, "\nError: stack bottom missing!\n");
					return EXIT_FAILURE;
				}
				strcpy(bottom, optarg);
				flag++;
				break;
			}
			case 'l':
			{
				if (optarg == NULL)
				{
					fprintf(stderr, "\nError: stack limit missing!\n");
					return EXIT_FAILURE;
				}
				strcpy(limit, optarg);
				flag++;
				break;
			}
			case 's':
			{
				if (optarg == NULL)
				{
					fprintf(stderr, "\nError: stack beginning address not given!\n");
					return EXIT_FAILURE;
				}
				flag++;
				strcpy(beginning, optarg);
				break;
			}
			case 'v':
				is_verbose++;
				break;
			case 'h':
				printf("%s\n\toptions: %s\n", argv[0], GETOPT_STRING);
				printf("\ti: name of input file\n");
				printf("\to: name of output file\n");
				printf("\tb: stack_bottom (high address, as hex)\n");
				printf("\tl: stack limit (low address, as hex)\n");
				printf("\ts: beginning %%rsp value (within the stack, as hex)\n");
				printf("\tv  verbose output\n");
				printf("\th  help\n");

				exit(EXIT_SUCCESS);
				break;
			default:
				break;
			}
		}
	}
	// Do not begin processing input until AFTER you have completely
	// processed the command line using the getopt() loop.

	// Do all the validation of upper and lower bounds down here, NOT
	// within the getopt() loop.

	char line[BUFFER_SIZE];

	if (flag == 3)
	{
		unsigned long longbottom = strtol(bottom, &ptr, 16);
		unsigned long longlimit = strtol(limit, &ptr, 16);
		unsigned long longbeginning = strtol(beginning, &ptr, 16);

		if (longbottom % 8 != 0)
		{
			fprintf(stderr, "\nError: stack_bottom is not multiple of 8!\n");
			return EXIT_FAILURE;
		}

		if (longlimit % 8 != 0)
		{
			fprintf(stderr, "\nError: stack_limit is not multiple of 8!\n");
			return EXIT_FAILURE;
		}

		if (longbeginning % 8 != 0)
		{
			fprintf(stderr, "\nError: stack_beginning is not multiple of 8!\n");
			return EXIT_FAILURE;
		}

		if (longbottom <= longlimit)
		{
			fprintf(stderr, "\nError: stack_bottom lower than stack limit\n");
			return EXIT_FAILURE;
		}

		if (longbeginning <= longlimit || longbeginning >= longbeginning)
		{
			fprintf(stderr, "\nError: stack_beginning out or range\n");
			return EXIT_FAILURE;
		}

		rsp = longbeginning;
		stack_bot = longbottom;
		stack_limit = longlimit;
	}

	stack = (unsigned long*)malloc(((stack_bot - stack_limit) / 8) * sizeof(unsigned long));

	// Have your loop for processing all the input down here.
	while (fgets(line, BUFFER_SIZE, ifile))
	{
		printf("\ncommand: ..%s..", line);
		char* word = strtok(line, " ");
		while (word != NULL)
		{
			if (strncmp(word, "status", 6) == 0)
			{
				stack_status(stack, registers, rsp, stack_bot, stack_limit, ofile);
			}
			else if (strncmp(word, "push", 4) == 0)
			{
				char*reg = strtok(NULL, " ");
				if (reg[0] == '%')
				{
					push_reg(reg);
				}
				else if (reg[0] == '$')
				{
					push_value(reg);
				}
				else
				{
					fprintf(stderr, "\nError: argument format\n");
				}
			}
			else if (strncmp(word, "pop", 3) == 0)
			{
				char*reg = strtok(NULL, " ");
				if (reg[0] != '%')
				{
					fprintf(stderr, "\nError: invalid register name for pop operation\n");
				}
				else
				{
					pop(reg);
				}
				break;
			}
			else if (strncmp(word, "exit", 4) == 0)
			{
				free(stack);
				fclose(ifile);
				fclose(ofile);
				return EXIT_SUCCESS;
			}
			else
			{
				fprintf(stderr, "\nError: invalid command\n");
			}
			word = strtok(NULL, " ");
		}
	}

	free(stack);
	fclose(ifile);
	fclose(ofile);
	return EXIT_SUCCESS;
}
 
