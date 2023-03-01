/*
   Header file for example library. This header simply exposes the elements from 
   the library that we want to use, i.e. an array, a function that takes and returns a 
   pointer, and an ordinary pointer. These elements are enough to show the techniques 
   and tradeoffs available when doing bounds check on projects where not all code 
   can be compiled (or changed). Note that there are no traces of bounds checking 
   or associated #pragma directives in this file.
*/

#ifndef _IntMax_
#define _IntMax_
extern unsigned int exampleLibraryArray[10];

extern unsigned int* maxIntArrayLibrary(unsigned int* ap, unsigned int n); // Returns pointer to max value in array

extern unsigned int* extLibrary_p; // Points somewhere into the exampleLibraryArray...
#endif
