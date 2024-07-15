/*
(1a) User provides txt file as argument when executing program, terms are separated by lines
(1b) Or, pwrompt user to enter all search terms separated by space
(1b) User begins typing a word
(3) When user presses TAB, there are three possible scenarios:
    (i) Prefix does not match any search terms, any nothing is outputted
    (ii) Prefix matches one search term, and is autocompleted on the same line
    (iii) Prefix matches multiple search terms, and all matches are outputted below the user's cursor (cursor stays on same line)

User can upload textfile as argument when calling program, has option to add more terms manually in shell during running
*/
#include <stdio.h>
#include "trie.h"



int main(void) {
    Trie *prefix_tree = trie_init();
    trie_insert(prefix_tree, "apple");
    trie_insert(prefix_tree, "app");
    trie_insert(prefix_tree, "appeal");
    trie_insert(prefix_tree, "ale");
    trie_insert(prefix_tree, "always");
    trie_insert(prefix_tree, "a");
    trie_display(prefix_tree);
    return 0;
}
