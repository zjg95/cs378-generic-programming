// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

#define BASE_CYCLE_LENGTH 1
#define MAX_INT 1000000

using namespace std;

#ifdef CACHE
    #define CACHE_SIZE 500000
    int cache[CACHE_SIZE] = {0};
#endif /* CACHE */

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// --------------------
// collatz_cycle_length
// --------------------

int collatz_cycle_length(unsigned int x){
    assert(x > 0);

    if (x <= 1)
        return 1;

    // check cache to see if value is known, if so return value
    #ifdef CACHE
        if(x < CACHE_SIZE && cache[x])
            return cache[x];
        int x_copy = x;
    #endif /* CACHE */

    if (x % 2 == 0) // even
        x /= 2;
    else
        x = x * 3 + 1;

    // compute the value, filling in cache if space permitting
    int value = 1 + collatz_cycle_length(x);

    #ifdef CACHE
        if (x < CACHE_SIZE)
            cache[x_copy] = value;
    #endif /* CACHE */

    assert(value > 0);

    return value;
}

// -----------------
// collatz_max_cycle
// -----------------

int collatz_max_cycle(int start, int finish){
    int max_cycle = BASE_CYCLE_LENGTH;

    for (; start <= finish; ++start){
        int value = collatz_cycle_length(start);

        if (value > max_cycle)
            max_cycle = value;
    }

    assert(max_cycle >= BASE_CYCLE_LENGTH);
    return max_cycle;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int start, int finish) {
    assert(start < MAX_INT && finish < MAX_INT);

    if (start > finish){
        // swap the start/finish values
        start ^= finish;
        finish ^= start;
        start ^= finish;
    }

    int max_cycle = collatz_max_cycle(start, finish);

    assert(max_cycle >= 1);
    return max_cycle;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}