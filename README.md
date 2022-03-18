# IString
IString is a library designed to improve the functionality of strings in C.

The standard string library is quite bad when it comes to quality of life and security
of handling strings. This library is geared towards my personal tastes and use cases 
so it may not be ideal for everyone. 

This library is heavily untested, unfinished, and in active development, so use at your own risk. If you have any suggestions,
or encounter any issues, please be sure to open an issue on this repo. 

To see examples of how to use this library and its features, please refer to `test.c`.
In order to use this in a project, you have to include the `istr.h` header and define `ISTR_IMPLEMENT` before the inclusion. 
```
#define ISTR_IMPLEMENT
#include "istr.h"
```
The library is implemented in a single header and in order to make sure the all definitions are included once (removing any issues from multiple definitions), 
the macro must be defined in a SINGLE source file. 

## Notes
- The `istr` struct members (`s` and `len`) are currently constant to prevent unintended modification and uses.
This presents an issue in there is no way to modify/reassign the value of an istring, and thus a new one must be
created for such uses (i.e. istr_cat). While having constant values is a good safety mechanism, if it impedes the 
usability of this library, it will be altered so feedback is appreciated. 
- The error handling currently implemented in IString (which is only to prevent improper allocations at the moment) is
is not final. I am currently unsure of how I'm going to handle them going forward, so this is just a stand-in. 
- Currently the library is implemented as a single header library, meaning all you need to do to use it is include the
header in your project and define the implementation macro in a single file. This is done for ease of packaging and 
integration; if any issues or grievances arise from this, please let me know. 
