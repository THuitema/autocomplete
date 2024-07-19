/*
(1a) User provides txt file as argument when executing program, terms are separated by lines
(1b) Or, prompt user to enter all search terms separated by space
(1b) User begins typing a word
(3) When user presses TAB, there are three possible scenarios:
    (i) Prefix does not match any search terms, any nothing is outputted
    (ii) Prefix matches one search term, and is autocompleted on the same line
    (iii) Prefix matches multiple search terms, and all matches are outputted below the user's cursor (cursor stays on same line)

User can upload textfile as argument when calling program, has option to add more terms manually in shell during running
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"

#define MAX_COMMAND_LENGTH 256
#define MAX_TOKENS 100

static void parse_line(const char *line, char tokens[MAX_TOKENS][MAX_COMMAND_LENGTH + 1], int *num_tokens);
static void execute(Trie *t, char tokens[MAX_TOKENS][MAX_COMMAND_LENGTH + 1], int *num_tokens);

int main(void) {
    Trie *prefix_tree = trie_init();

    char line[MAX_COMMAND_LENGTH + 1] = "";
    char tokens[MAX_TOKENS][MAX_COMMAND_LENGTH + 1] = {""};
    int num_tokens = 0;

    /* Read input from user */
    printf("(autocomplete) "); /* Prompt */
    while(fgets(line, MAX_COMMAND_LENGTH + 1, stdin)) {
        
        parse_line(line, tokens, &num_tokens);
        execute(prefix_tree, tokens, &num_tokens);

        printf("(autocomplete) "); /* Prompt */
    }

    return 0;
}

/*
Tokenizes line, places tokens in tokens[][] and set num_tokens to the number of tokens in line
*/
static void parse_line(const char *line, char tokens[MAX_TOKENS][MAX_COMMAND_LENGTH + 1], int *num_tokens) {
    int curr_token = 0;
    *num_tokens = 0;

    /* Remove \n character from end */
    char *newline = strchr(line, '\n' );
    if(newline) {
        *newline = 0;
    }

    /* Tokenize line */
    char *token = strtok(line, " \r\n");
    while(token) {
        strcpy(tokens[curr_token++], token);
        token = strtok(NULL, " ");
    }
    *num_tokens = curr_token;
}   

/*
Executes the command specified by the user
*/
static void execute(Trie *t, char tokens[MAX_TOKENS][MAX_COMMAND_LENGTH + 1], int *num_tokens) {
    /* Insert to trie */
    if (!strcmp(tokens[0], "add")) {
        for(int token = 1; token < *num_tokens; token++) {
            trie_insert(t, tokens[token]);
        }
    }
    /* Display trie */
    else if (!strcmp(tokens[0], "display")) {
        trie_display(t);
    }

    /* Quit program */
    else if (!strcmp(tokens[0], "quit")) {
        exit(EXIT_SUCCESS);
    }

    /* Invalid Command */
    else {
        printf("Invalid command\n");
    }
}

