# Makefile for the wordle game
FLAGS = -pedantic-errors -std=c++11

# main program 
WORDLE_main: main.o 4char.o 5char.o 6char.o 7char.o 8char.o
	g++ $(FLAGS) $^ -o $@

main.o: main.cpp 4char.h 5char.h 6char.h 7char.h 8char.h
	g++ $(FLAGS) -c $<


# list of helper function
4char.o: 4char.cpp 4char.h
	g++ $(FLAGS) -c $<

5char.o: 5char.cpp 5char.h
	g++ $(FLAGS) -c $<

6char.o: 6char.cpp 6char.h
	g++ $(FLAGS) -c $<

7char.o: 7char.cpp 7char.h
	g++ $(FLAGS) -c $<

8char.o: 8char.cpp 8char.h
	g++ $(FLAGS) -c $<



# Full clean command
clean:
	rm -f WORDLE_main main.o 4char.o 5char.o 6char.o 7char.o 8char.o

.PHONY: clean
