// --------------------------------
// projects/integer/TestInteger.c++
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
#include <deque>

#include "gtest/gtest.h"

#include "Integer.h"

using namespace std;

// -----------
// TestInteger
// -----------

    // ------------
    // IntegerClass
    // ------------

// -----------
// int_constructor
// -----------

TEST(IntegerClass, int_constructor_1){
    Integer<int> test_integer(1);
    ostringstream stream;
    stream << test_integer;
    ASSERT_EQ("1", stream.str());
}

TEST(IntegerClass, int_constructor_2){
    Integer<int> test_integer(22);
    ostringstream stream;
    stream << test_integer;
    ASSERT_EQ("22", stream.str());
}

TEST(IntegerClass, int_constructor_3){
    Integer<int> test_integer(-22);
    ostringstream stream;
    stream << test_integer;
    ASSERT_EQ("-22", stream.str());
}

TEST(IntegerClass, int_constructor_4){
    Integer<int> test_integer(00000001);
    ostringstream stream;
    stream << test_integer;
    ASSERT_EQ("1", stream.str());
}

// -----------
// string_constructor
// -----------

TEST(IntegerClass, string_constructor_1){
    Integer<int> test_integer("1");
    ostringstream stream;
    stream << test_integer;
    ASSERT_EQ("1", stream.str());
}

TEST(IntegerClass, string_constructor_2){
    Integer<int> test_integer("22");
    ostringstream stream;
    stream << test_integer;
    ASSERT_EQ("22", stream.str());
}

TEST(IntegerClass, string_constructor_3){
    Integer<int> test_integer("-22");
    ostringstream stream;
    stream << test_integer;
    ASSERT_EQ("-22", stream.str());
}

TEST(IntegerClass, string_constructor_4){
    Integer<int> test_integer("00000001");
    ostringstream stream;
    stream << test_integer;
    ASSERT_EQ("1", stream.str());
}

TEST(IntegerClass, string_constructor_5){
    Integer<int> test_integer("1234567891011121314151617181920");
    ostringstream stream;
    stream << test_integer;
    ASSERT_EQ("1234567891011121314151617181920", stream.str());
}

// ----------
// operator -
// ----------

TEST(IntegerClass, negate_1){
    Integer<int> test(1);
    test = -test;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-1", stream.str());
}

TEST(IntegerClass, negate_2){
    Integer<int> test(1);
    test = -test;
    test = -test;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("1", stream.str());
}

TEST(IntegerClass, negate_3){
    Integer<int> test(-1);
    test = -test;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("1", stream.str());
}

// ------------------
// multiplies_digits
// ------------------

// TEST(IntegerClass, multiplies_digits_1){
//     Integer<int> test_integer1(5);
//     Integer<int> test_integer2(6);
//     Integer<int> test_integer3(000);

//     multiplies_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

//     ASSERT_EQ(30, test_integer3);
// }

// ---
// abs
// ---

TEST(IntegerClass, abs_1){
    Integer<int> test(-1);
    test.abs();

    ostringstream stream;
    stream << test;

    ASSERT_EQ("1", stream.str());
}

TEST(IntegerClass, abs_2){
    Integer<int> test(1);
    test.abs();

    ostringstream stream;
    stream << test;

    ASSERT_EQ("1", stream.str());
}

TEST(IntegerClass, abs_3){
    Integer<int> test(1);
    test = -test;
    test = test.abs();

    ostringstream stream;
    stream << test;

    ASSERT_EQ("1", stream.str());
}

// -----------
// operator +=
// -----------

// ++

TEST(IntegerClass, plus_equals_1){
    Integer<int> test(1);

    test += 1;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("2", stream.str());
}

TEST(IntegerClass, plus_equals_2){
    Integer<int> test(5);

    test += 5;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("10", stream.str());
}

TEST(IntegerClass, plus_equals_3){
    Integer<int> test(100);

    test += 50;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("150", stream.str());
}

TEST(IntegerClass, plus_equals_4){
    Integer<int> test(50);

    test += 100;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("150", stream.str());
}

TEST(IntegerClass, plus_equals_5){
    Integer<int> test(999);

    test += 1;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("1000", stream.str());
}

// -+

TEST(IntegerClass, plus_equals_6){
    Integer<int> test(-1);

    test += 1;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("0", stream.str());
}

TEST(IntegerClass, plus_equals_7){
    Integer<int> test(-10);

    test += 20;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("10", stream.str());
}

