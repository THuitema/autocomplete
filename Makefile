CC=gcc
CFLAGS= -Wall -Wextra -pedantic -ggdb -g
TARGETS = autocomplete tests

all: $(TARGETS)

autocomplete: autocomplete.o trie.o
	$(CC) $(CFLAGS) -o autocomplete autocomplete.o trie.o

tests: tests.o trie.o
	$(CC) $(CFLAGS) -o tests tests.o trie.o

tests.o: tests.c trie.h
	$(CC) $(CFLAGS) -c tests.c

autocomplete.o: autocomplete.c
	$(CC) $(CFLAGS) -c autocomplete.c

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c