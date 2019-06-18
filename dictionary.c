// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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

typedef struct hash_bucket
{
    node *head, *tail;
    int n_elements;
} HashBucket;

// Represents a hash table
HashBucket hashtable[N];

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
        hashtable[i].head = NULL;
        hashtable[i].tail = NULL;
        hashtable[i].n_elements = 0;
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
    int index = 0;
    while (fscanf(file, "%s", word) != EOF)
    {
        index = hash(word);
        //printf("index: %d\n",index);

        //Extracting Linked List at a given index
        node *list = hashtable[index].head;

        //Creating a node to insert in the Hash Table
        node *node1 = malloc(sizeof(node));

        // copy data to list
        strcpy(node1->word, word);
        node1->next = NULL;

        // list is empty
        if (list == NULL)
        {
            hashtable[index].head = node1;
            hashtable[index].tail = node1;
        }
        // list is not empty
        // adding node to the end
        else
        {
            hashtable[index].tail->next = node1;
            hashtable[index].tail = node1;
        }

        // increment element count
        hashtable[index].n_elements++;

        // reset index
        index = 0;
    }

    // Close dictionary
    fclose(file);

    // Check size
    size();

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int size = 0;
    for (int index = 0; index < N; index++)
    {
        size = hashtable[index].n_elements + size;
    }
    //printf("words: %d\n",size);
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Get hash for the given word
    int index = hash(word);

    node *cursor = hashtable[index].head;
    //const char* text = "abc";
    while (cursor != NULL)
    {
        int value = strcasecmp(word, cursor->word);
        if (value == 0)
        {
            return true;
        }
        cursor = cursor->next;

    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int index = 0; index < N; index++)
    {
        node *cursor = hashtable[index].head;
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
