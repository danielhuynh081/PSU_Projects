CXX=g++
CFLAGS=-g
WFLAGS= -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wextra -Wpedantic -Werror
SFLAGS= -std=c++17
PROG = main

all: $(PROG)

$(PROG): main.o members.o treebuild.o
	$(CXX) $(SFLAGS) $(WFLAGS) $(CFLAGS) -o $(PROG) main.o members.o treebuild.o

main.o: main.cpp class.h
	$(CXX) $(SFLAGS) $(WFLAGS) $(CFLAGS) -c main.cpp

members.o: members.cpp class.h
	$(CXX) $(SFLAGS) $(WFLAGS) $(CFLAGS) -c members.cpp

treebuild.o: treebuild.cpp class.h
	$(CXX) $(SFLAGS) $(WFLAGS) $(CFLAGS) -c treebuild.cpp

clean: 
	rm -f $(PROG) * .o *~ \#*

