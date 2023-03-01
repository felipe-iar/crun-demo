
Readme for Boundscheck example with "third party" code
======================================================

This example shows how library code or "third party" code that cannot be changed 
can be handled when doing bounds check on the code calling the library. The issue 
we have to solve is the fact that the function signatures (for functions with 
pointers in the parameter list or as return value) and runtime pointer 
representation is changed when bounds check is enabled, which means that bounds-checked
code and non-checked code cannot be linked together without special measures if pointers 
pass between checked and un-checked code.

The example project consists of two build configurations corresponding to case 1 and case 2
described below.

The IntMax library code is built without any boundschecking and is not affected in any way
by the "main" project.

Note that the project also includes its own version of "ReportCheckFailedStdout.c" as an example of
tailored output without debugger support. Enable the file in the build and make sure you enable 
"extra options" for the linker. (The linker option is already present, but not active.)

Two cases (slightly simplified)
===============================
In general, one must inform the compiler (and linker) that functions in the 
library code does not have bounds check information. This is most simply done 
with a few compiler #pragmas, where #pragma default_no_bounds=on/off is the 
most simple one to use. It turns off (or on, but note the inverted 
meaning of the pragma name) the generation of bounds check information for all function
declarations following the #pragma, up until it is turned on again. So this is a convenient way
to deal with included header files. 
If wanted, the use of #pragmas can be guarded by the compiler-predefined symbol __AS_BOUNDS__.
The symbol __AS_BOUNDS__ is only active when bounds checking is enabled for the project.

There are other #pragmas for e.g. turning off bounds info for only the following 
function declaration etc. In the following we assume that all library function
declarations are preceded by one of the #pragmas above.

Case 1
======
This case corresponds to the build configuration "DoNotCheckPointersFromNonInstrumentedCode"
in project "Boundchecking_2".
Turning off bounds check info for library headers will in most cases work very well;
returned pointers will be bounds checked but will have associated bounds that are always "big enough".
This means that pointers originating in your code will be checked, but not pointers from 
the library. This might be perfectly acceptable and is non-intrusive in terms of code changes.
For this case there is no need to do anything more.
(There's a few special situations that might have to be handled otherwise; 
#pragmas and options are decsribed in the C-SPY debugging guide.)

Case 2
======
This case corresponds to the build configuration "CheckPointersFromNonInstrumentedCode"
in project "Boundchecking_2". See note about EXAMPLE_CHECK_POINTERS below.
Sometimes it is desirable to have bounds checking in your code also for pointers
defined in library code and functions returning pointers from library code. To get 
bounds checking for such pointers, you must enable the 
"Check pointers from non-instrumented functions" and/or 
"Check pointers from non-instrumented memory" options.

In such a case the returned pointer must be given sensible 
bounds by using __as_make_bounds() and maybe the associated functions __as_get_base() and
as_get_bounds(). If they are not given bounds with __as_make_bounds() you will get
a bounds error on the first access to the pointer, since the default range for such
pointers are [1,0] or similar to make it obvious that you need to supply a valid range.

Note that this build configuration defines a symbol called EXAMPLE_CHECK_POINTERS that is used to 
conditionally compile in the __as_make_bounds() calls to give pointers sensible bounds.

(Case 3)
========
There is a third case that we do not cover with this example: Non-bounds-checked code that calls a 
function in bounds-checked code that includes a pointer in its signature. In most cases this can be 
dealt with by enabling the "Generate functions callable from non-instrumented code" option
or using #pragma generate_entry_without_bounds for a single function.


