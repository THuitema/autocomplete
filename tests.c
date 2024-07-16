/*
The purpose of this file is to test the various functions of the program to 
ensure functions work as expected
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

#define SUCCESS 1
#define FAILURE 0

/* Tests trie_init() */
static int test_trie_init(void) {
    Trie *t = trie_init();
    if(!t || !t->root || t->root->is_terminal == 1) {
        return FAILURE;
    }
    return SUCCESS;
}

/* Tests trie_insert() */
static int test_trie_insert(void) {
    Trie *t = trie_init();
    
    /* Test invalid parameters */
    if(trie_insert(NULL, NULL) != 0) {
        return FAILURE;
    }
    /* Test a valid word can be inserted */
    if(trie_insert(t, "a") == 0) {
        return FAILURE;
    }
    TrieNode *a = t->root->chars[0];
    if(!a || !a->is_terminal) {
        return FAILURE;
    }
    
    /* Test that a prefix is not labeled as terminal */
    trie_insert(t, "apple");
    if(a->chars['p' - 'a']->is_terminal == 1) {
        return FAILURE;
    }

    /* Test a word with invalid characters cannot be inserted */
    if(trie_insert(t, "heLLo") != 0) {
        return FAILURE;
    }
}

int main(void) {
    int status = SUCCESS;
    if(test_trie_init() == FAILURE) status = FAILURE;
    if(test_trie_insert() == FAILURE) status = FAILURE;

    if(status == FAILURE) {
        printf("Test(s) failed\n");
        return EXIT_FAILURE;
    }
    printf("All tests passed\n");
    return EXIT_SUCCESS;
}
