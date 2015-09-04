// ------------------------------
// projects/c++/integer/Integer.h
// Copyright (C) 2015
// Glenn P. Downing
// ------------------------------

#ifndef Integer_h
#define Integer_h

#define MAX_VALUE 9
#define MIN_VALUE 0

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <iterator>  // distance
#include <stack>
#include <cmath>     // abs
// -----------------
// shift_left_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * ([b, e) << n) => x
 * Integer I = 12345;
 * Integer x = 0;
 * shift_left_digits(I.begin()+1, I.begin()+3, 4, x.begin());
 * assert(x == 230000);
 */
template <typename II, typename FI>
FI shift_left_digits (II b, II e, int n, FI x) {
    // 07 => 007
    while(n-- > 0){
        *(x++) = 0;
    }
    while(b != e){
        *(x++) = *(b++);
    }
    return x;
}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
template <typename II, typename FI>
FI shift_right_digits (II b, II e, int n, FI x) {
    // 07 => 7
    while (n-- > 0){
        assert(b != e);
        ++b;
    }
    if (b != e)
        while (b != e){
            *(x++) = *(b++);
        }
    else{
        *(x++) = 0;
    }
    return x;
}

// -----------
// plus_digits
// -----------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * ([b1, e1) + [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    int carry = 0;
    while (b1 != e1 || b2 != e2){
        int value1 = (b1 != e1) ? *b1 : 0;
        int value2 = (b2 != e2) ? *b2 : 0;

        *x = value1 + value2 + carry;

        carry = 0;

        if (*x > MAX_VALUE){
            carry = *x / 10;
            assert(carry < 2);
            *x %= 10;
            assert(*x <= MAX_VALUE);
        }
        if (b1 != e1)
            ++b1;
        if (b2 != e2)
            ++b2;
        ++x;
    }
    // add the final digit, if necessary
    if (carry > 0){
        *x = carry;
    }
    return x;
}

// ------------
// minus_digits
// ------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    int borrow = 0;
    while (b1 != e1 || b2 != e2){
        int value1 = (b1 != e1) ? *b1 : 0;
        int value2 = (b2 != e2) ? *b2 : 0;

        if (borrow < 0){
            value1 -= 1;
            borrow = 0;
        }

        if (value2 > value1){
            borrow = 10;
        }

        *x = (value1 + borrow) - value2;

        assert(*x >= 0);

        if (borrow > 0){
            borrow = -1;
        }

        if (b1 != e1)
            ++b1;

        if (b2 != e2)
            ++b2;
        ++x;
    }
    if (borrow < 0){
        *x = borrow;
    }
    return x;
}

// -----------------
// multiplies_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * ([b1, e1) * [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    
    // int mult = 1;
    // std::copy(b2, e2, x);
    // while(b1 != e1){
    //     for(int i = 0; i < (*b1)*mult; ++i){
    //         plus_digits(b2, e2, x, x+(e2-b2), x);
    //     }
    //     ++b1;
    //     mult *= 10;
    // }
    return x;
}

