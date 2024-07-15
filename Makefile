CC=gcc
CFLAGS= -Wall -Wextra -pedantic -ggdb -g

autocomplete: autocomplete.o trie.o
	$(CC) $(CFLAGS) -o autocomplete autocomplete.o trie.o

autocomplete.o: autocomplete.c
	$(CC) $(CFLAGS) -c autocomplete.c

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c