// --

TEST(IntegerClass, plus_equals_8){
    Integer<int> test(-10);

    test += -10;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-20", stream.str());
}

TEST(IntegerClass, plus_equals_9){
    Integer<int> test(-10);

    test += -5;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-15", stream.str());
}

TEST(IntegerClass, plus_equals_10){
    Integer<int> test(-999);

    test += -1;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-1000", stream.str());
}

// +-

TEST(IntegerClass, plus_equals_11){
    Integer<int> test(10);

    test += -10;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("0", stream.str());
}

TEST(IntegerClass, plus_equals_12){
    Integer<int> test(10);

    test += -20;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-10", stream.str());
}

TEST(IntegerClass, plus_equals_13){
    Integer<int> test(0);

    test += -10;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-10", stream.str());
}

// -----------
// operator -=
// -----------

// ++

TEST(IntegerClass, minus_equals_1){
    Integer<int> test(1);

    test -= 1;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("0", stream.str());
}

TEST(IntegerClass, minus_equals_2){
    Integer<int> test(5);

    test -= 2;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("3", stream.str());
}

TEST(IntegerClass, minus_equals_3){
    Integer<int> test(100);

    test -= 50;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("50", stream.str());
}

TEST(IntegerClass, minus_equals_4){
    Integer<int> test(50);

    test -= 100;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-50", stream.str());
}

TEST(IntegerClass, minus_equals_5){
    Integer<int> test(1000);

    test -= 1;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("999", stream.str());
}

// -+

TEST(IntegerClass, minus_equals_6){
    Integer<int> test(-1);

    test -= 1;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-2", stream.str());
}

TEST(IntegerClass, minus_equals_7){
    Integer<int> test(-10);

    test -= 20;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-30", stream.str());
}

// --

TEST(IntegerClass, minus_equals_8){
    Integer<int> test(-10);

    test -= -10;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("0", stream.str());
}

TEST(IntegerClass, minus_equals_9){
    Integer<int> test(-10);

    test -= -5;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-5", stream.str());
}

TEST(IntegerClass, minus_equals_10){
    Integer<int> test(-1000);

    test -= -1;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-999", stream.str());
}

// +-

TEST(IntegerClass, minus_equals_11){
    Integer<int> test(10);

    test -= -10;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("20", stream.str());
}

TEST(IntegerClass, minus_equals_12){
    Integer<int> test(10);

    test -= -20;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("30", stream.str());
}

TEST(IntegerClass, minus_equals_13){
    Integer<int> test(0);

    test -= -20;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("20", stream.str());
}

TEST(IntegerClass, minus_equals_14){
    Integer<int> test(0);

    test -= 10;

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-10", stream.str());
}

// ------------
// operator >>=
// ------------

TEST(IntegerClass, right_shift_equals_1){
    Integer<int> test_integer(10);
    ostringstream stream;
    
    stream << (test_integer >>= 1);

    ASSERT_EQ("1", stream.str());
}

TEST(IntegerClass, right_shift_equals_2){
    Integer<int> test_integer(-10);
    ostringstream stream;
    
    stream << (test_integer >>= 1);

    ASSERT_EQ("-1", stream.str());
}

TEST(IntegerClass, right_shift_equals_3){
    Integer<int> test_integer(100);
    ostringstream stream;
    
    stream << (test_integer >>= 2);

    ASSERT_EQ("1", stream.str());
}

// ------------
// operator <<=
// ------------

TEST(IntegerClass, left_shift_equals_1){
    Integer<int> test_integer(10);
    ostringstream stream;
    
    stream << (test_integer <<= 1);

    ASSERT_EQ("100", stream.str());
}

TEST(IntegerClass, left_shift_equals_2){
    Integer<int> test_integer(-10);
    ostringstream stream;
    
    stream << (test_integer <<= 1);

    ASSERT_EQ("-100", stream.str());
}

TEST(IntegerClass, left_shift_equals_3){
    Integer<int> test_integer(100);
    ostringstream stream;
    
    stream << (test_integer <<= 2);

    ASSERT_EQ("10000", stream.str());
}

// -----------
// operator *=
// -----------

TEST(IntegerClass, times_equals_1){
    Integer<int> test_integer(5);
    ostringstream stream;
    
    stream << (test_integer *= 2);

    ASSERT_EQ("10", stream.str());
}

TEST(IntegerClass, times_equals_2){
    Integer<int> test_integer(-5);
    ostringstream stream;
    
    stream << (test_integer *= 2);

    ASSERT_EQ("-10", stream.str());
}

TEST(IntegerClass, times_equals_3){
    Integer<int> test_integer(-5);
    ostringstream stream;
    
    stream << (test_integer *= -2);

    ASSERT_EQ("10", stream.str());
}

TEST(IntegerClass, times_equals_4){
    Integer<int> test_integer(5);
    ostringstream stream;
    
    stream << (test_integer *= -2);

    ASSERT_EQ("-10", stream.str());
}

// -----------
// operator /=
// -----------

TEST(IntegerClass, divide_equals_1){
    Integer<int> test_integer(10);
    ostringstream stream;
    
    stream << (test_integer /= 2);

    ASSERT_EQ("5", stream.str());
}

TEST(IntegerClass, divide_equals_2){
    Integer<int> test_integer(-10);
    ostringstream stream;
    
    stream << (test_integer /= 2);

    ASSERT_EQ("-5", stream.str());
}

TEST(IntegerClass, divide_equals_3){
    Integer<int> test_integer(-10);
    ostringstream stream;
    
    stream << (test_integer /= -2);

    ASSERT_EQ("5", stream.str());
}

TEST(IntegerClass, divide_equals_4){
    Integer<int> test_integer(10);
    ostringstream stream;
    
    stream << (test_integer /= -2);

    ASSERT_EQ("-5", stream.str());
}

TEST(IntegerClass, divide_equals_5){
    Integer<int> test_integer(100000);
    ostringstream stream;
    
    stream << (test_integer /= 2);

    ASSERT_EQ("50000", stream.str());
}

TEST(IntegerClass, divide_equals_6){
    Integer<int> test_integer("10000000000000000000000000000000000");
    ostringstream stream;
    
    stream << (test_integer /= Integer<int>("10000000000000000000000000000000000"));

    ASSERT_EQ("1", stream.str());
}

TEST(IntegerClass, divide_equals_7){
    Integer<int> test_integer("100000000000000000000000000000000000000000000000000000000000000000000");
    ostringstream stream;
    
    stream << (test_integer /= Integer<int>("100000000000000000000000000000000000000000000000000000000000000000000"));

    ASSERT_EQ("1", stream.str());
}

TEST(IntegerClass, divide_equals_8){
    Integer<int> test_integer("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    ostringstream stream;
    
    stream << (test_integer /= Integer<int>("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    ASSERT_EQ("1", stream.str());
}

// -----------
// operator %=
// -----------

TEST(IntegerClass, mod_equals_1){
    Integer<int> test_integer(10);
    
    test_integer %= 10;

    ASSERT_EQ(0, test_integer);
}

TEST(IntegerClass, mod_equals_2){
    Integer<int> test_integer(11);
    
    test_integer %= 10;

    ASSERT_EQ(1, test_integer);
}

TEST(IntegerClass, mod_equals_3){
    Integer<int> test_integer(12);
    
    test_integer %= 10;

    ASSERT_EQ(2, test_integer);
}

TEST(IntegerClass, mod_equals_4){
    Integer<int> test_integer(13);
    
    test_integer %= 10;

    ASSERT_EQ(3, test_integer);
}

TEST(IntegerClass, mod_equals_5){
    Integer<int> test_integer(14);
    
    test_integer %= 10;

    ASSERT_EQ(4, test_integer);
}

TEST(IntegerClass, mod_equals_6){
    Integer<int> test_integer(15);
    
    test_integer %= 10;

    ASSERT_EQ(5, test_integer);
}

TEST(IntegerClass, mod_equals_7){
    Integer<int> test_integer(16);
    
    test_integer %= 10;

    ASSERT_EQ(6, test_integer);
}

TEST(IntegerClass, mod_equals_8){
    Integer<int> test_integer(17);
    
    test_integer %= 10;

    ASSERT_EQ(7, test_integer);
}

TEST(IntegerClass, mod_equals_9){
    Integer<int> test_integer(18);
    
    test_integer %= 10;

    ASSERT_EQ(8, test_integer);
}

TEST(IntegerClass, mod_equals_10){
    Integer<int> test_integer(19);
    
    test_integer %= 10;

    ASSERT_EQ(9, test_integer);
}

TEST(IntegerClass, mod_equals_11){
    Integer<int> test_integer(-10);
    
    test_integer %= 10;

    ASSERT_EQ(-10 % 10, test_integer);
}

TEST(IntegerClass, mod_equals_12){
    Integer<int> test_integer(-71);
    
    test_integer %= 4;

    ASSERT_EQ(-71 % 4, test_integer);
}

TEST(IntegerClass, mod_equals_13){
    Integer<int> test_integer(123456789);
    
    test_integer %= 54321;

    ASSERT_EQ(123456789 % 54321, test_integer);
}

TEST(IntegerClass, mod_equals_14){
    Integer<int> test_integer(123456789);
    
    test_integer %= 678910;

    ASSERT_EQ(123456789 % 678910, test_integer);
}

TEST(IntegerClass, mod_equals_15){
    Integer<int> test_integer(-123456789);
    
    test_integer %= 678910;

    ASSERT_EQ(-123456789 % 678910, test_integer);
}

// ---
// pow
// ---

TEST(IntegerClass, pow_1){
    Integer<int> test_integer(2);
    ostringstream stream;
    
    stream << (test_integer.pow(2));

    ASSERT_EQ("4", stream.str());
}

TEST(IntegerClass, pow_2){
    Integer<int> test_integer(2);
    ostringstream stream;
    
    stream << (test_integer.pow(10));

    ASSERT_EQ("1024", stream.str());
}

TEST(IntegerClass, pow_3){
    Integer<int> test_integer(-2);
    ostringstream stream;
    
    stream << (test_integer.pow(3));

    ASSERT_EQ("-8", stream.str());
}

TEST(IntegerClass, pow_4){
    Integer<int> test_integer(10);
    ostringstream stream;
    
    stream << (test_integer.pow(2));

    ASSERT_EQ("100", stream.str());
}

TEST(IntegerClass, pow_5){
    Integer<int> test_integer(10);
    ostringstream stream;
    
    stream << (test_integer.pow(10));

    ASSERT_EQ("10000000000", stream.str());
}


    // ----------------
    // IntegerFunctions
    // ----------------

// -----------------
// shift_left_digits
// -----------------

TEST(IntegerFunctions, shift_left_digits_1) {
    Integer<int> test_integer1 = (123);
    Integer<int> test_integer2 = (999999);

    shift_left_digits(test_integer1.begin(), test_integer1.end(), 3, test_integer2.begin());

    ASSERT_EQ(123000, test_integer2);
}

TEST(IntegerFunctions, shift_left_digits_2) {
    Integer<int> test_integer1 = (2);
    Integer<int> test_integer2 = (999);

    shift_left_digits(test_integer1.begin(), test_integer1.end(), 2, test_integer2.begin());

    ASSERT_EQ(200, test_integer2);
}

TEST(IntegerFunctions, shift_left_digits_3){
    Integer<int> test_integer1(555);
    Integer<int> test_integer2(999);

    shift_left_digits(test_integer1.begin(), test_integer1.end(), 0, test_integer2.begin());

    ASSERT_EQ(555, test_integer2);
}

TEST(IntegerFunctions, shift_left_digits_4){
    Integer<int> test_integer1(5);
    Integer<int> test_integer2(9999);

    shift_left_digits(test_integer1.begin(), test_integer1.end(), 3, test_integer2.begin());

    ASSERT_EQ(5000, test_integer2);
}

TEST(IntegerFunctions, shift_left_digits_5){
    Integer<int> test_integer1(1);
    Integer<int> test_integer2("9999999999");

    shift_left_digits(test_integer1.begin(), test_integer1.end(), 9, test_integer2.begin());

    ASSERT_EQ(Integer<int>("1000000000"), test_integer2);
}

// ------------------
// shift_right_digits
// ------------------

TEST(IntegerFunctions, shift_right_digits_1) {
    Integer<int> test_integer1 = (123456);
    Integer<int> test_integer2 = (999);

    shift_right_digits(test_integer1.begin(), test_integer1.end(), 3, test_integer2.begin());

    ASSERT_EQ(123, test_integer2);
}

TEST(IntegerFunctions, shift_right_digits_2) {
    Integer<int> test_integer1 = (200);
    Integer<int> test_integer2 = (9);

    shift_right_digits(test_integer1.begin(), test_integer1.end(), 2, test_integer2.begin());

    ASSERT_EQ(2, test_integer2);
}

TEST(IntegerFunctions, shift_right_digits_3){
    Integer<int> test_integer1(555);
    Integer<int> test_integer2(999);

    shift_right_digits(test_integer1.begin(), test_integer1.end(), 0, test_integer2.begin());

    ASSERT_EQ(555, test_integer2);
}

TEST(IntegerFunctions, shift_right_digits_4){
    Integer<int> test_integer1(555);
    Integer<int> test_integer2(9);

    shift_right_digits(test_integer1.begin(), test_integer1.end(), 3, test_integer2.begin());

    ASSERT_EQ(0, test_integer2);
}

TEST(IntegerFunctions, shift_right_digits_5){
    Integer<int> test_integer1(1);
    Integer<int> test_integer2(1);

    shift_right_digits(test_integer1.begin(), test_integer1.end(), 1, test_integer2.begin());

    ASSERT_EQ(0, test_integer2);
}

// ---
// abs
// ---

TEST(IntegerFunctions, abs_1){
    Integer<int> test(-1);
    test = abs(test);

    ostringstream stream;
    stream << test;

    ASSERT_EQ("1", stream.str());
}

TEST(IntegerFunctions, abs_2){
    Integer<int> test(-1);
    abs(test);

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-1", stream.str());
}

TEST(IntegerFunctions, abs_3){
    Integer<int> test(1);
    test = -abs(-test.abs());

    ostringstream stream;
    stream << test;

    ASSERT_EQ("-1", stream.str());
}

// -----------
// operator <<
// -----------

TEST(IntegerFunctions, print_1){
    Integer<int> test_integer(12345);

    ostringstream stream;

    stream << test_integer;

    ASSERT_EQ("12345", stream.str());
}

TEST(IntegerFunctions, print_2){
    Integer<int> test_integer(0005);

    ostringstream stream;

    stream << test_integer;

    ASSERT_EQ("5", stream.str());
}

TEST(IntegerFunctions, print_3){
    Integer<int> test_integer(-5);

    ostringstream stream;

    stream << test_integer;

    ASSERT_EQ("-5", stream.str());
}

// -----------
// operator ==
// -----------

TEST(IntegerFunctions, equal_1){
    Integer<int> test_integer1(12345);
    Integer<int> test_integer2(12345);

    ASSERT_TRUE(test_integer1 == test_integer2);
}

TEST(IntegerFunctions, equal_2){
    Integer<int> test_integer1(12345);
    Integer<int> test_integer2(12346);

    ASSERT_FALSE(test_integer1 == test_integer2);
}

TEST(IntegerFunctions, equal_3){
    Integer<int> test_integer1(12345);
    Integer<int> test_integer2(123456);

    ASSERT_FALSE(test_integer1 == test_integer2);
}

TEST(IntegerFunctions, equal_4){
    Integer<int> test_integer1(1);
    Integer<int> test_integer2(-1);

    ASSERT_FALSE(test_integer1 == test_integer2);
}

TEST(IntegerFunctions, equal_5){
    Integer<int> test_integer1(0);
    Integer<int> test_integer2(0);

    ASSERT_TRUE(test_integer1 == test_integer2);
}

TEST(IntegerFunctions, equal_6){
    Integer<int> test_integer1(0);

    ASSERT_TRUE(test_integer1 == 0);
}

TEST(IntegerFunctions, equal_7){
    Integer<int> test_integer1(-20);

    ASSERT_TRUE(test_integer1 == -20);
}

TEST(IntegerFunctions, equal_8){
    Integer<int> test_integer1(51);

    ASSERT_FALSE(test_integer1 == 15);
}

TEST(IntegerFunctions, equal_9){
    Integer<int> test_integer1(10);

    ASSERT_FALSE(test_integer1 == 0);
}

TEST(IntegerFunctions, equal_10){
    Integer<int> test_integer1(-10);

    ASSERT_FALSE(test_integer1 == 0);
}

// -----------
// operator <
// -----------

// ++

TEST(IntegerFunctions, less_than_1){
    ASSERT_FALSE(Integer<int>(1001) < 1001);
}

TEST(IntegerFunctions, less_than_2){
    ASSERT_TRUE(Integer<int>(1001) < 1002);
}

TEST(IntegerFunctions, less_than_3){
    ASSERT_FALSE(Integer<int>(2002) < 2001);
}

// --

TEST(IntegerFunctions, less_than_4){
    ASSERT_FALSE(Integer<int>(-1001) < -1001);
}

TEST(IntegerFunctions, less_than_5){
    ASSERT_TRUE(Integer<int>(-2001) < -1001);
}

TEST(IntegerFunctions, less_than_6){
    ASSERT_FALSE(Integer<int>(-1001) < -2001);
}

// +-

TEST(IntegerFunctions, less_than_7){
    ASSERT_FALSE(Integer<int>(1001) < -1001);
}

// -+

TEST(IntegerFunctions, less_than_8){
    ASSERT_TRUE(Integer<int>(-1001) < 1001);
}

// ++

TEST(IntegerFunctions, less_than_9){
    ASSERT_TRUE(Integer<int>(1) < 1000);
}

TEST(IntegerFunctions, less_than_10){
    ASSERT_TRUE(Integer<int>(7) < 23);
}

TEST(IntegerFunctions, less_than_11){
    ASSERT_FALSE(Integer<int>(37) < 28);
}

// --

TEST(IntegerFunctions, less_than_12){
    ASSERT_FALSE(Integer<int>(-7) < -12);
}

TEST(IntegerFunctions, less_than_13){
    ASSERT_TRUE(Integer<int>(-2) < -1);
}

TEST(IntegerFunctions, less_than_14){
    ASSERT_FALSE(Integer<int>(-28) < -34);
}

// +-

TEST(IntegerFunctions, less_than_15){
    ASSERT_FALSE(Integer<int>(6) < -35);
}

// -+

TEST(IntegerFunctions, less_than_16){
    ASSERT_TRUE(Integer<int>(-15) < 23);
}

// 0X

TEST(IntegerFunctions, less_than_17){
    ASSERT_TRUE(Integer<int>(0) < 23);
}

TEST(IntegerFunctions, less_than_18){
    ASSERT_FALSE(Integer<int>(0) < 0);
}

TEST(IntegerFunctions, less_than_19){
    ASSERT_FALSE(Integer<int>(0) < -8);
}

// X0

TEST(IntegerFunctions, less_than_20){
    ASSERT_TRUE(Integer<int>(-2) < 0);
}

TEST(IntegerFunctions, less_than_21){
    ASSERT_FALSE(Integer<int>(8) < 0);
}

TEST(IntegerFunctions, less_than_22){
    ASSERT_FALSE(Integer<int>(71) < 0);
}

// -----------
// plus_digits
// -----------

TEST(IntegerFunctions, plus_digits_1){
    Integer<int> test_integer1(1);
    Integer<int> test_integer2(1);
    Integer<int> test_integer3(1);

    plus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(2, test_integer3);
}

TEST(IntegerFunctions, plus_digits_2){
    Integer<int> test_integer1(5);
    Integer<int> test_integer2(5);
    Integer<int> test_integer3(20);

    plus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(10, test_integer3);
}

TEST(IntegerFunctions, plus_digits_3){
    Integer<int> test_integer1(1111);
    Integer<int> test_integer2(1111);
    Integer<int> test_integer3(1000);

    plus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(2222, test_integer3);
}

TEST(IntegerFunctions, plus_digits_4){
    Integer<int> test_integer1(9999);
    Integer<int> test_integer2(9999);
    Integer<int> test_integer3(10000);

    plus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(19998, test_integer3);
}

TEST(IntegerFunctions, plus_digits_5){
    Integer<int> test_integer1(9999);
    Integer<int> test_integer2(1);
    Integer<int> test_integer3(55555);

    plus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(10000, test_integer3);
}

// ------------
// minus_digits
// ------------

TEST(IntegerFunctions, minus_digits_1){
    Integer<int> test_integer1(1);
    Integer<int> test_integer2(1);
    Integer<int> test_integer3(1);

    minus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(0, test_integer3);
}

TEST(IntegerFunctions, minus_digits_2){
    Integer<int> test_integer1(10);
    Integer<int> test_integer2(5);
    Integer<int> test_integer3(9);

    minus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(5, test_integer3);
}

TEST(IntegerFunctions, minus_digits_3){
    Integer<int> test_integer1(5);
    Integer<int> test_integer2(10);
    Integer<int> test_integer3(9);

    minus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(5, test_integer3);
}

TEST(IntegerFunctions, minus_digits_4){
    Integer<int> test_integer1(2);
    Integer<int> test_integer2(7);
    Integer<int> test_integer3(9);

    minus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(5, test_integer3);
}

TEST(IntegerFunctions, minus_digits_5){
    Integer<int> test_integer1(1000);
    Integer<int> test_integer2(1);
    Integer<int> test_integer3(555);

    minus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(999, test_integer3);
}

TEST(IntegerFunctions, minus_digits_6){
    Integer<int> test_integer1(1001);
    Integer<int> test_integer2(9);
    Integer<int> test_integer3(555);

    minus_digits(test_integer1.begin(), test_integer1.end(), test_integer2.begin(), test_integer2.end(), test_integer3.begin());

    ASSERT_EQ(992, test_integer3);
}

// ----------------
// RunInteger tests
// ----------------

TEST(RunInteger, 20_prime_vector){
    const Integer<int> n = Integer<int>(2).pow(4423) - 1;
}

TEST(RunInteger, 20_prime_deque){
    const Integer< int, std::deque<int> > n = Integer< int, std::deque<int> >(2).pow(4423) - 1;
}

// -----------------------
// prime computation tests
// -----------------------

TEST(Primes, 19_prime){
    const Integer<int> n = Integer<int>(2).pow(4253) - 1;
    ostringstream stream;
    stream << n;

    ASSERT_EQ("190797007524439073807468042969529173669356994749940177394741882673528979787005053706368049835514900244303495954950709725762186311224148828811920216904542206960744666169364221195289538436845390250168663932838805192055137154390912666527533007309292687539092257043362517857366624699975402375462954490293259233303137330643531556539739921926201438606439020075174723029056838272505051571967594608350063404495977660656269020823960825567012344189908927956646011998057988548630107637380993519826582389781888135705408653045219655801758081251164080554609057468028203308718724654081055323215860189611391296030471108443146745671967766308925858547271507311563765171008318248647110097614890313562856541784154881743146033909602737947385055355960331855614540900081456378659068370317267696980001187750995491090350108417050917991562167972281070161305972518044872048331306383715094854938415738549894606070722584737978176686422134354526989443028353644037187375385397838259511833166416134323695660367676897722287918773420968982326089026150031515424165462111337527431154890666327374921446276833564519776797633875503548665093914556482031482248883127023777039667707976559857333357013727342079099064400455741830654320379350833236245819348824064783585692924881021978332974949906122664421376034687815350484991", stream.str());
}

TEST(Primes, 20_prime){
    const Integer<int> n = Integer<int>(2).pow(4423) - 1;
    ostringstream stream;
    stream << n;

    ASSERT_EQ("285542542228279613901563566102164008326164238644702889199247456602284400390600653875954571505539843239754513915896150297878399377056071435169747221107988791198200988477531339214282772016059009904586686254989084815735422480409022344297588352526004383890632616124076317387416881148592486188361873904175783145696016919574390765598280188599035578448591077683677175520434074287726578006266759615970759521327828555662781678385691581844436444812511562428136742490459363212810180276096088111401003377570363545725120924073646921576797146199387619296560302680261790118132925012323046444438622308877924609373773012481681672424493674474488537770155783006880852648161513067144814790288366664062257274665275787127374649231096375001170901890786263324619578795731425693805073056119677580338084333381987500902968831935913095269821311141322393356490178488728982288156282600813831296143663845945431144043753821542871277745606447858564159213328443580206422714694913091762716447041689678070096773590429808909616750452927258000843500344831628297089902728649981994387647234574276263729694848304750917174186181130688518792748622612293341368928056634384466646326572476167275660839105650528975713899320211121495795311427946254553305387067821067601768750977866100460014602138408448021225053689054793742003095722096732954750721718115531871310231057902608580607", stream.str());
}

TEST(Primes, 21_prime){
    const Integer<int> n = Integer<int>(2).pow(9689) - 1;
    ostringstream stream;
    stream << n;

    ASSERT_EQ("4782202788054612029528392986600059097414971724022365008513345109918378950942662970278927686112707894586824720981524256319306585052676834087480834429433264797425893247623688331021633208954847354805799943341309825989013743806187109581043148680813778321530496715601563282624414040398143207622036272190408590790537203475256105564071579263867875240985573356522656108542128577321057879052328865035355873615679363655889925711574420153832091752422843046918811427400662135559303516853703976812686385750376227787949580582081831261725701003498206512329872677233489510953469375683037038373999696771585788905639115522613405495707184524158219208223766442059014593330657009722153962376853423770486138578089775621301167811299166407361746606697808186757966914671246073712904200588408923186387737887675292886953797066980967406053530122853539036965490224784924649007954898678503314655546475504501686187354866964374552614120640782949622452027788962138602665933147687696322089504278791624651519312327831756553779377194524673395819281486668576384019590720179413349582970319393884388810494546040342087536563628332152073181614300721769371426238517540520845214665313301183551962591849558938499025348780376716477073930634436840084468255937443451690315999349137664638968972614199015304906547819056227171224947070739716300953775743441307920501863532234466545645695774331885044978250148663467372130392099894852145190998232878772486650513010816769902892518719250066947215706536216248696240569256865554296221552211560427778662545936998801070186162601476474293459830183651273363462732675883060701410359254829149774339297173680765610959599911309189788238350131635672661435969218239977196933874395403996623675580528211207136396370858056051160781770985452576988032333812939272752101944629527490313835551985197095928885236415301789218675141014541203096191270934369039522098280317668942061325572349643638403056487349290884223786292887472231219032385281034091824306618947740727265524284893304474861454942076799041739447165838281671410435831206790501914527326287370339974707206016882562827404270170322606727980343479326425730091839813077719322455394763960606588214326603156141490740557698055166263044447583756711516490181193442236859424151843795389335765432129944054855345155859273424561825146813714720606287781021240923708021492298349635179527270302962970156927686511635050080407282674252362644695710769768866137302789313609674382719017385508484663373476120843567983065059558072935110637544240807350667082987233779768874938983584523095638996120616318634391967112086464384649470963230072729200912586147267999762496709852769503535733924416202657720741248683592202828983311140833923302433917797976990311425843619350936754483811194408812763388084204451804912454383884180800945275626668057628954763384641305107753773247082495804533355717481965025070819730466422826105697510564289798951182192885976352229053898948737614642139910911535864505818992696826225754111", stream.str());
}

TEST(Primes, 22_prime){
    const Integer<int> n = Integer<int>(2).pow(9941) - 1;
    ostringstream stream;
    stream << n;

    ASSERT_EQ("34608828249085121524296039576741331672262866890023854779048928344500622080983411446436437554415370753366448674763505018641470709332373970608376690404229265789647993709760358469552319045484910050304149809818540283507159683562232941968059762281334544739720849260904855192770626054911793590389060795981163838721432994278763633095377438194844866471124967685798888172212033000821469684464956146997194126921284336206463313859537577200462442029064681326087558257488470489384243989270236884978643063093004422939603370010546595386302009073043944482202559097406700597330570799507832963130938739885080198416258635194522913042562936679859587495721031173747796418895060701941717506001937152430032363631934265798516236047451209089864707430780362298307038193445486493756647991804258775574973833903315735082891029392359352758617185019942554834671861074548772439880729606244911940066680112823824095816458261761861746604034802056466823143718255492784779380991749580255263323326536457743894150848953969902818530057870876229329803338285735419228259022169602665532210834789602051686546011466737981306056247480055071718250333737502267307344178512950738594330684340802698228963986562732597175372087295649072830289749771358330867951508710859216743218522918811670637448496498549094430541277444079407989539857469452772132166580885754360477408842913327292948696897496141614919739845432835894324473601387609643750514699215032683744527071718684091832170948369396280061184593746143589068811190253101873595319156107319196071150598488070027088705842749605203063194191166922106176157609367241948160625989032127984748081075324382632093913796444665700601391278360323002267434295194325607280661260119378719405151497555187549252134264394645963853964913309697776533329401822158003182889278072368602128982710306618115118964131893657845400296860012420391376964670183983594954112484565597312460737798777092071706710824503707457220155015899591766244957768006802482976673920392995410164224776445671222149803657927708412925555542817045572430846389988129960519227313987291200902060882060733762075892299473666405897427035811786879875694315078654420055603469625309399653955932310466430039146465805452965014040019423897552675534768248624631951431493188170905972588780111850281190559073677771187432814088678674286302108275149258477101296451833651979717375170900505673645964696355331369819296000267389583289299126738345726980325998955997501176664201042888546085699446442834195232948787488410595750197438786353119204210855804692460582533832967771946911459901921324984968810021189968284941331573164056304725480868921823442538199590383852412786840833479611419970101792978355653650755329138298654246225346827207503606740745956958127383748717825918527473164970582095181312905519242710280573023145554793628499010509296055849712377978984921839997037415897674154830708629145484724536724572622450131479992681684310464449439022250504859250834761894788889552527898400988196200014868575640233136509145628127191354858275083907891469979019426224883789463551", stream.str());
}

