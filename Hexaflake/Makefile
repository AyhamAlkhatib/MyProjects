CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -I/opt/homebrew/Cellar/sfml/2.6.0/include -I/opt/homebrew/Cellar/boost/1.82.0_1/include -g
LIB =  -L/opt/homebrew/cellar/sfml/2.6.0/lib -L/opt/homebrew/Cellar/boost/1.82.0_1/lib  -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = hexa.hpp
# Your compiled .o files
OBJECTS = hexa.o
# The name of your program
PROGRAM = Hexa

.PHONY: all clean lint

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

Test: Test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp
