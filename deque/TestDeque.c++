// --------------------------------
// projects/c++/deque/TestDeque.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// http://www.cplusplus.com/reference/deque/deque/

// --------
// includes
// --------

#include <deque>     // deque
#include <list>
#include <vector>
#include <stdexcept> // invalid_argument, out_of_range

#include "gtest/gtest.h"

#include "Deque.h"

// -----
// Using
// -----

using namespace std;

using testing::Test;
using testing::Types;

// -----
// Types
// -----

template <typename T>
struct Deque_Fixture : Test {
    typedef T                               deque_type;
    typedef typename deque_type::value_type value_type;};

typedef Types<
               deque<int>,
            my_deque<int>>
        deque_types;

TYPED_TEST_CASE(Deque_Fixture, deque_types);

// -------------------
// default_constructor
// -------------------

TYPED_TEST(Deque_Fixture, default_contructor_1) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x;
    ASSERT_TRUE(x.empty());
    ASSERT_EQ(x.size(),0);
}

// ---------------
// arg_constructor
// ---------------

TYPED_TEST(Deque_Fixture, arg_constructor_1) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(10, 2);
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(10, x.size());
}

TYPED_TEST(Deque_Fixture, arg_constructor_2) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(10);
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(10, x.size());
}

TYPED_TEST(Deque_Fixture, arg_constructor_3) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(0);
    ASSERT_TRUE(x.empty());
    ASSERT_EQ(0, x.size());
}

TYPED_TEST(Deque_Fixture, arg_constructor_4) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(300);
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(300, x.size());
}

TYPED_TEST(Deque_Fixture, arg_constructor_5) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(306);
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(306, x.size());
}

TYPED_TEST(Deque_Fixture, arg_constructor_7) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(123456);
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(123456, x.size());
}

TYPED_TEST(Deque_Fixture, arg_constructor_8) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(10, 2);
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(2, x.front());
    ASSERT_EQ(2, x.back());
}

// ----------------
// copy_constructor
// ----------------

TYPED_TEST(Deque_Fixture, copy_constructor_1) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(10, 2);
    const deque_type y(x);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
    ASSERT_TRUE(!x.empty() && !y.empty());
    ASSERT_EQ(x.size(), y.size());
}

TYPED_TEST(Deque_Fixture, copy_constructor_2) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(1000, 2);
    const deque_type y = x;

    ASSERT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
    ASSERT_TRUE(!x.empty() && !y.empty());
    ASSERT_EQ(x.size(), y.size());
}

TYPED_TEST(Deque_Fixture, copy_constructor_3) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x;
    const deque_type y = x;

    ASSERT_TRUE(x.empty() && y.empty());
    ASSERT_EQ(x.size(), y.size());
}

TYPED_TEST(Deque_Fixture, copy_constructor_4) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(1);
    const deque_type y = x;

    ASSERT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
    ASSERT_TRUE(!x.empty() && !y.empty());
    ASSERT_EQ(x.size(), y.size());
}

// -------------------
// assignment_operator
// -------------------

TYPED_TEST(Deque_Fixture, assign_1) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(10, 2);
    deque_type y;

    ASSERT_EQ(0, y.size());

    y = x;

    ASSERT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
    ASSERT_EQ(x.size(), y.size());
}

TYPED_TEST(Deque_Fixture, assign_2) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(1000);
    deque_type y;

    ASSERT_EQ(0, y.size());

    y = x;

    ASSERT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
    ASSERT_EQ(x.size(), y.size());
}

TYPED_TEST(Deque_Fixture, assign_3) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(10);
    const deque_type z(1000);
    deque_type y;

    ASSERT_EQ(0, y.size());

    y = x;

    ASSERT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
    ASSERT_EQ(x.size(), y.size());

    y = z;

    ASSERT_TRUE(std::equal(z.begin(), z.end(), y.begin()));
    ASSERT_EQ(z.size(), y.size());

    y = x;

    ASSERT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
    ASSERT_EQ(x.size(), y.size());
}

// -----------
// operator []
// -----------

TYPED_TEST(Deque_Fixture, index_operator_1) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(1,2);

    ASSERT_EQ(2, x[0]);
}

TYPED_TEST(Deque_Fixture, index_operator_2) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(5, 2);
    ASSERT_EQ(2, x[0]);
    ASSERT_EQ(2, x[1]);
    ASSERT_EQ(2, x[2]);
    ASSERT_EQ(2, x[3]);
    ASSERT_EQ(2, x[4]);
}

TYPED_TEST(Deque_Fixture, index_operator_3) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(10, 2);
    ASSERT_EQ(2, x[0]);
    ASSERT_EQ(2, x[1]);
    ASSERT_EQ(2, x[2]);
    ASSERT_EQ(2, x[3]);
    ASSERT_EQ(2, x[4]);
    ASSERT_EQ(2, x[5]);
    ASSERT_EQ(2, x[6]);
    ASSERT_EQ(2, x[7]);
    ASSERT_EQ(2, x[8]);
    ASSERT_EQ(2, x[9]);
}

TYPED_TEST(Deque_Fixture, index_operator_4) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(200, 2);
    ASSERT_EQ(2, x[3]);
}

TYPED_TEST(Deque_Fixture, index_operator_5) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(100, 2);
    ASSERT_EQ(2, x[20]);
}

TYPED_TEST(Deque_Fixture, index_operator_6) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(101, 2);
    ASSERT_EQ(2, x[20]);
}

// --
// at
// --

TYPED_TEST(Deque_Fixture, at_1) {
    //at end
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(2);
    x[0] = 1;
    x[1] = 2;

    ASSERT_EQ(2, x.at(1));
}

TYPED_TEST(Deque_Fixture, at_2) {
    //at begin
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(1, 1);
    ASSERT_EQ(1, x.at(0));
}

TYPED_TEST(Deque_Fixture, at_3) {
    //at middle
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(200, 1);
    x[103] = 3;
    ASSERT_EQ(3, x.at(103));
}

TYPED_TEST(Deque_Fixture, at_4) {
    //too high
    typedef typename TestFixture::deque_type deque_type;
    try{
        deque_type x(100, 10);
         ASSERT_EQ(10, x.at(100));
    }catch (out_of_range &e){
        //should go here
        ASSERT_TRUE(true);
    }
}

TYPED_TEST(Deque_Fixture, at_5) {
    //too low
    typedef typename TestFixture::deque_type deque_type;
    try{
        deque_type x(100, 10);
       ASSERT_EQ(10, x.at(-1));
    }catch (out_of_range &e){
        //should go here
        ASSERT_TRUE(true);
    }
}

TYPED_TEST(Deque_Fixture, at_6) {
    //given size (wrong)
    typedef typename TestFixture::deque_type deque_type;
    try{
        deque_type x(100, 10);
        ASSERT_EQ(10, x.at(100));
    }catch (out_of_range &e){
        //should go here
        ASSERT_TRUE(true);
    }
}

// -----
// erase
// -----

TYPED_TEST(Deque_Fixture, erase_1) {
    //at begin
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3);
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;

    ASSERT_EQ(3, x.size());
    ASSERT_EQ(1, *(x.begin()));
    ASSERT_EQ(3, *(--x.end()));
    x.erase(x.begin());
    ASSERT_EQ(2, x.size());
    ASSERT_EQ(2, *(x.begin()));
    ASSERT_EQ(3, *(--x.end()));
    
}


TYPED_TEST(Deque_Fixture, erase_2) {
    //at end
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3);
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;

    ASSERT_EQ(3, x.size());
    ASSERT_EQ(1, *x.begin());
    ASSERT_EQ(3, *(--x.end()));
    x.erase(--(x.end()));
    ASSERT_EQ(2, x.size());
    ASSERT_EQ(2, *(--x.end()));
    ASSERT_EQ(1, *x.begin());
    
}

TYPED_TEST(Deque_Fixture, erase_3) {
    //at middle
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3);
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;

    ASSERT_EQ(3, x.size());
    ASSERT_EQ(1, *x.begin());
    ASSERT_EQ(3, *(--x.end()));
    x.erase(x.begin() + 1);
    ASSERT_EQ(2, x.size());
    ASSERT_EQ(3, *(--x.end()));
    ASSERT_EQ(1, *x.begin());
    
}

TYPED_TEST(Deque_Fixture, erase_4) {
    //at middle
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3);
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;

    ASSERT_EQ(3, x.size());
    ASSERT_EQ(1, *x.begin());
    ASSERT_EQ(3, *(--x.end()));
    
    typename deque_type::iterator iter = x.erase(x.begin() + 1);
    
    ASSERT_EQ(3, *iter);
}

TYPED_TEST(Deque_Fixture, erase_5) {
    //remove all fron begin
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(300);
    for(int i = 0; i < 300; ++i)
        x[i] = i+1;

    for(int i = 0; i < 300; ++i)
        x.erase(x.begin());

    ASSERT_EQ(0, x.size());
    ASSERT_TRUE(x.begin() == x.end());
}

TYPED_TEST(Deque_Fixture, erase_6) {
    //remove all from end
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(300);
    for(int i = 0; i < 300; ++i)
        x[i] = i+1;

    for(int i = 0; i < 300; ++i)
        x.erase(x.end() - 1);

    ASSERT_EQ(0, x.size());
    ASSERT_TRUE(x.begin() == x.end());
}

TYPED_TEST(Deque_Fixture, erase_7) {
    //at middle
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3000);
    for(int i = 0; i < 3000; ++i)
        x[i] = i;

    for(int i = 0; i < 100; ++i)
        x.erase(x.begin() + 2000);

    ASSERT_EQ(2900, x.size());
    ASSERT_FALSE(x.begin() == x.end());
    ASSERT_EQ(2100, x[2000]);

}


// --------
// pop_back
// --------

TYPED_TEST(Deque_Fixture, pop_back_1) {
    //at middle
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(2);
    x[0] = 1;
    x[1] = 2;

    ASSERT_EQ(1, x.at(0));
    ASSERT_EQ(2, x.at(1));
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(2, x.size());
    x.pop_back();
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(1, x.size());
    ASSERT_EQ(1, x.at(0));
}

TYPED_TEST(Deque_Fixture, pop_back_2) {
    //at middle
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(1, 1);

    ASSERT_EQ(1, x.at(0));
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(1, x.size());
    x.pop_back();
    ASSERT_TRUE(x.empty());
    ASSERT_EQ(0, x.size());
}

TYPED_TEST(Deque_Fixture, pop_back_3) {
    //at middle
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(4927, 1);
    std::vector<int> v(4927, 1);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));

    for (int i = 0; i < 1234; ++i){
        v.pop_back();
        x.pop_back();
    }

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));    
}

// ---------
// pop_front
// ---------

TYPED_TEST(Deque_Fixture, pop_front_1) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(2);
    x[0] = 1;
    x[1] = 2;

    ASSERT_EQ(1, x.at(0));
    ASSERT_EQ(2, x.at(1));
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(2, x.size());

    x.pop_front();

    ASSERT_FALSE(x.empty());
    ASSERT_EQ(1, x.size());
    ASSERT_EQ(2, x.at(0));
}

TYPED_TEST(Deque_Fixture, pop_front_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(1, 1);

    ASSERT_EQ(1, x.at(0));
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(1, x.size());

    x.pop_front();

    ASSERT_TRUE(x.empty());
    ASSERT_EQ(0, x.size());
}

TYPED_TEST(Deque_Fixture, pop_front_3) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(4927, 1);
    std::list<int> v(4927, 1);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));

    for (int i = 0; i < 1234; ++i){
        v.pop_front();
        x.pop_front();
    }

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));    
}

// ------
// resize
// ------

TYPED_TEST(Deque_Fixture, resize_1) { // make it the same
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    ASSERT_EQ(0, x.size());

    x.resize(0);

    ASSERT_EQ(0, x.size());
}

TYPED_TEST(Deque_Fixture, resize_2) { // make it smaller
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10);

    ASSERT_EQ(10, x.size());

    x.resize(5, 7);

    ASSERT_EQ(5, x.size()); 
}

TYPED_TEST(Deque_Fixture, resize_3) { // make it bigger
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    ASSERT_EQ(0, x.size());

    x.resize(5, 7);

    ASSERT_EQ(5, x.size());

    std::vector<int> v(5, 7);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));  
}

TYPED_TEST(Deque_Fixture, resize_4) { // make it bigger
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10, 7);

    ASSERT_EQ(10, x.size());

    x.resize(15, 7);

    ASSERT_EQ(15, x.size());

    std::vector<int> v(15, 7);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));  
}

TYPED_TEST(Deque_Fixture, resize_5) { // make it much much bigger
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    ASSERT_EQ(0, x.size());

    x.resize(150, 7);

    ASSERT_EQ(150, x.size());

    std::vector<int> v(150, 7);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));  
}

TYPED_TEST(Deque_Fixture, resize_6) { // make it much much smaller
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(150, 7);

    ASSERT_EQ(150, x.size());

    x.resize(5, 7);

    ASSERT_EQ(5, x.size());

    std::vector<int> v(5, 7);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));  
}

TYPED_TEST(Deque_Fixture, resize_7) { // make it much much bigger
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    ASSERT_EQ(0, x.size());

    x.resize(300, 7);

    ASSERT_EQ(300, x.size());

    std::vector<int> v(300, 7);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));  
}

TYPED_TEST(Deque_Fixture, resize_8) { // make it much much bigger
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    ASSERT_EQ(0, x.size());

    x.resize(3000, 7);

    ASSERT_EQ(3000, x.size());

    std::vector<int> v(3000, 7);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));  
}

TYPED_TEST(Deque_Fixture, resize_9) { // make it much much bigger
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(23, 7);

    ASSERT_EQ(23, x.size());

    x.resize(492, 7);

    ASSERT_EQ(492, x.size());

    std::vector<int> v(492, 7);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));  
}

TYPED_TEST(Deque_Fixture, resize_10) { // make it much much bigger
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(55, 7);

    ASSERT_EQ(55, x.size());

    x.resize(60, 7);

    ASSERT_EQ(60, x.size());

    std::vector<int> v(60, 7);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));  
}

// ----
// swap
// ----

TYPED_TEST(Deque_Fixture, swap_1) {
    //different numbers, same size.
    typedef typename TestFixture::deque_type deque_type;
    
    deque_type x(5);
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;
    x[3] = 4;
    x[4] = 5;
    vector<int> xv = {1,2,3,4,5};
    
    deque_type y(5);
    y[0] = 1;
    y[1] = 2;
    y[2] = 3;
    y[3] = 4;
    y[4] = 5;
    vector<int> yv = {1,2,3,4,5};


    ASSERT_TRUE(std::equal(x.begin(), x.end(), xv.begin()));
    ASSERT_TRUE(std::equal(y.begin(), y.end(), yv.begin()));

    x.swap(y);

    ASSERT_TRUE(std::equal(x.begin(), x.end(), yv.begin()));
    ASSERT_TRUE(std::equal(y.begin(), y.end(), xv.begin()));  
}

TYPED_TEST(Deque_Fixture, swap_2) {
    //different sizes
    typedef typename TestFixture::deque_type deque_type;
    
    deque_type x(5, 5);
    deque_type y(6, 6);
   
    ASSERT_EQ(5, x.size());
    ASSERT_EQ(5, x.front());

    ASSERT_EQ(6, y.size());
    ASSERT_EQ(6, y.front());

    x.swap(y);

    ASSERT_EQ(6, x.size());
    ASSERT_EQ(6, x.front());

    ASSERT_EQ(5, y.size());
    ASSERT_EQ(5, y.front());
 
}

TYPED_TEST(Deque_Fixture, swap_3) {
    //default constructor with argument constructor.
    typedef typename TestFixture::deque_type deque_type;
    
    deque_type x;
    deque_type y(6, 6);
   
    ASSERT_EQ(0, x.size());
    ASSERT_TRUE(x.empty());

    ASSERT_EQ(6, y.size());
    ASSERT_EQ(6, y.front());

    x.swap(y);

    ASSERT_EQ(6, x.size());
    ASSERT_EQ(6, x.front());

    ASSERT_EQ(0, y.size());
    ASSERT_TRUE(y.empty());
 
}

TYPED_TEST(Deque_Fixture, swap_4) {
    //big deque swap
    typedef typename TestFixture::deque_type deque_type;
    
    deque_type x(500, 5);
    deque_type y(600, 6);
   
    ASSERT_EQ(500, x.size());
    ASSERT_EQ(5, x.back());

    ASSERT_EQ(600, y.size());
    ASSERT_EQ(6, y.back());

    x.swap(y);

    ASSERT_EQ(600, x.size());
    ASSERT_EQ(6, x.back());

    ASSERT_EQ(500, y.size());
    ASSERT_EQ(5, y.back());
 
}

// --------
// iterator
// --------

TYPED_TEST(Deque_Fixture, iterator_begin_1) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(1, 7);

    typename deque_type::iterator iter = x.begin();

    ASSERT_EQ(7, *iter);
}

TYPED_TEST(Deque_Fixture, iterator_begin_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(2);
    x[0] = 1;
    x[1] = 2;

    typename deque_type::iterator iter = x.begin();

    ASSERT_EQ(1, *iter);
    ASSERT_EQ(2, *(++iter));
}

TYPED_TEST(Deque_Fixture, iterator_begin_3) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3);
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;

    typename deque_type::iterator iter = x.begin();

    ASSERT_EQ(1, *iter);
    ASSERT_EQ(2, *(++iter));
    ASSERT_EQ(3, *(++iter));
    ASSERT_EQ(2, *(--iter));
    ASSERT_EQ(1, *(--iter));
}

TYPED_TEST(Deque_Fixture, iterator_end_1) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10, 5);
    typename deque_type::iterator iter = x.end();

    ASSERT_EQ(5, *(--iter));
}

TYPED_TEST(Deque_Fixture, iterator_end_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3, 3);
    x[2] = 4;

    typename deque_type::iterator iter = x.end();

    ASSERT_EQ(4, *(--iter));
}

TYPED_TEST(Deque_Fixture, iterator_end_3) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3, 3);
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;

    typename deque_type::iterator iter = x.end();

    ASSERT_EQ(3, *(--iter));
    ASSERT_EQ(2, *(--iter));
    ASSERT_EQ(1, *(--iter));
    ASSERT_EQ(2, *(++iter));
    ASSERT_EQ(3, *(++iter));
}

TYPED_TEST(Deque_Fixture, iterator_end_equals_begin_1) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(1, 7);

    typename deque_type::iterator iter_b = x.begin();
    typename deque_type::iterator iter_e = x.end();

    ASSERT_TRUE(iter_e != iter_b);
    ASSERT_EQ(*(--iter_e), *iter_b);
    ASSERT_TRUE(iter_e == iter_b);
}

TYPED_TEST(Deque_Fixture, iterator_end_equals_begin_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3, 7);

    typename deque_type::iterator iter_b = x.begin();
    typename deque_type::iterator iter_e = x.end();

    ASSERT_TRUE(iter_e != iter_b);
    ASSERT_TRUE((iter_e -= 3) == iter_b);
}



// --------------
// const_iterator
// --------------

TYPED_TEST(Deque_Fixture, const_iterator_begin_1) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(1, 7);
    typename deque_type::const_iterator iter = x.begin();

    ASSERT_EQ(7, *iter);
}

TYPED_TEST(Deque_Fixture, const_iterator_begin_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(2);
    x[0] = 1;
    x[1] = 2;

    const deque_type& r = x; // you can't have a const iterator on a non-const object
    typename deque_type::const_iterator iter = r.begin();

    ASSERT_EQ(1, *iter);
    ASSERT_EQ(2, *(++iter));
}

