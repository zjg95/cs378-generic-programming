// -------------------------------
// projects/collatz/RunCollatz.c++
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

#include <cassert>  // assert
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#define BASE_CYCLE_LENGTH 1
#define CACHE_SIZE 100

using namespace std;

int cache[CACHE_SIZE] = {0};

pair<int, int> collatz_read (const string& s);
int collatz_eval (int i, int j);
void collatz_print (ostream& w, int i, int j, int v);
void collatz_solve (istream& r, ostream& w);

// ----
// main
// ----

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}

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

int collatz_cycle_length(int x){
    if (x <= 1)
        return 1;

    // check cache to see if value is known, if so return value
    #ifdef CACHE
        if(x < CACHE_SIZE && cache[x])
            return cache[x];
    #endif /* CACHE */

    int x_copy;

    if (x % 2 == 0) // even
        x_copy = x / 2;
    else
        x_copy = x * 3 + 1;

    // compute the value, filling in cache if space permitting
    int value = 1 + collatz_cycle_length(x_copy);

    #ifdef CACHE
        if (x < CACHE_SIZE)
            cache[x] = value;
    #endif /* CACHE */

    return value;
}

// -----------------
// collatz_max_cycle
// -----------------

int collatz_max_cycle(int start, int finish){
    int max_cycle = BASE_CYCLE_LENGTH;

    for (; start < finish; ++start){
        int value = collatz_cycle_length(start);

        if (value > max_cycle)
            max_cycle = value;
    }

    return max_cycle;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int start, int finish) {
    assert(start != finish);

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