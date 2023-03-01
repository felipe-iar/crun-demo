/* This example demonstrates basic bounds checking functionality */
/* In this case we control  the compilation of all code in the program, so there */ 
/* are no special cases to deal with    */
/* Take a look at IntMax.h/c to see what's exported from IntMax */
#include <stdio.h>
#include <stdlib.h>
#include "IntMax.h"

unsigned int array[10] = {1,3,5,7,11,0,8,6,4,2};

void main(void)
{
  unsigned int *ap = 0;
  char *cp = 0;
  ap = maxIntArrayLibrary(array,10);
  printf("Max value from array: %i \n",*ap);
  
  ap = maxIntArrayLibrary(exampleLibraryArray,10);
  printf("Max value from exampleLibraryArray: %i \n",*ap); // OK
  printf("Some other value from exampleLibraryArray: %i \n",*(ap+1));      // Is this out of bounds?
  printf("And yet another value from exampleLibraryArray: %i \n",*(ap+2)); // Is this out of bounds?
  
  /* This is a pointer access through another pointer. Such indirect access requires a slot in the 
     bounds table. Note that the size of the bounds table should be set by the user. Default size is 4k slots 
     which is probably too many, by far!    */
  printf("Sample value from exampleLibraryArray accessed through another pointer: %i \n",*extLibrary_p);

  cp = malloc(10);
  cp[10] = 'A';
}







