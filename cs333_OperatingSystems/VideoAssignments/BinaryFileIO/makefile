CC=gcc
CFLAGS=-g
WFLAGS = -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wextra -Wpedantic -Werror -Wno-return-local-addr -Wunsafe-loop-optimizations -Wuninitialized
PROG = bin_write
PROG2 = bin_cat
PROG3 = bin_update
PROG4 = bin_add
PROGS = $(PROG) $(PROG2) $(PROG3) $(PROG4)
INCLUDES = bin_file.h

all: $(PROGS)

$(PROG): $(PROG).o 
	$(CC) $(WFLAGS) $(CFLAGS) -o $@ $^

$(PROG).o: $(PROG).c $(INCLUDES)
	$(CC) $(WFLAGS) $(CFLAGS) -c $<

$(PROG2): $(PROG2).o
	        $(CC) $(WFLAGS) $(CFLAGS) -o $@ $^

$(PROG2).o: $(PROG2).c $(INCLUDES)
	        $(CC) $(WFLAGS) $(CFLAGS) -c $<

$(PROG3): $(PROG3).o
	                $(CC) $(WFLAGS) $(CFLAGS) -o $@ $^

$(PROG3).o: $(PROG3).c $(INCLUDES)
	                $(CC) $(WFLAGS) $(CFLAGS) -c $<


$(PROG4): $(PROG4).o
	                        $(CC) $(WFLAGS) $(CFLAGS) -o $@ $^

$(PROG4).o: $(PROG4).c $(INCLUDES)
	                        $(CC) $(WFLAGS) $(CFLAGS) -c $<


clean cls:
	rm -f $(PROGS) *.o *~ \#* 
tar: 
	tar cvfa bin_files_${LOGNAME}.tar.gz *.[ch] [mM]akefile
