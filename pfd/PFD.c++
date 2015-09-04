// ----------------------------
// projects/pfd/PFD.c++
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
#include <vector>
#include <queue>

#include "PFD.h"

#define MAX_RULES 100
#define MAX_TASKS 100

using namespace std;

// ------------
// pfd_string_to_vector
// ------------

vector<int> pfd_string_to_vector (const string& s) {
    istringstream sin(s);
    vector<int> num_list;
    int n;
    while (sin >> n){
        num_list.push_back(n);
    }
    return num_list;
}

vector<int> pfd_stream_to_vector(istream& r){
    string s;
    getline(r, s);
    return pfd_string_to_vector(s);
}

// -------------
// pfd_print
// -------------

void pfd_print (ostream& w, const vector<int>& output_list) {
    vector<int>::const_iterator itr = output_list.begin();
    vector<int>::const_iterator end = output_list.end();

    while (itr != end){
        assert(*itr > 0);
        w << *itr;
        if (++itr != end)
            w << " ";
    }
}

int pfd_next_task(vector<task>& task_list){
    priority_queue<task, vector<task>, greater<task>> queue;

    // fill the queue with values
    for (task& target : task_list)
        queue.push(target);

    const task& top = queue.top();
    assert(top.dependencies == 0);
    assert(*top > 0);

    int index;
    for (unsigned i = 0; i < task_list.size(); ++i){
        if (task_list[i] == top)
            index = i;
        else
            task_list[i] -= top;
    }
    
    task_list.erase(task_list.begin() + index);

    return *top;
}

// ----
// eval
// ----

vector<int> pfd_eval(vector<task> task_list){
    vector<int> output_list;

    while (!task_list.empty()){
        int value = pfd_next_task(task_list);
        output_list.push_back(value);
    }

    return output_list;
}

// -------------
// pfd_solve
// -------------

void pfd_solve (istream& r, ostream& w) {
    vector<int> input_list;

    input_list = pfd_stream_to_vector(r); // put into a vector

    assert(input_list.size() == 2);

    const unsigned int  tasks = input_list[0];
    const unsigned int  rules = input_list[1];

    assert(tasks > 0 && tasks <= MAX_TASKS);
    assert(rules <= MAX_RULES);
    assert(tasks >= rules);

    vector<task> task_list;

    for (unsigned i = 1; i <= tasks; ++i)
        task_list.push_back(task(i));

    assert(task_list.size()    == tasks);

    for (unsigned int i = 0; i < rules; ++i){
        // read the line into a list
        input_list = pfd_stream_to_vector(r);

        assert(input_list.size() > 0);
        assert(input_list.size() > 2);

        const unsigned int       target = input_list[0] - 1;
        const unsigned int dependencies = input_list[1];

        assert(target >= 0);
        assert(dependencies > 0 && dependencies < tasks);

        task& target_task = task_list[target];

        // remove the 2nd elements
        input_list.erase (input_list.begin() + 1);
        input_list.erase (input_list.begin());

        // add dependencies to the target task
        for (int i : input_list){
            --i;
            assert(target_task != task_list[i]);
            target_task += task_list[i];
        }
    }

    vector<int> output_list = pfd_eval(task_list);

    assert(output_list.size() == tasks);

    pfd_print(w, output_list);
}


