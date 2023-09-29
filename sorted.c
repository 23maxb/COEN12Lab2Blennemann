/**
 * This file (sorted.c) is an implementation for the set data type.
 * A similar file exists (unsorted.c) that implements this set but does not sort the elements as they are added.
 * The set data type guarantees no duplicate elements.
 * This implementation reduces the time complexity of searches for values by sorting the array (from O(N) to O(log(N)))).
 * However, this implementation leads to a O(Nlog(N)) worst case scenario time complexity for the addElement function.
 *
 * @author Max Blennemann
 * @version 9/25/23
 */

#include "set.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct set {
    char **data;
    unsigned int count;         // Number of elements that contain data
    unsigned int size;   // How much space is allocated to the array
} sortedSet;

/**
 * Returns a new set with the specified number of elements as the maximum capacity.
 *
 * @param maxElts the maximum amount of elements the set can hold
 * @return the newly allocated set
 * @timeComplexity O(n)
 */
SET *createSet(int maxElts) { // maxElts should be unsigned but the header file has this variable signed
    sortedSet *a = malloc(sizeof(sortedSet));
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
    free(sp);
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
 * Finds the index of an element in the set.
 * Returns -1 if the element does not exist within the set.
 *
 * @precondition Set is sorted.
 * @param sp the set to search through
 * @param elt the element to search for
 * @return the index where the element is or should be added
 * @timeComplexity O(log(n))
 */
static unsigned int findElementIndex(SET *sp, char *elt, bool *found) {
    assert(sp != NULL);
    if (sp->count == 0)
        return 0;
    unsigned int low = 0;
    unsigned int high = sp->count - 1;
    unsigned int mid = (low + high) / 2;
    while (low <= high) {
        int comparison = strcmp(elt, sp->data[mid]);
        if (comparison < 0)
            high = mid - 1;
        else if (comparison > 0)
            low = mid + 1;
        else {
            return mid;
            found = (bool *) true;
        }
        mid = (low + high) / 2;
    }
    found = false;
    return mid + 1;
}

/**
 * Adds a new element to the set
 * Sorts the list after the element is added to guarantee the set is sorted
 *
 * @param sp the set to add an element to
 * @param elt the element to add.
 * @timeComplexity O(Nlog(N))
 */
void addElement(SET *sp, char *elt) {
    assert(sp != NULL);
    assert(sp->count < sp->size);
    bool a;
    unsigned int indexOfElement = findElementIndex(sp, elt, &a);
    unsigned int i = sp->count;
    for (; i > indexOfElement; i--) {
        sp->data[i] = sp->data[i - 1];
    }
    sp->data[indexOfElement] = strdup(elt);
    sp->count++;
}

/**
 * This method removes an element from the give set.
 * It also shifts all the elements after it forward 1 to speed up future searches.
 * This element keeps the set sorted.
 * This function will silently fail if the string given does not exist.
 *
 * @param sp the set to remove the element from
 * @param elt the element to remove
 * @timeComplexity O(N)
 */
void removeElement(SET *sp, char *elt) {
    assert(sp != NULL);
    unsigned int i = findElementIndex(sp, elt);
    if (strcmp(sp->data[i], elt) != 0)
        return;
    free(sp->data[i]);
    for (; i < sp->count - 1; i++)
        sp->data[i] = sp->data[i + 1];
    sp->count--;
}


/**
 * Finds the element in the set.
 * Returns NULL if the element does not exist within the set.
 *
 * @precondition Set is sorted.
 * @param sp the set to search through
 * @param elt the element to search for
 * @return a pointer to the string in the set if it exists
 * otherwise NULL
 * @timeComplexity O(log(N))
 */
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL);
    unsigned int indexOfElement = findElementIndex(sp, elt, NULL);
    if (strcmp(sp->data[indexOfElement], elt) == 0)
        return NULL;
    else
        return sp->data[indexOfElement];
}

/**
 * Copies all the values in the set to a new array and returns that new array.
 * The user must free the array of strings before exiting to avoid a memory leak.
 * Since this set maintains an array of strings sorted alphabetically this method is guaranteed to
 * return an array of alphabetically sorted strings.
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
