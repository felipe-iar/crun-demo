#include <stdio.h>

/* 
  __AS_BOUNDS__ is here only used to guard the usage of the #pragma to make sure it's
  only used when bounds checking is enabled/present to enhance portability.  
  (__AS_BOUNDS__ is defined by the compiler when bounds checking is enabled.)
*/
#ifdef __AS_BOUNDS__
#pragma default_no_bounds=on
#endif
#include "IntMax.h"
#ifdef __AS_BOUNDS__
#pragma default_no_bounds=off
#endif

unsigned int array[10] = {1,3,5,7,11,0,8,6,4,2};

void main(void)
{
  unsigned int* ap = 0;
  ap = maxIntArrayLibrary(array,10);
  // If "Check pointers from non-instrumented functions" is set, the *ap access 
  // below generates a C-RUN error if we do not give ap new bounds. The function definition tells us the expected 
  // bounds for the return value, so we can use __as_make_bounds() to give ap sensible bounds.
  // EXAMPLE_CHECK_POINTERS is only defined for the "CheckPointersFromNonInstrumentedCode" build configuration
#ifdef EXAMPLE_CHECK_POINTERS
  ap =  __as_make_bounds(ap,1);  /* As long as we do no arithmetic on this pointer  or treat it like an array it's OK with size=1 */
#endif
  printf("Max value from array: %i \n",*ap);
  
  ap = maxIntArrayLibrary(exampleLibraryArray,10);
  // If "Check pointers from non-instrumented functions" is set, the *ap access 
  // below generates a C-RUN error, unless bounds are set with __as_make_bounds(). 
  // The function definition tells us the expected 
  // bounds for the return value, so we can use the following: 
#ifdef EXAMPLE_CHECK_POINTERS
  ap =  __as_make_bounds(ap,1); 
#endif
  printf("Max value from exampleLibraryArray: %i \n",*ap); // OK
  // The following access is out of bounds, since we set a size of one for the bound...
  // If "Check pointers from non-instrumented functions" is not set, we get no error.
  printf("Another value from exampleLibraryArray: %i \n",*(ap+1)); 
  
  // extLibrary_p is an external pointer without bounds. If "Check pointers from non-instrumented memory"
  // is set, the access in printf() will generate an error.
  // If we know the expected range for extLibrary_p, we can give it sensible bounds with __as_make_bounds
#ifdef EXAMPLE_CHECK_POINTERS
  // We know that extLibrary_p points somewhere in the exampleLibraryArray, so
  // we can give the pointer bounds reflecting that in case we want to access something before or after 
  // the current pointer without bounds errors. This variant of __as_make_bounds could of course have been 
  // used also for the previous locations.
  extLibrary_p = __as_make_bounds(extLibrary_p,exampleLibraryArray,exampleLibraryArray+9); 
#endif
  printf("Sample value from externally non-bounds-checked array: %i \n",*extLibrary_p);

}

