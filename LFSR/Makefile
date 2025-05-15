
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -I/opt/homebrew/Cellar/sfml/2.6.0/include -I/opt/homebrew/Cellar/boost/1.83.0/include -g
LIB =  -L/opt/homebrew/cellar/sfml/2.6.0/lib -L/opt/homebrew/Cellar/boost/1.83.0/lib  -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = FibLFSR.hpp 
# Your compiled .o files
OBJECTS = FibLFSR.o 
# The name of your program
PROGRAM = PhotoMagic

.PHONY: all clean lint

all: $(PROGRAM) test PhotoMagic.a

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

PhotoMagic.a: $(OBJECTS)
	ar rcs PhotoMagic.a FibLFSR.o

clean:
	rm *.o test $(PROGRAM)

lint:
	cpplint *.cpp *.hpp