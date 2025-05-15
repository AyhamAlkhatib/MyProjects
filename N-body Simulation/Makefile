CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -I/opt/homebrew/Cellar/sfml/2.6.0/include -I/opt/homebrew/Cellar/boost/1.82.0_1/include -g
LIB =  -L/opt/homebrew/cellar/sfml/2.6.0/lib -L/opt/homebrew/Cellar/boost/1.82.0_1/lib  -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
DEPS = Universe.hpp CelestialBody.hpp
# Your compiled .o files
OBJECTS = Universe.o CelestialBody.o
# The name of your program
PROGRAM = NBody

.PHONY: all clean lint 

all: $(PROGRAM) test NBody.a

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

NBody.a: $(OBJECTS)
	ar rcs NBody.a CelestialBody.o Universe.o

clean:
	rm *.o $(PROGRAM) test NBody.a


lint:
	cpplint *.cpp *.hpp
