#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

static void trie_display_helper(TrieNode *curr, char *prefix);
static TrieNode* trie_node_create(void);

static TrieNode* trie_node_create(void) {
    return calloc(1, sizeof(TrieNode));
}

Trie* trie_init(void) {
    Trie *trie = malloc(sizeof(Trie));
    trie->root = trie_node_create();
    return trie;
}

/* Return true if word is inserted successfully */
int trie_insert(Trie *t, const char *word) {
    TrieNode *curr = t->root;
    for(int i = 0; i < strlen(word); i++) {
        /* Check for invalid character */
        if(word[i] < CHAR_MIN || word[i] > CHAR_MAX) {
            return 0;
        }

        /* Create new prefix path if it doesn't exist yet */
        if(!curr->chars[word[i] - CHAR_MIN]) {
            curr->chars[word[i] - CHAR_MIN] = trie_node_create();
        } 
        curr = curr->chars[word[i] - CHAR_MIN];
    }

    curr->is_terminal = 1; /* curr is the end of the word, so make it a terminal node */
    return 1;
}

/* Prints the structure of the tree to stdout */
/* Words are marked with an asterisk */
void trie_display(Trie *t) {
    /* DFS for each index of the current node's array */
    TrieNode *curr = t->root;
    trie_display_helper(curr, "");
}

static void trie_display_helper(TrieNode *curr, char *prefix) {
    /* Print word */
    for(int i = 0; i < strlen(prefix); i++) {
        printf("  ");
    }
    if(curr->is_terminal) {
        printf("*%s*\n", prefix);
    } else {
        printf("%s\n", prefix);
    }

    /* Loop through each character pointer */
    for(int i = 0; i < NUM_CHARS; i++) {
        if(curr->chars[i]) {
            char c_to_str[2];
            c_to_str[1] = '\0';
            c_to_str[0] = CHAR_MIN + i;

            char new_prefix[strlen(prefix) + 2];
            new_prefix[0] = '\0';
            strcat(new_prefix, prefix);
            strcat(new_prefix, c_to_str);
            trie_display_helper(curr->chars[i], new_prefix);
        }
        
    }
}