// --------------
// divides_digits
// --------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * ([b1, e1) / [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    // <your code>
    return x;
}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    // -----------
    // operator ==
    // -----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      a boolean that is true if the two Integers are equivalent
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        if (lhs.is_negative != rhs.is_negative) // both have same sign
            return false;
        if (lhs._x.size() != rhs._x.size()) // both have same size
            return false;
        return (lhs._x == rhs._x);
    }

    // -----------
    // operator !=
    // -----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      a boolean that is true if the two Integers are not equivalent
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) {
        return !(lhs == rhs);
    }

    // ----------
    // operator <
    // ----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      a boolean that is true if the lhs is less than the rhs
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        // -+
        if (lhs.is_negative && !rhs.is_negative) // -20 < 2
            return true;
        // +-
        if (!lhs.is_negative && rhs.is_negative) //  20 > 2 
            return false;

        assert(lhs.is_negative == rhs.is_negative);

        // if they are the same size
        if (lhs._x.size() == rhs._x.size()){

            int size = lhs._x.size() - 1;

            if (!lhs.is_negative && !rhs.is_negative){
                // if both positive
                
                while (size >= 0){
                    if (lhs._x[size] > rhs._x[size]){
                        return false;
                    }
                    if (lhs._x[size] < rhs._x[size]){
                        return true;
                    }
                    --size;
                }
            }
            // -999 < -998
            else if (lhs.is_negative && rhs.is_negative){
                // both negative

                while (size >= 0){
                    if (rhs._x[size] < lhs._x[size]){
                        return true;
                    }
                    if (rhs._x[size] > lhs._x[size]){
                        return false;
                    }
                    --size;
                }
            }

            assert(lhs == rhs);
            return false;
        }
        // they're not the same size
        return (!lhs.is_negative && !rhs.is_negative) ? lhs._x.size() < rhs._x.size() : rhs._x.size() < lhs._x.size();
    }


    // ----------
    // operator <
    // ----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      a boolean that is true if the lhs is less than the rhs
     */
    friend bool abs_less_than (const Integer& lhs, const Integer& rhs) {
        // if they are the same size
        if (lhs._x.size() == rhs._x.size()){

            int size = lhs._x.size() - 1;

            while (size >= 0){
                if (lhs._x[size] > rhs._x[size]){
                    return false;
                }
                if (lhs._x[size] < rhs._x[size]){
                    return true;
                }
                --size;
            }

            return false;
        }
        // they're not the same size
        return lhs._x.size() < rhs._x.size();
    }

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      a boolean that is true if the lhs is less than the rhs
     */
    friend bool abs_less_than_equal (const Integer& lhs, const Integer& rhs) {
        // if they are the same size
        if (lhs._x.size() == rhs._x.size()){

            int size = lhs._x.size() - 1;

            while (size >= 0){
                if (lhs._x[size] > rhs._x[size]){
                    return false;
                }
                if (lhs._x[size] < rhs._x[size]){
                    return true;
                }
                --size;
            }

            return true;
        }
        // they're not the same size
        return lhs._x.size() <= rhs._x.size();
    }

    // -----------
    // operator <=
    // -----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      a boolean that is true if the lhs is less than or equal to the rhs
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);
    }

    // ----------
    // operator >
    // ----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      a boolean that is true if the lhs is greater than the rhs
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);
    }

    // -----------
    // operator >=
    // -----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      a boolean that is true if the lhs is greater than or equal to the rhs
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);
    }

    // ----------
    // operator +
    // ----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      an Integer whose value is the sum of lhs and rhs
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;
    }

    // ----------
    // operator -
    // ----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      an Integer whose value is the difference of lhs and rhs
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;
    }

    // ----------
    // operator *
    // ----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      an Integer whose value is the product of lhs and rhs
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;
    }

    // ----------
    // operator /
    // ----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      an Integer whose value is the division of lhs and rhs
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;
    }

    // ----------
    // operator %
    // ----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      an Integer whose value is the remainder after division of lhs and rhs
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;
    }

    // -----------
    // operator <<
    // -----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      an Integer whose value is the lhs * 10^(rhs)
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;
    }

    // -----------
    // operator >>
    // -----------

    /**
     * @param lhs   an Integer object
     * @param rhs   an Integer object 
     * @return      an Integer whose value is the lhs / 10^(rhs)
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;
    }

    // -----------
    // operator <<
    // -----------

    /**
     * @param lhs   an ostream object
     * @param rhs   an Integer object 
     * @return      an ostream object concatenated with the value of rhs
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
        if (rhs.is_negative){
            lhs << "-";
        }
        std::stack<int> digits;
        for (int i : rhs){
            digits.push(i);
        }
        while (!digits.empty()){
            lhs << digits.top();
            digits.pop();
        }
        return lhs;
    }

    // ---
    // abs
    // ---
    
    /**
     * absolute value
     * @param x an Integer object
     * @return  an Integer whose value is the absolute value of lhs
     */
    friend Integer abs (Integer x) {
        return x.abs();
    }

    // ---
    // pow
    // ---

    /**
     * power
     * @param x an Integer object
     * @param e an int
     * @return  an Integer whose value is the result of x^e
     * @throws invalid_argument if ((x == 0) && (e == 0)) || (e < 0)
     */
    friend Integer pow (Integer x, int e) {
        return x.pow(e);
    }

    private:
        // ----
        // data
        // ----

        C _x; // the backing container
        bool is_negative;

    private:
        // -----
        // valid
        // -----

        bool valid () const { // class invariant
            if (_x.empty()) // there must always be at least 1 element in the container
                assert(false);
            if (_x.back() == 0 && is_negative) // cannot have negative zero
                assert(false);
            if (_x.back() < 1 && _x.size() > 1) // cases with extra leading zero values ex. 00001
                assert(false);
            for (T current : _x){ // cannot have misfit values
                if (current < MIN_VALUE || current > MAX_VALUE)
                    assert(false);
            }
            return true;
        }

    public:
        /**
         * shrink
         * @param rhs   an Integer object
         * @return      an Integer with no leading zeroes
         */
        friend void shrink(Integer& rhs){
            while (rhs._x.size() > 1 && rhs._x.back() == 0){
                rhs._x.pop_back();
            }
        }

        /**
         * grow
         * @param rhs   an Integer object
         * @param x     an integer
         * @return      an Integer with n leading zeroes
         */
        friend void grow(Integer& rhs, int n){
            while (n-- > 0){
                rhs._x.push_back(0);
            }
        }

        /**
         * compare_and_resize
         * @param lhs   an Integer object
         * @param rhs   an Integer object
         * @param seed  an int
         * makes the containers of lhs and rhs have the same number of digits
         * Use seed to grow lhs extra spaces
         */
        friend void compare_and_resize(Integer& lhs, const Integer& rhs, const int& seed){
            int size_difference = rhs._x.size() - lhs._x.size();
            if (size_difference < 0){
                size_difference = 0;
            }
            grow(lhs, size_difference + seed);
        }
        friend void compare_and_resize2(Integer& lhs, const Integer& rhs, const int& seed){
            if (rhs._x.size() > lhs._x.size())
                lhs._x.resize(rhs._x.size() + 1);
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         * int constructor
         * @param value     an int
         */
        Integer (int value) {
            is_negative = value < 0;

            value = std::abs(value);

            assert(value >= 0);
            if (value == 0){
                _x.push_back(0);
            }
            while (value > 0){
                _x.push_back(value % 10);
                value /= 10;
            }
            assert(valid());
        }

        /**
         * string constructor
         * @param value     a string
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            std::string::const_iterator begin = value.begin();
            std::string::const_iterator end   = value.end();

            is_negative = (*begin == '-');
            if(is_negative){
                ++begin;
            }
            //delete leading zeroes
            while((*begin - '0') == 0 && begin != end){
                ++begin;
            }
            std::stack<int> digits;
            while (begin != end){
                digits.push(*begin - '0');
                assert(digits.top() >= MIN_VALUE && digits.top() <= MAX_VALUE);
                ++begin;
            }
            while (!digits.empty()){
                _x.push_back(digits.top());
                digits.pop();
            }
            if (_x.size() < 1)
                _x.push_back(0);

            if (!valid())
                throw std::invalid_argument("Integer::Integer()");
        }

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * negation operator
         * @return  an Integer object whose value is the original value * -1
         */
        Integer operator - () const {
            Integer copy = *this;
            copy.is_negative = !copy.is_negative;
            return copy;
        }

        // -----------
        // operator ++
        // -----------

        /**
         * pre-increment operator
         * @return  an Integer object whose value is the original value +1
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;
        }

        /**
         * post-increment operator
         * @return  an Integer object whose value is the original value 
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;
        }

        // -----------
        // operator --
        // -----------

        /**
         * pre-decrement operator
         * @return  an Integer object whose value is the original value - 1
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;
        }

        /**
         * post-decrement operator
         * @return  an Integer object whose value is the original value
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;
        }

        // -----------
        // operator +=
        // -----------

        /**
         * @param rhs   an Integer object
         * @return  an Integer object whose value is the sum of the original caller and rhs
            * If both signs are positive, the answer will be positive.
                Example: 14 - (-6) = 14 + 6 = 20
            * If both signs are negative, the answer will be negative.
                Example: -14 - (+6) = -14 - 6 = -20
            * If the signs are different subtract the smaller absolute value from the larger absolute value. The sign will be the sign of the integer that produced the larger absolute value. 
                Example: 14 - (+6) = 14 - 6 = 8 
                Example: -14 - (-6) = -14 + 6 = -8
         */
        Integer& operator += (const Integer& rhs) {
            if (*this == 0){
                *this = rhs;
                return *this;
            }
            else if (rhs == 0){
                return *this;
            }

            // ++
            if (!is_negative && !rhs.is_negative){
                compare_and_resize(*this, rhs, 1);
                plus_digits(this->begin(), this->end(), rhs.begin(), rhs.end(), this->begin());
            }
            // +-
            else if(!is_negative && rhs.is_negative){
                *this -= -rhs;
            }
            // -+
            else if(is_negative && !rhs.is_negative){
                *this = (rhs - -*this);
            }
            // --
            else if(is_negative && rhs.is_negative){
                *this -= -rhs;
            }
            shrink(*this);
            return *this;
        }

        // -----------
        // operator -=
        // -----------

        /**
         * @param rhs   an Integer object
         * @return  an Integer object whose value is the difference of the original caller and rhs
            * If both signs are positive, the answer will be positive.
                Example: 14 - (-6) = 14 + 6 = 20
            * If both signs are negative, the answer will be negative.
                Example: -14 - (+6) = -14 - 6 = -20
            * If the signs are different subtract the smaller absolute value from the larger absolute value. The sign will be the sign of the integer that produced the larger absolute value. 
                Example: 14 - (+6) = 14 - 6 = 8 
                Example: -14 - (-6) = -14 + 6 = -8
         */
        Integer& operator -= (const Integer& rhs) {
            bool lhs_sign = is_negative;
            bool rhs_sign = !rhs.is_negative;
            if (*this == 0){
                *this = rhs;
                this->is_negative = rhs_sign;
                return *this;
            }
            else if (rhs == 0){
                return *this;
            }
            // If both signs are positive, the answer will be positive.
            if (!is_negative && !rhs_sign){
                compare_and_resize(*this, rhs, 1);
                plus_digits(this->begin(), this->end(), rhs.begin(), rhs.end(), this->begin());
            }
            // If both signs are negative, the answer will be negative.
            else if(is_negative && rhs_sign){
                compare_and_resize(*this, rhs, 1);
                plus_digits(this->begin(), this->end(), rhs.begin(), rhs.end(), this->begin());
            }
            // If the signs are different subtract the smaller absolute value from the larger absolute value.
            // The sign will be the sign of the integer that produced the larger absolute value. 
            else if(is_negative != rhs_sign){
                if (abs_less_than(*this, rhs)){
                    compare_and_resize(*this, rhs, 1);
                    minus_digits(rhs.begin(), rhs.end(), this->begin(), this->end(), begin());
                    is_negative = rhs_sign;
                }
                else if (abs_less_than(rhs, *this)){
                    compare_and_resize(*this, rhs, 1);
                    minus_digits(this->begin(), this->end(), rhs.begin(), rhs.end(), begin());
                    is_negative = lhs_sign;
                }
                else /*if (*this == rhs)*/{
                    *this = 0;
                    is_negative = false;
                }
            }
            shrink(*this);
            return *this;
        }

        // -----------
        // operator *=
        // -----------

        /**
         * @param rhs   an Integer object
         * @return  an Integer object whose value is the product of the original caller and rhs
         */
        Integer& operator *= (const Integer& rhs) {
            if ((this->_x.size() == 1 && this->_x[0] == 0) || (rhs._x.size() == 1 && rhs._x[0] == 0)){
                *this = 0;
                return *this;
            }

            bool rhs_sign = rhs.is_negative;

            Integer this_copy = *this;

            for (Integer i = 2; abs_less_than_equal(i, rhs); ++i){
                *this += this_copy;
            }

            if (rhs_sign)
                is_negative = !is_negative;

            return *this;
        }

        // -----------
        // operator /=
        // -----------

        /**
         * @param rhs   an Integer object
         * @return  an Integer object whose value is the division of the original caller and rhs
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (Integer rhs) {
            if (*this == 0){
                return *this;
            }
            if (rhs == 0){
                throw std::invalid_argument("cannot divide by zero");
            }

            bool this_sign = is_negative;
            bool rhs_sign  = rhs.is_negative;

            Integer this_copy = *this;
            this_copy.abs();
            rhs.abs();

            *this = 0;

            while (this_copy > 0){
                this_copy -= rhs;
                ++*this;
            }

            if (this_sign)
                *this = -*this;

            if (rhs_sign)
                *this = -*this;

            return *this;
        }

        // -----------
        // operator %=
        // -----------

        /**
         * @param rhs   an Integer object
         * @return  an Integer object whose value is the remainder of division of the original caller and rhs
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (Integer rhs) {
            if (*this == 0){
                assert(is_negative == false);
                return *this;
            }
            if (rhs <= 0){
                throw std::invalid_argument("cannot mod by zero");
            }

            bool this_sign = is_negative;

            this->abs();
            Integer this_copy = *this;

            *this = 0;

            while (this_copy > 0 && this_copy >= rhs){
                this_copy -= rhs;
            }

            *this = this_copy;

            if (this_sign && *this != 0)
                *this = -*this;

            return *this;
        }

        // ------------
        // operator <<=
        // ------------

        /**
         * @param n   an int
         * @return  an Integer object whose value is the original value of the caller * 10^n
         */
        Integer& operator <<= (int n) {
            Integer this_copy = *this;
            grow(*this, n);
            shift_left_digits(this_copy.begin(), this_copy.end(), n, this->begin());
            return *this;
        }

        // ------------
        // operator >>=
        // ------------

        /**
         * @param n   an int
         * @return  an Integer object whose value is the original value of the caller / 10^n
         */
        Integer& operator >>= (int n) {
            Integer this_copy = *this;
            for (int i = 0; i < n; ++i)
                _x.pop_back();
            shift_right_digits(this_copy.begin(), this_copy.end(), n, this->begin());
            return *this;
        }

        // ---
        // abs
        // ---

        /**
         * absolute value
         * @return an Integer object that is the absolute value of the original caller's value
         */
        Integer& abs () {
            is_negative = false;
            return *this;
        }

        // ---
        // pow
        // ---

        /**
         * power
         * @param e   an int
         * @return  an Integer object whose value is the original value of the caller ^ e
         * @throws invalid_argument if ((this == 0) && (e == 0)) or (e < 0)
         */
        Integer& pow (int e) {
            if ((this == 0) && (e == 0)){
                throw std::invalid_argument("cannot have zero to the 0th power");
            }
            if (e < 0){
                throw std::invalid_argument("cannot have a negative exponent");
            }
            Integer this_copy = *this;
            while (e-- > 1){
                *this *= this_copy;
            }
            return *this;
        }

        // ---------
        // Iterators
        // ---------

        /**
         * begin
         * @return an Iterator to the beginning of this Integer's container
         */
        typename C::iterator begin () {
            return _x.begin();
        }

        /**
         * end
         * @return an Iterator to the end of this Integer's container
         */
        typename C::iterator end () {
            return _x.end();
        }

        /**
         * begin
         * @return an Iterator to the beginning of this Integer's container
         */
        typename C::const_iterator begin () const {
            return _x.begin();
        }

        /**
         * end
         * @return an Iterator to the end of this Integer's container
         */
        typename C::const_iterator end () const {
            return _x.end();
        }
};
#endif // Integer_h