/**
 * This file (unsorted.c) is an implementation for the set data type.
 * A similar file exists (sorted.c) that implements this set but also sorts the elements as they are added.
 * The set data type guarantees no duplicate elements.
 * This implementation decreases the time complexity of adding values by simply appending elements to the end of the array.
 * This implementation forces sequential searches for values.
 * However, this implementation has O(N) or better time complexity on all functions.
 *
 * @author Max Blennemann
 * @version 9/25/23
 */

#include "set.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct set {
    char **data;
    unsigned int count;         // Number of elements that contain data
    unsigned int size;   // How much space is allocated to the array
} unsortedSet;

/**
 * Returns a new set with the specified number of elements as the maximum capacity.
 *
 * @param maxElts the maximum amount of elements the set can hold
 * @return the newly allocated set
 * @timeComplexity O(N)
 */
SET *createSet(int maxElts) {
    unsortedSet *a = malloc(sizeof(unsortedSet));
    a->count = 0;
    a->size = maxElts;
    a->data = malloc(maxElts * sizeof(char *));
    return a;
}

/**
 * Frees the memory allocated to the set.
 *
 * @param sp the set to destroy
 * @timeComplexity O(N)
 */
void destroySet(SET *sp) {
    assert(sp != NULL);
    int i = 0;
    for (; i < sp->count; i++)
        free(sp->data[i]);
    free(sp->data);
}

/**
 * Returns the number of elements in the set
 *
 * @param sp the set to access
 * @return the number of unique elements
 * @timeComplexity O(1)
 */
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

/**
 * Adds a new element to the set
 *
 * @param sp the set to add an element to
 * @param elt the element to add.
 * @timeComplexity O(N)
 */
void addElement(SET *sp, char *elt) {
    assert(sp != NULL);
    if (!(sp->count >= sp->size || findElement(sp, elt) != NULL)) {
        sp->data[sp->count] = strdup(elt);
        sp->count++;
    }
}

/**
 * This method removes an element from the give set.
 * Will silently fail if the element does not exist in the set.
 *
 * @param sp the set to remove the element from
 * @param elt the element to remove
 * @timeComplexity O(N)
 */
void removeElement(SET *sp, char *elt) {
    assert(sp != NULL);
    int i = 0;
    for (; i < sp->count; i++) {
        if (strcmp(sp->data[i], elt) == 0) {
            free(sp->data[i]);
            sp->data[i] = sp->data[sp->count-1];
            sp->count--;
            return;
        }
    }
}

/**
 * Checks if the specified element is in the array.
 * Returns a pointer to the element in the array or returns NULL if the element is not in the array.
 *
 * @param sp the set to search through
 * @param elt the element to search for
 * @return a pointer to the element if it exists, otherwise NULL
 * @timeComplexity O(N)
 */
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL);
    int i = 0;
    for (; i < sp->count; i++) {
        if (strcmp(sp->data[i], elt) == 0) {
            return sp->data[i];
        }
    }
    return NULL;
}

/**
 * Copies all the values in the set to a new array and returns that new array.
 * The user must free the array of strings before exiting to avoid a memory leak.
 * The array returned from this method will be sorted according to the order the strings were first added to the set.
 * The first string added to the set will appear at index 0 in the array. (Unless removed.)
 *
 * @param sp The set to access
 * @return A new array of strings
 * @timeComplexity O(N)
 */
char **getElements(SET *sp) {
    assert(sp != NULL);
    char **toReturn = malloc(sp->count * sizeof(char *));
    int i = 0;
    for (; i < sp->count; i++) {
        toReturn[i] = strdup(sp->data[i]);
    }
    return toReturn;
}