TYPED_TEST(Deque_Fixture, const_iterator_begin_3) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3);
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;

    const deque_type& r = x; // you can't have a const iterator on a non-const object
    typename deque_type::const_iterator iter = r.begin();

    ASSERT_EQ(1, *iter);
    ASSERT_EQ(2, *(++iter));
    ASSERT_EQ(3, *(++iter));
    ASSERT_EQ(2, *(--iter));
    ASSERT_EQ(1, *(--iter));
}

TYPED_TEST(Deque_Fixture, const_iterator_end_1) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(10, 5);
    typename deque_type::const_iterator iter = x.end();

    ASSERT_EQ(5, *(--iter));
}

TYPED_TEST(Deque_Fixture, const_iterator_end_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3, 3);
    x[2] = 4;

    const deque_type& r = x; // you can't have a const iterator on a non-const object
    typename deque_type::const_iterator iter = r.end();

    ASSERT_EQ(4, *(--iter));
}

TYPED_TEST(Deque_Fixture, const_iterator_end_3) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3, 3);
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;

    const deque_type& r = x; // you can't have a const iterator on a non-const object
    typename deque_type::const_iterator iter = r.end();

    ASSERT_EQ(3, *(--iter));
    ASSERT_EQ(2, *(--iter));
    ASSERT_EQ(1, *(--iter));
    ASSERT_EQ(2, *(++iter));
    ASSERT_EQ(3, *(++iter));
}

TYPED_TEST(Deque_Fixture, const_iterator_end_equals_begin_1) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(1, 7);

    typename deque_type::const_iterator iter_b = x.begin();
    typename deque_type::const_iterator iter_e = x.end();

    ASSERT_TRUE(iter_e != iter_b);
    ASSERT_EQ(*(--iter_e), *iter_b);
    ASSERT_TRUE(iter_e == iter_b);
}

TYPED_TEST(Deque_Fixture, const_iterator_end_equals_begin_2) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x(3, 7);
    typename deque_type::const_iterator iter_b = x.begin();
    typename deque_type::const_iterator iter_e = x.end();


    ASSERT_TRUE(iter_e != iter_b);
    ASSERT_TRUE((iter_e -= 3) == iter_b);
}

// ---------
// push_back
// ---------

TYPED_TEST(Deque_Fixture, push_back_1a) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3, 7);

    x.push_back(5);

    vector<int> v = {7,7,7,5};

    ASSERT_EQ(4, x.size());
    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));
}

TYPED_TEST(Deque_Fixture, push_back_2a) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    x.push_back(5);

    vector<int> v = {5};

    ASSERT_EQ(1, x.size());
    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));
}

TYPED_TEST(Deque_Fixture, push_back_3a) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 10; ++i){
        x.push_back(10);
    }

    vector<int> v(10, 10);

    ASSERT_EQ(10, x.size());
    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));
}

TYPED_TEST(Deque_Fixture, push_back_4a) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(55, 0);

    x.push_back(1);

    vector<int> v(55, 0);
    v.push_back(1);

    ASSERT_EQ(56, x.size());
    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));
}

// ----------
// push_front
// ----------

// case 1/3

TYPED_TEST(Deque_Fixture, push_front_1) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3, 7);

    x.push_front(5);

    std::list<int> v = {5,7,7,7};

    ASSERT_EQ(4, x.size());
    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));
}

TYPED_TEST(Deque_Fixture, push_front_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    x.push_front(5);

    std::list<int> v = {5};

    ASSERT_EQ(1, x.size());
    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));
}

TYPED_TEST(Deque_Fixture, push_front_3) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 10; ++i){
        x.push_front(10);
    }

    std::list<int> v(10, 10);

    ASSERT_EQ(10, x.size());
    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));
}

// using resize

