// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];
unsigned long words = 0;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        unsigned int h = hash(word);

        node *n = malloc(sizeof(node));
        if (n != NULL)
        {
            strcpy(n->word, word);
            n->next = NULL;
        }
        else
        {
            return false;
        }

        if (hashtable[h] != NULL)
        {
            n->next = hashtable[h];
        }

        hashtable[h] = n;

        words++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    return words;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int h = hash(word);
    //node *cursor = malloc(sizeof(node));

    //Convert word to lowercase
    int n = strlen(word);
    char copyword[n + 1];
    copyword[n] = '\0';

    for (int i = 0; i < n; i++)
    {
        copyword[i] = tolower(word[i]);
    }

    if (hashtable[h] != NULL)
    {
        node *cursor = hashtable[h];

        while (cursor != NULL)
        {
            if (strcmp(cursor->word, copyword) == 0)
            {
                return true;
            }

            cursor = cursor->next;
        }
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i <= N; i++)
    {
        node *cursor = hashtable[i];
        node *tmp = NULL;
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        free(cursor);
    }

    return true;
}
