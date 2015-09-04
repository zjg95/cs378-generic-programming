// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Collatz_h
#define Collatz_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair

using namespace std;

// ------------
// collatz_read
// ------------

/**
 * read two ints
 * @param s a string
 * @return a pair of ints, representing the beginning and end of a range, [i, j]
 */
pair<int, int> collatz_read (const string& s);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
int collatz_eval (int i, int j);

// -----------------
// collatz_max_cycle
// -----------------

/**
 * calculate the maximum cycle length of a given range
 * @param start the start of range
 * @param finish the end of the range
 * @return int, representing the max cycle length
 */
int collatz_max_cycle(int start, int finish);

// --------------------
// collatz_cycle_length
// --------------------

/**
 * computes the cycle length of a given value
 * @param x the number to find the cycle length for
 * @return int, representing the cycle length
 */
int collatz_cycle_length(unsigned int x);

// -------------
// collatz_print
// -------------

/**
 * print three ints
 * @param w an ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (ostream& w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void collatz_solve (istream& r, ostream& w);

#endif // Collatz_h