TYPED_TEST(Deque_Fixture, push_front_4) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 44; ++i){
        ASSERT_EQ(i, x.size());
        x.push_front(i);
    }

    ASSERT_EQ(44, x.size());
    x.push_front(44);
    ASSERT_EQ(45, x.size());

    for (int i = 0; i < 45; ++i){
        ASSERT_EQ(44 - i, x[i]);
    }
    
}

TYPED_TEST(Deque_Fixture, push_front_5) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 1003; ++i){
        ASSERT_EQ(i, x.size());
        x.push_front(i);
    }

    ASSERT_EQ(1003, x.size());
    x.push_front(1003);
    ASSERT_EQ(1004, x.size());

    for (int i = 0; i < 1004; ++i){
        ASSERT_EQ(1003 - i, x[i]);
    }
}

TYPED_TEST(Deque_Fixture, push_front_6) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 10003; ++i){
        ASSERT_EQ(i, x.size());
        x.push_front(i);
    }

    ASSERT_EQ(10003, x.size());
    x.push_front(10003);
    ASSERT_EQ(10004, x.size());

    for (int i = 0; i < 10004; ++i){
        ASSERT_EQ(10003 - i, x[i]);
    }
}

// ---------
// push_back
// ---------

// case 2/3

TYPED_TEST(Deque_Fixture, push_back_1) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3);
    for (int i = 0; i < 3; ++i){
        x[i] = i;
    }

    x.push_back(3);

    std::list<int> v = {0,1,2,3};

    ASSERT_EQ(4, x.size());
    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));
}

TYPED_TEST(Deque_Fixture, push_back_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;
    int size = 0;

    for (int i = 0; i < 1; ++i){
        ASSERT_EQ(size++, x.size());
        x.push_back(i);
    }

    ASSERT_EQ(1, x.size());
    x.push_back(1);
    ASSERT_EQ(2, x.size());

    for (int i = 0; i < 2; ++i){
        ASSERT_EQ(i, x[i]);
    }
}

TYPED_TEST(Deque_Fixture, push_back_3) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;
    int size = 0;

    for (int i = 0; i < 10; ++i){
        ASSERT_EQ(size++, x.size());
        x.push_back(i);
    }

    ASSERT_EQ(10, x.size());
    x.push_back(10);
    ASSERT_EQ(11, x.size());

    for (int i = 0; i < 11; ++i){
        ASSERT_EQ(i, x[i]);
    }
}

// using resize

TYPED_TEST(Deque_Fixture, push_back_4) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;
    int size = 0;

    for (int i = 0; i < 57; ++i){
        ASSERT_EQ(size++, x.size());
        x.push_back(i);
    }

    ASSERT_EQ(57, x.size());
    x.push_back(57);
    ASSERT_EQ(58, x.size()); 

    for (int i = 0; i < 58; ++i){
        ASSERT_EQ(i, x[i]);
    }
}

TYPED_TEST(Deque_Fixture, push_back_5) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 1000; ++i){
        ASSERT_EQ(i, x.size());
        x.push_back(i);
    }

    ASSERT_EQ(1000, x.size());
    x.push_back(1000);
    ASSERT_EQ(1001, x.size());

    for (int i = 0; i < 1001; ++i){
        ASSERT_EQ(i, x[i]);
    }
}

TYPED_TEST(Deque_Fixture, push_back_6) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 10000; ++i){
        ASSERT_EQ(i, x.size());
        x.push_back(i);
    }

    ASSERT_EQ(10000, x.size());
    x.push_back(10000);
    ASSERT_EQ(10001, x.size());

    for (int i = 0; i < 10001; ++i){
        ASSERT_EQ(i, x[i]);
    }
}

// ------
// insert
// ------

// case 3/3

TYPED_TEST(Deque_Fixture, insert) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(3);
    for (int i = 0; i < 3; ++i){
        x[i] = i;
    }
    ASSERT_EQ(3, x.size());
    x.insert( x.begin() + 1, 7);
    ASSERT_EQ(4, x.size());
    ASSERT_EQ(7, *(x.begin() + 1));
    std::list<int> v = {0,7,1,2};

    ASSERT_EQ(4, x.size());
    ASSERT_TRUE(std::equal(x.begin(), x.end(), v.begin()));
}

