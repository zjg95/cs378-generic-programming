// --------------------------------
// projects/pfd/TestPFD.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read
// ----

TEST(PFDFixture, read_1) {
    string s("1 10\n");
    vector<int> v = pfd_string_to_vector(s);
    ASSERT_EQ( 2, v.size());
    ASSERT_EQ( 1, v[0]);
    ASSERT_EQ(10, v[1]);
}

TEST(PFDFixture, read_2) {
    string s("");
    vector<int> v = pfd_string_to_vector(s);
    ASSERT_EQ(0, v.size());
}

TEST(PFDFixture, read_3) {
    string s("1 10 20");
    vector<int> v = pfd_string_to_vector(s);
    ASSERT_EQ( 3, v.size());
    ASSERT_EQ( 1, v[0]);
    ASSERT_EQ(10, v[1]);
    ASSERT_EQ(20, v[2]);
}

TEST(PFDFixture, read_4) {
    string s("\n");
    vector<int> v = pfd_string_to_vector(s);
    ASSERT_EQ( 0, v.size());
}

TEST(PFDFixture, read_5) {
    string s("1\n2");
    vector<int> v = pfd_string_to_vector(s);
    ASSERT_EQ( 2, v.size());
    ASSERT_EQ( 1, v[0]);
}

// --------------
// get_input_list
// --------------

TEST(PFDFixture, get_input_list_1){
    istringstream r("1 2 3 4 5\n");
    vector<int> list = pfd_stream_to_vector(r);

    ASSERT_EQ(5, list.size());
    ASSERT_EQ(1,     list[0]);
    ASSERT_EQ(2,     list[1]);
    ASSERT_EQ(3,     list[2]);
    ASSERT_EQ(4,     list[3]);
    ASSERT_EQ(5,     list[4]);
}

TEST(PFDFixture, get_input_list_2){
    istringstream r("1\n1\n1");
    vector<int> list = pfd_stream_to_vector(r);

    ASSERT_EQ(1, list.size());
    ASSERT_EQ(1,     list[0]);
}

TEST(PFDFixture, get_input_list_3){
    istringstream r("\n1\n1");
    vector<int> list = pfd_stream_to_vector(r);

    ASSERT_EQ(0, list.size());
}

TEST(PFDFixture, get_input_list_4){
    istringstream r("\n1\n2 3");
    vector<int> list = pfd_stream_to_vector(r);

    ASSERT_EQ(0, list.size());

    list = pfd_stream_to_vector(r);
    ASSERT_EQ(1, list.size());
    ASSERT_EQ(1,     list[0]);

    list = pfd_stream_to_vector(r);
    ASSERT_EQ(2, list.size());
    ASSERT_EQ(2,     list[0]);
    ASSERT_EQ(3,     list[1]);
}

// -----
// print
// -----

TEST(PFDFixture, print_1) {
    ostringstream w;
    vector<int> x = {1, 2, 3};
    pfd_print(w, x);
    ASSERT_EQ("1 2 3", w.str());
}

TEST(PFDFixture, print_2) {
    ostringstream w;
    vector<int> x = {1, 2, 3, 4, 5, 6, 7};
    pfd_print(w, x);
    ASSERT_EQ("1 2 3 4 5 6 7", w.str());
}

TEST(PFDFixture, print_3) {
    ostringstream w;
    vector<int> x = {1};
    pfd_print(w, x);
    ASSERT_EQ("1", w.str());
}

TEST(PFDFixture, print_4) {
    ostringstream w;
    vector<int> x;
    pfd_print(w, x);
    ASSERT_EQ("", w.str());
}

// -----
// solve
// -----

TEST(PFDFixture, solve_1) {
    istringstream r(""
    "5 4\n"
    "3 2 1 5\n"
    "2 2 5 3\n"
    "4 1 3\n"
    "5 1 1");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4", w.str());
}

TEST(PFDFixture, solve_2) {
    istringstream r(""
    "4 2\n"
    "1 1 4\n"
    "2 1 3");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 2 4 1", w.str());
}

