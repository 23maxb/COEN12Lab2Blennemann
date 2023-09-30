

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unsorted.c"


/* This is sufficient for the test cases in /scratch/coen12. */

# define MAX_SIZE 18000

int main(int argc, char* argv[]) {
    unsortedSet a = *createSet(26);
    addElement(&a, "d");
    addElement(&a, "a");
    addElement(&a, "b");
    addElement(&a, "a");
    addElement(&a, "b");
    addElement(&a, "a");
    addElement(&a, "b");
    addElement(&a, "a");
    printf("\n\n\n");
    for (int i = 0; i < a.count; i++)
        printf("%s\n", a.data[i]);
    printf("%i", a.count);
    destroySet(&a);
    exit(EXIT_SUCCESS);
}