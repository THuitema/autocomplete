/*
Trie Node
    • Array of children nodes (one for each character)
    • Boolean isTerminal (signals if the node is the end of a word, can contain children nodes of which it is a prefix of)
*/
#define NUM_CHARS 26 /* 26 for lowercase alphabet a-z */
#define CHAR_MIN 97 /* 'a' */
#define CHAR_MAX 122 /* 'z' */

typedef struct TrieNode {
    struct TrieNode *chars[NUM_CHARS]; /* character = 'a' + index */
    int is_terminal;
} TrieNode;

typedef struct {
    TrieNode *root;
} Trie;

Trie* trie_init(void);
int trie_insert(Trie *t, const char *word);
void trie_display(Trie *t);
// int trie_contains(Trie *t, const char *word);
// int trie_delete_word(Trie *t, const char *word);