TEST(PFDFixture, solve_3) {
    istringstream r(""
    "4 3\n"
    "1 3 2 3 4\n"
    "2 1 4\n"
    "3 1 4");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("4 2 3 1", w.str());
}

TEST(PFDFixture, solve_4) {
    istringstream r(""
    "6 5\n"
    "1 2 2 3\n"
    "2 1 3\n"
    "4 2 1 5\n"
    "6 2 5 4\n"
    "5 1 2");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 2 1 5 4 6", w.str());
}

TEST(PFDFixture, solve_5) {
    istringstream r("4 0");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 2 3 4", w.str());
}

TEST(PFDFixture, solve_6) {
    istringstream r("1 0\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1", w.str());
}

TEST(PFDFixture, solve_7) {
    istringstream r("3 2\n1 1 2\n3 1 2\n");
    ostringstream w;
    pfd_solve(r, w);

    ASSERT_EQ("2 1 3", w.str());
}

TEST(PFDFixture, solve_8) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4", w.str());
}

TEST(PFDFixture, solve_9) {
    istringstream r(""
    "6 4\n"
    "5 2 3 4\n"
    "6 2 1 2\n"
    "2 2 3 4\n"
    "1 2 3 4\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 4 1 2 5 6", w.str());
}

TEST(PFDFixture, solve_10) {
    istringstream r(""
    "9 7\n"
    "2 1 1\n"
    "3 2 6 2\n"
    "4 1 2\n"
    "6 2 5 4\n"
    "7 1 6\n"
    "8 1 7\n"
    "9 1 5\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 2 4 5 6 3 7 8 9", w.str());
}

// ---------
// next_task
// ---------

TEST(PFDFixture, next_task_1){
    vector<task> task_list;
    for (int i = 1; i < 4; ++i)
        task_list.push_back(task(i));

    task_list[0] += task_list[1] += task_list[2];
    task_list[0] += task_list[2];

    ASSERT_EQ(2, task_list[0].dependencies);
    ASSERT_EQ(1, task_list[1].dependencies);
    ASSERT_EQ(0, task_list[2].dependencies);

    ASSERT_EQ(3, pfd_next_task(task_list));
    ASSERT_EQ(2, pfd_next_task(task_list));
    ASSERT_EQ(1, pfd_next_task(task_list));
}

TEST(PFDFixture, next_task_2){
    vector<task> task_list;
    for (int i = 1; i < 4; ++i)
        task_list.push_back(task(i));

    task_list[1] += task_list[0];
    task_list[2] += task_list[0];
    task_list[2] += task_list[1];

    ASSERT_EQ(0, task_list[0].dependencies);
    ASSERT_EQ(1, task_list[1].dependencies);
    ASSERT_EQ(2, task_list[2].dependencies);

    ASSERT_EQ(1, pfd_next_task(task_list));
    ASSERT_EQ(2, pfd_next_task(task_list));
    ASSERT_EQ(3, pfd_next_task(task_list));
}

// ----
// task
// ----

TEST(TaskFixture, task_1){
    task t(1);
    ASSERT_EQ(1,                   t.number);
    ASSERT_EQ(0,             t.dependencies);
    ASSERT_EQ(0, t.dependencies_list.size());
}

TEST(TaskFixture, task_2){
    vector<task> task_list;
    for (int i = 1; i < 4; ++i)
        task_list.push_back(task(i));

    task_list[0] += task_list[1] += task_list[2];
    task_list[0] += task_list[2];

    ASSERT_EQ(2, task_list[0].dependencies);
    ASSERT_EQ(1, task_list[1].dependencies);
    ASSERT_EQ(0, task_list[2].dependencies);

    task_list[0] -= task_list[2];
    task_list[2] -= task_list[0];
    task_list[1] -= task_list[2];

    ASSERT_EQ(1, task_list[0].dependencies);
    ASSERT_EQ(0, task_list[1].dependencies);
    ASSERT_EQ(0, task_list[2].dependencies);
}


