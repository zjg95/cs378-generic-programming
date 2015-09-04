// -------------------------------
// projects/pfd/RunPFD.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout

#include "PFD.h"

// ----
// main
// ----

int main () {
    using namespace std;
    pfd_solve(cin, cout);
    return 0;}

/*
% g++-4.8 -pedantic -std=c++11 -Wall PFD.c++ RunPFD.c++ -o RunPFD



% cat RunPFD.in
1 10
100 200
201 210
900 1000



% RunPFD < RunPFD.in > RunPFD.out



% cat RunPFD.out
1 10 1
100 200 1
201 210 1
900 1000 1



% doxygen -g
// That creates the file Doxyfile.
// Make the following edits to Doxyfile.
// EXTRACT_ALL            = YES
// EXTRACT_PRIVATE        = YES
// EXTRACT_STATIC         = YES



% doxygen Doxyfile
// That creates the directory html/.
*/