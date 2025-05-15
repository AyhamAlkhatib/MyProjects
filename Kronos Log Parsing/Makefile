CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -I/opt/homebrew/Cellar/boost/1.83.0/include -g
LIB =  -L/opt/homebrew/Cellar/boost/1.83.0/lib -lboost_unit_test_framework -lboost_date_time -lboost_regex
# Your .hpp files
DEPS = Kronos.hpp
# Your compiled .o files
OBJECTS = Kronos.o
# The name of your program
PROGRAM = ps7

.PHONY: all ps7 clean lint

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o $(PROGRAM) *.rpt

lint:
	cpplint *.cpp *.hpp
