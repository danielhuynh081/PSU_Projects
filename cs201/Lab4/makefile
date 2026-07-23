CC=gcc
CFLAGS=-g
WFLAGS=-Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wextra -Wpedantic -Werror
PROG = push_pop

all: $(PROG)

$(PROG): push_pop.o stack_status.o
	$(CC) $(WFLAGS) $(CFLAGS) -o push_pop push_pop.o stack_status.o

push_pop.o: push_pop.c push_pop.h
	$(CC) $(WFLAGS) $(CFLAGS) -c push_pop.c

stack_status.o: stack_status.c push_pop.h
	$(CC) $(WFLAGS) $(CFLAGS) -c stack_status.c

clean cls:
	rm -f $(PROG) *.o *~ \#* 


