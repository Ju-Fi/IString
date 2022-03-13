# IString
IString is a library designed to improve the functionality of strings in C.

The standard string library is quite bad when it comes to quality of life and security
of handling strings. This library is geared towards my personal tastes and use cases 
so it may not be ideal for everyone. 

This library is heavily untested, unfinished, and in active development, so use at your own risk. If you have any suggestions,
or encounter any issues, please be sure to open an issue on this repo. 

To see examples of how to use this library and its features, please refer to `test.c`.

## Notes
- The `istr` struct members (`s` and `len`) are currently constant to prevent unintended modification and uses.
This presents an issue in there is no way to modify/reassign the value of an istring, and thus a new one must be
created for such uses (i.e. istr_cat). While having constant values is a good safety mechanism, if it impedes the 
usability of this library, it will be altered so feedback is appreciated. 
- The error handling currently implemented in IString (which is only to prevent improper allocations at the moment) is
is not final. I am currently unsure of how I'm going to handle them going forward, so this is just a stand-in. 