TYPED_TEST(Deque_Fixture, insert_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 1; ++i){
        ASSERT_EQ(i, x.size());
        x.push_back(i);
    }

    ASSERT_EQ(1, x.size());
    x.insert(x.begin(), 69);
    ASSERT_EQ(2, x.size());

    ASSERT_EQ(69, x[0]);
    ASSERT_EQ(0,  x[1]);
}

TYPED_TEST(Deque_Fixture, insert_3) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 1; ++i){
        ASSERT_EQ(i, x.size());
        x.push_back(i);
    }

    ASSERT_EQ(1, x.size());
    x.insert(x.end(), 69);
    ASSERT_EQ(2, x.size());

    ASSERT_EQ(69, x[1]);
    ASSERT_EQ(0,  x[0]);
}

// using resize

TYPED_TEST(Deque_Fixture, insert_4) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 57; ++i){
        ASSERT_EQ(i, x.size());
        x.push_back(i);
    }

    ASSERT_EQ(57, x.size());
    ASSERT_EQ(20, x[20]);
    x.insert(x.begin() + 20, 10);
    ASSERT_EQ(58, x.size());  
    ASSERT_EQ(10, x[20]);
    ASSERT_EQ(20, x[21]);
}

TYPED_TEST(Deque_Fixture, insert_5) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x;

    for (int i = 0; i < 1000; ++i){
        ASSERT_EQ(i, x.size());
        x.push_back(i);
    }

    ASSERT_EQ(1000, x.size());
    ASSERT_EQ(200, x[200]);
    x.insert(x.begin() + 200, 10);
    x.insert(x.begin() + 400, 10);
    ASSERT_EQ(1002, x.size());  
    ASSERT_EQ(10, x[200]);
    ASSERT_EQ(200, x[201]);
    ASSERT_EQ(10, x[400]);
}

//-------
// clear
//-------

TYPED_TEST(Deque_Fixture, clear_1) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10);
    ASSERT_EQ(10, x.size());
    ASSERT_TRUE(x.begin() != x.end());
    x.clear();
    ASSERT_EQ(0, x.size());
    ASSERT_TRUE(x.begin() == x.end());
}

TYPED_TEST(Deque_Fixture, clear_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(1000, 10);
    ASSERT_EQ(1000, x.size());
    ASSERT_TRUE(x.begin() != x.end());
    x.clear();
    ASSERT_EQ(0, x.size());
    ASSERT_TRUE(x.begin() == x.end());
}

TYPED_TEST(Deque_Fixture, clear_3) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10, 10);
    ASSERT_EQ(10, x.size());
    ASSERT_TRUE(x.begin() != x.end());
    x.resize(100, 10);
    ASSERT_EQ(100, x.size());
    ASSERT_TRUE(x.begin() != x.end());
    x.clear();
    ASSERT_EQ(0, x.size());
    ASSERT_TRUE(x.begin() == x.end());
}

//-------
// equal
//-------

TYPED_TEST(Deque_Fixture, equal_1) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10, 10);
    deque_type y(10, 10);
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(10, y.size());
    ASSERT_TRUE(x == y);
}

TYPED_TEST(Deque_Fixture, equal_2) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10, 10);
    deque_type y(10, 5);
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(10, y.size());
    ASSERT_FALSE(x == y);
}

TYPED_TEST(Deque_Fixture, equal_3) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10, 10);
    deque_type y(5, 10);
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(5, y.size());
    ASSERT_FALSE(x == y);
}

TYPED_TEST(Deque_Fixture, equal_4) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10, 10);
    deque_type y(10, 10);
    y[9] = 9;
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(10, y.size());
    ASSERT_FALSE(x == y);
}

TYPED_TEST(Deque_Fixture, equal_5) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10, 10);
    deque_type y(10, 10);
    x[9] = 9;
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(10, y.size());
    ASSERT_FALSE(x == y);
}