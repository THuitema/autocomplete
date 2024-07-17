#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

static TrieNode* trie_node_create(void);
static void trie_display_helper(TrieNode *curr, char *prefix);
static int trie_delete_word_helper(TrieNode *curr, const char *word);
static void trie_node_delete(TrieNode *t);
static TrieNode* trie_get_prefix(Trie *t, const char *prefix);

/*
Returns a pointer to a new TrieNode with is_terminal set to false
Time complexity: O(1)
*/
static TrieNode* trie_node_create(void) {
    return calloc(1, sizeof(TrieNode));
}

/*
Free the memory associated with the given TrieNode
*/
static void trie_node_delete(TrieNode *t) {
    free(t);
}

/*
Returns a pointer to a Trie with its root initialized
Time complexity: O(1)
*/
Trie* trie_init(void) {
    Trie *trie = malloc(sizeof(Trie));
    trie->root = trie_node_create();
    trie->root->is_root = 1;
    return trie;
}

/*
Inserts word into trie
Returns true if word is inserted successfully, false otherwise
Time complexity: O(N) where N is the length of the word being inserted
*/
int trie_insert(Trie *t, const char *word) {
    /* Check for valid parameters */
    if(!t || !word) {
        return 0;
    }

    TrieNode *curr = t->root;
    for(int curr_char = 0; curr_char < strlen(word); curr_char++) {
        /* Check for invalid character in word */
        if(word[curr_char] < CHAR_MIN || word[curr_char] > CHAR_MAX) {
            return 0;
        }

        /* Create new prefix path if it doesn't exist yet */
        if(!curr->chars[word[curr_char] - CHAR_MIN]) {
            curr->chars[word[curr_char] - CHAR_MIN] = trie_node_create();
        } 
        curr = curr->chars[word[curr_char] - CHAR_MIN];
    }

    curr->is_terminal = 1; /* curr is the end of the word, so make it a terminal node */
    return 1;
}

/* 
Prints the structure of the trie to stdout 
Words (is_terminal is true) are marked with an asterisk 
Time compexity: O(N) where N is the number of prefixes or nodes in the trie
*/
void trie_display(Trie *t) {
    if(t) {
        TrieNode *curr = t->root;
        trie_display_helper(curr, "");
    }
}

/*
Helper function for trie_display()
Prints the prefix at curr 
Performs depth-first search on each child pointer
*/
static void trie_display_helper(TrieNode *curr, char *prefix) {
    /* Print word, indent based on which layer of the tree the current node is */
    for(int i = 1; i < strlen(prefix); i++) {
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
            /* Append current char to prefix*/
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

/*
Returns a pointer to the TrieNode at prefix.
If prefix isn't in the trie, NULL is returned
*/
static TrieNode* trie_get_prefix(Trie *t, const char *prefix) {
    if(!t || !prefix) {
        return NULL;
    }

    TrieNode *curr = t->root;

    for(int curr_char = 0; curr_char < strlen(prefix); curr_char++) {
        /* Check for invalid character in word */
        if(prefix[curr_char] < CHAR_MIN || prefix[curr_char] > CHAR_MAX) {
            return NULL;
        }

        curr = curr->chars[prefix[curr_char] - CHAR_MIN];
        if(!curr) {
            return NULL;
        }
    }

    return curr;
}

/*
Returns 1 if the word exists in the trie, 0 otherwise
*/
int trie_contains_word(Trie *t, const char *word) {
    TrieNode *prefix = trie_get_prefix(t, word);
    return prefix && prefix->is_terminal;
}

/*
Deletes the word from the trie, if it exists
If the word serves as a prefix for other words, the TrieNode is kept and is_terminal is set to 0
If the word has no children, the TrieNode is deleted and 
its ancestors are deleted if the deleted word is their only dependency
*/
void trie_delete_word(Trie *t, const char *word) {
    /* Check for valid parameters */
    if(t && word) {
        trie_delete_word_helper(t->root, word);
    }
}

/*
Helper function for trie_delete_word()
Deletes the ancestor nodes of the word to delete if they have no other children
Returns 1 if the function is done deleting (whether successful or not)
Returns 0 to continue checking if ancestor nodes can be deleted
*/
static int trie_delete_word_helper(TrieNode *curr, const char *word) {
    /* Word is not in the tree */
    if(!curr) { 
        return 1;
    }

    /* At TrieNode to remove */
    if(!strcmp(word, "")) { 
        /* Don't delete if word is actually a prefix */
        if(!curr->is_terminal) {
            return 1;
        }

        curr->is_terminal = 0;

        /* See if it has any children. If not, we can delete the TrieNode */
        for(int i = 0; i < NUM_CHARS; i++) {
            if(curr->chars[i]) {
                return 1;
            }
        }
        trie_node_delete(curr);
        return 0; /* Return 0 to see if we can delete its parent as well*/
    } else {
        /* Check for invalid character in word */
        if(word[0] < CHAR_MIN || word[0] > CHAR_MAX) {
            return 1;
        }

        /* Recursive call */
        if(!trie_delete_word_helper(curr->chars[word[0] - CHAR_MIN], word + 1)) {
            /* Delete the node to remove and its parents while they have no other children */
            curr->chars[word[0] - CHAR_MIN] = NULL;

            /* See if it has any children. If not, we can delete the TrieNode */
            for(int i = 0; i < NUM_CHARS; i++) {
                if(curr->chars[i]) {
                    return 1;
                }
            }

            if(!curr->is_root) { /* Stop deleting if we've reached the root of the trie */
                trie_node_delete(curr);
                return 0;
            }
        } 
        return 1;
    }
}


/*
Prints all words in the trie that start with prefix to standard output
Printed in alphabetical order
*/
void trie_get_words(Trie *t, const char *prefix) {

}
