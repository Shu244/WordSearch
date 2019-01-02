# Hw3 Makefile

CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra

#all: word_search run clean

#runs executable
#run: test
#	./test

#.PHONEY: all run

# Links together files needed to create executable
word_search: word_search.o search_functions.o
	$(CC) -o word_search word_search.o search_functions.o

#Runs executable call test_execute 
test: test_execute
	./test

.PHONEY: test

#Links together files needed to create executable
test_execute: test_search_functions.o search_functions.o
	$(CC) -o test test_search_functions.o search_functions.o

# Compiles word_search.c to create word_search.o
word_search.o: word_search.c search_functions.h
	$(CC) $(CFLAGS) -c word_search.c

#Compiles test_word_search.c to create test_word_search.o
test_search_functions.o: test_search_functions.c search_functions.h
	$(CC) $(CFLAGS) -c test_search_functions.c

# Compiles search_functions.c to create search_functions.o
search_functions.o: search_functions.c search_functions.h
	$(CC) $(CFLAGS) -c search_functions.c

# Removes all object files and the executable with .o extension,
# so the directory doesn't get crowded
clean:
	rm -f *.o word_search test 


