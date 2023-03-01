/*
  This is a library project built _without_ bounds checking to illustrate the
  use of the "Check pointers from non-instrumented functions" and 
  "Check pointers from non-instrumented memory" options together with the 
  various #pragma directives and intrinsic functions available for more fine 
  grained control.
*/
#include "IntMax.h"

unsigned int exampleLibraryArray[10] = {1,2,3,4,5,6,7,8,9,0};

/*
  If the code using this pointer is built with bounds checking, it must decide 
  if the pointer bounds should be tracked or not in the calling code. By enabling the 
  "Check pointers from non-instrumented memory" option the pointer will be tracked and 
  receive default bounds [0,0] which is probably wrong. To create proper initial bounds,
  use __as_make_bounds()
*/
 unsigned int* extLibrary_p = &exampleLibraryArray[4];


 /* 
  Example function that takes a pointer argument and returns a pointer 
  If the calling code is using bounds checking, it must precede the declaration with 
  #pragma no_bounds

  The calling code must also decide if the bounds of the returned pointer should be 
  tracked or not, by setting or not setting the 
  "Check pointers from non-instrumented functions" option.
  With this option set, the returned pointer will get default bounds [1,0], which is probably wrong, i.e. always give an error, 
  so initial proper bounds must be given with __as_make_bounds()
*/
unsigned int* maxIntArrayLibrary(unsigned int* ap, unsigned int n)
{
  unsigned int* maxp = 0;
  unsigned int max   = 0;
  for (int i=0;i<n;++i)
  {
    if (ap[i] > max)
    {
      maxp = &ap[i];
      max  = ap[i];
    }
  }
  return maxp;
}

