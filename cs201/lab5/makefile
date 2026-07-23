CC=gcc
CFLAGS=-g
WFLAGS = -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wextra -Wpedantic -Werror
PROG = float-2-hex
PROG2 = hex-2-float

all: $(PROG) $(PROG2)

$(PROG): float-2-hex.o 
	$(CC) $(WFLAGS) $(CFLAGS) -o float-2-hex float-2-hex.o -lm

float-2-hex.o: float-2-hex.c 
	$(CC) $(WFLAGS) $(CFLAGS) -c float-2-hex.c 

$(PROG2): hex-2-float.o
	$(CC) $(WFLAGS) $(CFLAGS) -o hex-2-float hex-2-float.o -lm

hex-2-float.o: hex-2-float.c
	$(CC) $(WFLAGS) $(CFLAGS) -c hex-2-float.c 


clean cls:
	rm -f $(PROG) $(PROG2) *.o *~ \#* 
