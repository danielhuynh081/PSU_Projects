CC=gcc
CFLAGS=-g
WFLAGS = -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wextra -Wpedantic -Werror -Wno-return-local-addr -Wunsafe-loop-optimizations -Wuninitialized 
PROG = thread_hash
PROGS = $(PROG)

all: $(PROGS)

$(PROG): $(PROG).o 
	$(CC) $(WFLAGS) $(CFLAGS) -o $@ $^ -lcrypt -pthread

$(PROG).o: $(PROG).c #$(INCLUDES) 
	$(CC) $(WFLAGS) $(CFLAGS) -c $<


clean cls:
	rm -f $(PROGS) *.o *~ \#* 
tar: 
	tar cvfa Lab5_${LOGNAME}.tar.gz *.[ch] [mM]akefile
