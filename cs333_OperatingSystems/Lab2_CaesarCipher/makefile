CC=gcc
CFLAGS=-g
WFLAGS = -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wextra -Wpedantic -Werror -Wno-return-local-addr -Wunsafe-loop-optimizations -Wuninitialized
PROG = caesar
PROG2 = xor

all: $(PROG) $(PROG2)

$(PROG): $(PROG).o 
	$(CC) $(WFLAGS) $(CFLAGS) -o $(PROG) $(PROG).o -lm

$(PROG).o: $(PROG).c 
	$(CC) $(WFLAGS) $(CFLAGS) -c $(PROG).c 

$(PROG2): $(PROG2).o
	$(CC) $(WFLAGS) $(CFLAGS) -o $(PROG2) $(PROG2).o -lm

$(PROG2).o: $(PROG2).c
	$(CC) $(WFLAGS) $(CFLAGS) -c $(PROG2).c 


clean cls:
	rm -f $(PROG) $(PROG2) *.o *~ \#* 
