CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -I/opt/homebrew/Cellar/sfml/2.6.0/include -I/opt/homebrew/Cellar/boost/1.82.0_1/include -g
LIB =  -L/opt/homebrew/cellar/sfml/2.6.0/lib -L/opt/homebrew/Cellar/boost/1.82.0_1/lib  -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
DEPS = Sokoban.hpp Matrix.hpp
# Your compiled .o files
OBJECTS = Sokoban.o Matrix.o
# The name of your program
PROGRAM = Sokoban

.PHONY: all clean lint 

all: $(PROGRAM)  Sokoban.a

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

Sokoban.a: $(OBJECTS)
	ar rcs Sokoban.a Sokoban.o Matrix.o

clean:
	rm *.o $(PROGRAM) Sokoban.a
lint:
	cpplint *.cpp *.hpp
