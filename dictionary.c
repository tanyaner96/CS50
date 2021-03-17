// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table (initially 1)
const unsigned int N = 26;

// Hash table
node *table[N];

// Hash value
unsigned int hash_val;

// Word count
unsigned int word_count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // return true if word in dictionary and false otherwise
    // should be case insensitive
    // hash word to obtain hash value
    // access linked list at that index to in the hash table
    // look for word in linked list (strcasecmp) - compares two string case insensitively
    
    hash_val = hash(word);
    node *cursor = table[hash_val];
    
    while (cursor != NULL)
    {
        //check if word is in the dictionary
        if (strcasecmp(word, cursor->word))
        {
            return true;
        }
        
        cursor = cursor->next;
    
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    //Take as input a word with alphabetical letters and possibly aprostophes
    //Output numerical value between 0 - N-1 (inclusive) (N be default is 1 but should set to something larger so that hash table got more buckets and speed up search time)
    //Deterministic (same input should yield same output each time)
    //If function ends up with a value greater than N, % N can be used to get a value within the appropes range.
    // hash from http://www.cse.yorku.ca/~oz/hash.html
    
    // Source: djib2 by Dan Bernstein (https://stackoverflow.com/questions/7666509/hash-function-for-string)
    
    unsigned long hash = 5381;
    int c;
    
    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
            

    return hash % N;
    
    //return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //Open dictionary file
    //Read strings from file one at a time
    //Create new node for each word
    //Hash word to obtain hash value
    //Insert node into hash table at that value 
    
    FILE *file = fopen(dictionary, "r");
    
    if (file == NULL)
    {
        return false;
    }
    
    
    char word[LENGTH + 1];
    
    if (file != NULL)
    {
        while (fscanf(file, "%s", word) != EOF)//while fscaf is not EOF 
        {
            //malloc
            node *n = malloc(sizeof(node)); 
            //check if null 
            if (n == NULL)
            {
                return false;
            }
        
            else
            {
                //strcpy the word into node
                strcpy(n->word, word);
                
                //hash the node TODO
                hash_val = hash(word);
                n->next = table[hash_val];
                table[hash_val] = n;
                word_count = word_count + 1;
                
            }
        fclose(file);
        
        }
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count;
    }
    
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // call free on any memory allocated
    
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        
        while (cursor != NULL)
        {
            node *tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
        
        if (cursor == NULL)
        {
            return true;
        }
    }
     
    
    
    return false;
}
