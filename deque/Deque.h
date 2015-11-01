// --------------------------
// projects/c++/deque/Deque.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=
#include <cmath>
#include <iostream>
#define DEFAULT_ARRAY_SIZE 10

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;
using namespace std;
// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);
    }
    return b;
}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;
        }
    }
    catch (...) {
        destroy(a, p, x);
        throw;
    }
    return x;
}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;
        }}
    catch (...) {
        destroy(a, p, b);
        throw;
    }
    return e;
}

// -------
// my_deque
// -------

template < typename T, typename A = std::allocator<T> >
class my_deque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                        allocator_type;
        typedef typename allocator_type::value_type      value_type;

        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;

        typedef typename A::template rebind<pointer>::other      B;

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * @param lhs the left hand side
         * @param rhs the right hand side
         * @return true if they are equal, false otherwise.
         */
        friend bool operator == (const my_deque& lhs, const my_deque& rhs) {
            if (lhs.size() != rhs.size())
                return false;
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        // ----------
        // operator <
        // ----------

        /**
         * @param lhs the left hand side
         * @param rhs the right hand side
         * @return true if lhs is less than rhs, false otherwise.
         */
        friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
            return false;    
        }

    private:
        // ----
        // data
        // ----
        B        c_allocator;   
        pointer* _container;

        pointer * container; //backing container that holds our allocators. 
        allocator_type* data_begin; //begining of data.
        allocator_type* data_end; //end of data.

        allocator_type allocator; // the allocator for our container

        int container_size; // the number of pointers in main array

        int forward_capacity; 
        int backward_capacity;

        int total_capacity; // total amount possible
        int data_size; // amount of data used by user

        int main_front; // front index in main array
        int sub_front; // front index in sub arrays
        
        bool is_push_front;

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            assert(total_capacity == (size() + backward_capacity + forward_capacity));
            return true;
        }

        // ---------
        // push_back
        // ---------

        void increment(int& main, int& sub){
            assert(main < container_size);
            assert(main >= 0);
            assert(sub  >= 0);
            assert(sub  < DEFAULT_ARRAY_SIZE);
            ++sub;
            if (sub >= DEFAULT_ARRAY_SIZE){
                sub -= DEFAULT_ARRAY_SIZE;
                ++main;
            }
            assert(main < container_size);
            assert(main >= 0);
            assert(sub  >= 0);
            assert(sub  < DEFAULT_ARRAY_SIZE);
        }

        // ----------
        // push_front
        // ----------

        void decrement(int& main, int& sub){
            assert(main < container_size);
            assert(main >= 0);
            assert(sub  >= 0);
            assert(sub  < DEFAULT_ARRAY_SIZE);
            --sub;
            if (sub < 0){
                sub += DEFAULT_ARRAY_SIZE;
                --main;
            }
            assert(main < container_size);
            assert(main >= 0);
            assert(sub  >= 0);
            assert(sub  < DEFAULT_ARRAY_SIZE);
        }

        /**
         * makes 
         */
        my_deque (const my_deque& that, size_type c) {
            allocator = that.allocator;
            data_size = that.data_size;

            container_size = (int)ceil((c) / (double)DEFAULT_ARRAY_SIZE); 
            _container = c_allocator.allocate(sizeof(pointer) * container_size);

            sub_front = (DEFAULT_ARRAY_SIZE / 2) - 1;
            main_front = (container_size / 2) - 1;
            total_capacity = container_size * DEFAULT_ARRAY_SIZE;
            forward_capacity = ((container_size / 2 - 1) * DEFAULT_ARRAY_SIZE) + (DEFAULT_ARRAY_SIZE / 2 - 1);
            backward_capacity = total_capacity - forward_capacity - size();

            for (int i = 0; i < container_size; ++i){
                _container[i] = allocator.allocate(sizeof(value_type) * DEFAULT_ARRAY_SIZE);
            }

            uninitialized_copy(allocator, that.begin(), that.end(), begin());
            assert(valid());
        }

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef          std::bidirectional_iterator_tag iterator_category;
                typedef typename my_deque::value_type            value_type;
                typedef typename my_deque::difference_type       difference_type;
                typedef typename my_deque::pointer               pointer;
                typedef typename my_deque::reference             reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * @param lhs the left hand side
                 * @param rhs the right hand side
                 * @return true if their index values are the same, false otherwise.
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    return (lhs.index == rhs.index);
                    
                }

                /**
                * @param lhs the left hand side
                * @param rhs the right hand side
                * @return true if their index values are different, false otherwise.
                */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);
                }

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs the left hand side
                 * @param rhs the right hand side
                 * @return returns an iterator with the added indexs of lhs and rhs.
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;
                }

                // ----------
                // operator -
                // ----------

                /**
                 * @param lhs the left hand side
                 * @param rhs the right hand side
                 * @return returns an iterator with the added indexs of lhs and rhs.
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;
                }

            private:
                // ----
                // data
                // ----

                // <your data>
                unsigned int index; 
                my_deque& deque;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    assert(index >= 0);
                    return true;
                }

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * @param d the given my_deque 
                 * @param i starting index
                 * @return returns an iterator starting at i.
                 */
                iterator (my_deque& d, const int& i) : deque(d) {
                    index = i;
                    assert(valid());;
                }

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * @return returns a reference value pointed to by the iterator.
                 * looks up the value from the iterators index.
                 */
                reference operator * () const {
                    return deque[index];
                }

                // -----------
                // operator ->
                // -----------

                /**
                 * @return returns a pointer to the value pointed to by the iterator.
                 */
                pointer operator -> () const {
                    return &**this;
                }

                // -----------
                // operator ++
                // -----------

                /**
                 * @return returns the given iterator.
                 * increments the iterators index value.
                 */
                iterator& operator ++ () {
                    ++index;
                    assert(valid());
                    return *this;
                }

                /**
                 * @return returns the given iterator.
                 * increments the iterators index value.
                 * returns a copy of the original iterator.
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;
                }

                // -----------
                // operator --
                // -----------

                /**
                 * @return returns the given iterator.
                 * decrements the iterators index value.
                 */
                iterator& operator -- () {
                    --index;
                    assert(valid());
                    return *this;
                }

                /**
                 * @return returns an iterator.
                 * decrements the iterators index value.
                 * returns a copy of the original iterator.
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;
                }

                // -----------
                // operator +=
                // -----------

                /**
                 * @param d amount to increase by.
                 * @return returns an iterator reference.
                 * increases the iterators index value by d.
                 */
                iterator& operator += (difference_type d) {
                    index += d;
                    assert(valid());
                    return *this;
                }

                // -----------
                // operator -=
                // -----------

                /**
                 * @param d amount to decrease by.
                 * @return returns an iterator reference.
                 * decreases the iterators index value by d.
                 */
                iterator& operator -= (difference_type d) {
                    index -= d;
                    assert(valid());
                    return *this;
                }
            };

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef          std::bidirectional_iterator_tag iterator_category;
                typedef typename my_deque::value_type            value_type;
                typedef typename my_deque::difference_type       difference_type;
                typedef typename my_deque::const_pointer         pointer;
                typedef typename my_deque::const_reference       reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * @param lhs the left hand side
                 * @param rhs the right hand side
                 * @return true if their index values are the same, false otherwise.
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    return (lhs.index == rhs.index);
                }

                /**
                * @param lhs the left hand side
                * @param rhs the right hand side
                * @return true if their index values are different, false otherwise.
                */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);
                }

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs the left hand side
                 * @param rhs the right hand side
                 * @return returns an iterator with the added indexs of lhs and rhs.
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;
                }

                // ----------
                // operator -
                // ----------

                /**
                 * @param lhs the left hand side
                 * @param rhs the right hand side
                 * @return returns an iterator with the added indexs of lhs and rhs.
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;
                }

            private:
                // ----
                // data
                // ----

                // <your data>
                unsigned int index;
                const my_deque& deque;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    assert(index <= deque.size());
                    return true;
                }

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * @param d the given my_deque 
                 * @param i starting index
                 * @return returns an iterator starting at i.
                 */
                const_iterator (const my_deque& d, const int& i) : deque(d) {
                    index = i;
                    assert(valid());
                }

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * @return returns a reference value pointed to by the iterator.
                 * looks up the value from the iterators index.
                 */
                reference operator * () const {
                    return deque[index];
                }

                // -----------
                // operator ->
                // -----------

                /**
                 * @return returns a pointer to the value pointed to by the iterator.
                 */
                pointer operator -> () const {
                    return &**this;
                }

                // -----------
                // operator ++
                // -----------

                /**
                 * @return returns the given iterator.
                 * increments the iterators index value.
                 */
                const_iterator& operator ++ () {
                    ++index;
                    assert(valid());
                    return *this;
                }

                 /**
                 * @return returns the given iterator.
                 * increments the iterators index value.
                 * returns a copy of the original iterator.
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;
                }

                // -----------
                // operator --
                // -----------

                
                /**
                 * @return returns the given iterator.
                 * decrements the iterators index value.
                 */
                const_iterator& operator -- () {
                    --index;
                    assert(valid());
                    return *this;
                }

                /**
                 * @return returns an iterator.
                 * decrements the iterators index value.
                 * returns a copy of the original iterator.
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;
                }

                // -----------
                // operator +=
                // -----------

               /**
                 * @param d amount to increase by.
                 * @return returns an iterator reference.
                 * increases the iterators index value by d.
                 */
                const_iterator& operator += (difference_type d) {
                    index += d;
                    assert(valid());
                    return *this;
                }

                // -----------
                // operator -=
                // -----------

                /**
                 * @param d amount to decrease by.
                 * @return returns an iterator reference.
                 * decreases the iterators index value by d.
                 */
                const_iterator& operator -= (difference_type d) {
                    index -= d;
                    assert(valid());
                    return *this;
                }
            };

    public:
        // ------------
        // constructors
        // ------------

        /**
         * @param a an allocator to use for the backing containers.
         * @return a new instance of my_deque.
        */
        explicit my_deque (const allocator_type& a = allocator_type()) {
            allocator = a;
            is_push_front = false;
            _container = c_allocator.allocate(sizeof(pointer) * DEFAULT_ARRAY_SIZE);
            data_begin = data_end = NULL;

            main_front = sub_front = (DEFAULT_ARRAY_SIZE / 2) - 1;
            container_size = DEFAULT_ARRAY_SIZE;

            //set size value
            data_size = 0;
            total_capacity = DEFAULT_ARRAY_SIZE * DEFAULT_ARRAY_SIZE;
            forward_capacity = ((container_size / 2 - 1) * DEFAULT_ARRAY_SIZE) + (DEFAULT_ARRAY_SIZE / 2 - 1);
            backward_capacity = total_capacity - forward_capacity;

            for (int i = 0; i < container_size; ++i){
                _container[i] = allocator.allocate(sizeof(value_type) * DEFAULT_ARRAY_SIZE);
            }

            assert(valid());
        }

        
        /**
         * @param a an allocator to use for the backing containers.
         * @param s initalize size of my_deque instance.
         * @param v a value to initalize the my_deque 
         * @return a new instance of my_deque.
        */
        explicit my_deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) {
            assert(s >= 0);

            allocator = a;
            data_size = s;
            is_push_front = false;
            sub_front = (DEFAULT_ARRAY_SIZE / 2) - 1;

            if (s > (int)ceil((DEFAULT_ARRAY_SIZE * DEFAULT_ARRAY_SIZE) / 2.0)){
                // the case where we resize
                container_size = (int)ceil((s * 2) / (double)DEFAULT_ARRAY_SIZE);
            }
            else{
                // default case
                container_size = DEFAULT_ARRAY_SIZE;
            }
            main_front = (container_size / 2) - 1;
            total_capacity = container_size * DEFAULT_ARRAY_SIZE;
            forward_capacity = ((container_size / 2 - 1) * DEFAULT_ARRAY_SIZE) + (DEFAULT_ARRAY_SIZE / 2 - 1);
            backward_capacity = total_capacity - forward_capacity;
            _container = c_allocator.allocate(sizeof(pointer) * container_size); // make main array a big enough size

            // initialization

            for (int i = 0; i < container_size; ++i){
                _container[i] = allocator.allocate(sizeof(v) * DEFAULT_ARRAY_SIZE);
            }

            int count = data_size;
            int main_index = main_front;
            int  sub_index = sub_front;
            while (count > 0){
                for (; sub_index < DEFAULT_ARRAY_SIZE && count-- > 0; ++sub_index){
                    allocator.construct(&_container[main_index][sub_index], v);
                    --backward_capacity;
                }
                if (count <= 0){
                    break;
                }
                sub_index = 0;
                ++main_index;
            }
        }

        /**
         * @param that a my_deque intance
         * @return a new instance of my_deque that is an exact copy of that.
        */
        my_deque (const my_deque& that) {
            allocator = that.allocator;
            container_size = that.container_size;
            main_front = that.main_front;
            sub_front = that.sub_front;
            data_size = that.data_size;
            total_capacity = that.total_capacity;
            forward_capacity = that.forward_capacity;
            backward_capacity = that.backward_capacity;
            _container = c_allocator.allocate(sizeof(pointer) * container_size);

            for (int i = 0; i < container_size; ++i){
                _container[i] = allocator.allocate(sizeof(value_type) * DEFAULT_ARRAY_SIZE);
                uninitialized_copy(that._container[i], that._container[i] + DEFAULT_ARRAY_SIZE, _container[i]);
            }
            assert(valid());
        }

        // ----------
        // destructor
        // ----------

        /**
        * deletes the instance of my_deque from memory. 
        */
        ~my_deque () {
            for (int i = 0; i < container_size; ++i){
                allocator.deallocate(_container[i], sizeof(pointer));
            }
            c_allocator.deallocate(_container, sizeof(pointer) * container_size);
            assert(valid());
        }

        // ----------
        // operator =
        // ----------

        /**
         * @param that an instance of my_deque
         * @return the instance of my_deque now assigined to the contents of that
        */
        my_deque& operator = (const my_deque& that) {
            for (int i = 0; i < container_size; ++i){
                allocator.deallocate(_container[i], sizeof(pointer));
            }
            c_allocator.deallocate(_container, sizeof(pointer) * container_size);

            c_allocator = that.c_allocator;
            allocator = that.allocator;
            container_size = that.container_size;
            main_front = that.main_front;
            sub_front = that.sub_front;
            data_size = that.data_size;
            total_capacity = that.total_capacity;
            forward_capacity = that.forward_capacity;
            backward_capacity = that.backward_capacity;
            _container = c_allocator.allocate(sizeof(pointer) * container_size);

            for (int i = 0; i < container_size; ++i){
                _container[i] = allocator.allocate(sizeof(value_type) * DEFAULT_ARRAY_SIZE);
                uninitialized_copy(that._container[i], that._container[i] + DEFAULT_ARRAY_SIZE, _container[i]);
            }
            assert(valid());
            return *this;
        }

        // -----------
        // operator []
        // -----------

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        reference operator [] (size_type index) {
            using namespace std;
            assert (index >= 0);
            int main_index = (index / DEFAULT_ARRAY_SIZE) + main_front;
            int  sub_index = (index % DEFAULT_ARRAY_SIZE) + sub_front;
            
            while (sub_index >= DEFAULT_ARRAY_SIZE){
                ++main_index;
                sub_index -= DEFAULT_ARRAY_SIZE;
            }
            
            assert (sub_index < 10);
            assert (sub_index >= 0);
            assert (main_index < container_size);
            assert (main_index >= 0);
            
            return _container[main_index][sub_index];
        }

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);
        }

        // --
        // at
        // --

        /**
         * @param index Takes a position of an element in the container.
         * @return the element at the specifed position.
         * Throws out_of_range exception if index is out of bounds.
         */
        reference at (size_type index) {
            if(index < 0 || index >= data_size){
                throw out_of_range("index out of bounds");
            }
            return operator [](index);
        }

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);
        }

        // ----
        // back
        // ----

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        reference back () {
            return (*this)[size() - 1];
        }

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();
        }

        // -----
        // begin
        // -----

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        iterator begin () {
            return iterator(*this, 0);
        }

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        const_iterator begin () const {
            return const_iterator(*this, 0);
        }

        // -----
        // clear
        // -----

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        void clear () {
            resize(0);
            assert(valid());
        }

        // -----
        // empty
        // -----

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        bool empty () const {
            return !size();
        }

        // ---
        // end
        // ---

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        iterator end () {
            return iterator(*this, size()); 
        }

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        const_iterator end () const {
            return const_iterator(*this, size());
        }

        // -----
        // erase
        // -----
         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        iterator erase (iterator itr) {
            
            if(itr == begin()){
                allocator.destroy(&*itr);
                --data_size;
                increment(main_front, sub_front);  //update our begining.
                ++forward_capacity; 
                return begin();
            }else if (itr == end() - 1){
                allocator.destroy(&*itr);
                --data_size;
                ++backward_capacity;
                return end() - 1;
            }else{
                copy (itr + 1, end(), itr); //move elements forward one place.
                allocator.destroy(&*(end() - 1));
                --data_size;
                ++backward_capacity;
                return itr; 
            }
        }

        

        // -----
        // front
        // -----

         /**
         * @param index the index value to returned.
         * @return the value found at index in the given my_deque
         */
        reference front () {
            return (*this)[0];
        }

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();
        }

        // ------
        // insert
        // ------

        /**
         * @param itr Inserts new element v before the specified position itr.
         * returns an iterator that points to the newly inserted element.
         */
        iterator insert (iterator itr, const_reference v) {
            
            if(itr == begin()){ // push to the front
                if (forward_capacity <= 0){
                    // resize
                    is_push_front = true;
                    resize(size() + 1, v);
                    is_push_front = false;
                    }
                else{
                    ++data_size;
                    decrement(main_front, sub_front);  //update our begining.
                    --forward_capacity;
                    allocator.construct(&*itr, v);
                }
            }
            else if (itr == end()){ // push to the back
                if (backward_capacity <= 0){
                    // resize
                    resize(size() + 1, v);
                }
                else{
                    ++data_size;
                    --backward_capacity;
                }
                allocator.construct(&*(end() - 1), v);

            }else{ // push somewhere else
                if (backward_capacity <= 0){
                    // resize
                    resize(size() + 1);
                }
                else{
                    ++data_size;
                    --backward_capacity;
                    allocator.construct(&*end(), *(end() - 1));
                }
                iterator e = end() - 1;
                while (itr != e){
                    *e = *(e -1);
                    --e;
                }
                *itr = v;
            }
            assert(valid());
            return itr;
        }

        // ---
        // pop
        // ---

        /**
         * Removes and destroys the last element from the container
         * reduces size by one. 
         */
        void pop_back () {
            erase(end() - 1);
            assert(valid());
        }

        
        /**
         * Removes and destroys the last element from the container
         * reduces size by one. 
         */
        void pop_front () {
            erase(begin());
            assert(valid());
        }

        // ----
        // push
        // ----

        
        /**
         * Removes and destroys the last element from the container
         * reduces size by one. 
         */
        void push_back (const_reference v) {
            insert(end(), v);
            assert(valid());
        }

        
        /**
         * Removes and destroys the last element from the container
         * reduces size by one. 
         */
        void push_front (const_reference v) {
            insert(begin(), v);
            assert(valid());
        }

        // ------
        // resize
        // ------

        void reserve (size_type c) {
            my_deque x(*this, c);
            swap(x);
            assert(valid());
        }

        
        /**
         * Removes and destroys the last element from the container
         * reduces size by one. 
         */
        void resize (size_type s, const_reference v = value_type()) {
            if (s == size()){
                return;
            }
            else if (s < size()){
                destroy(allocator, begin() + s, end());
                backward_capacity += (size() - s);
                data_size = s;
            }
            else if (s <= backward_capacity && forward_capacity > 0){
                if (is_push_front){
                    push_front(v);
                }
                else{
                    uninitialized_fill(allocator, end(), begin() + s, v);
                    backward_capacity -= (s - size());
                    data_size = s;
                }
            }
            else {
                reserve(std::max((size_type)(2 * total_capacity), s));
                resize(s, v);
            }
            assert(valid());
        }

        // ----
        // size
        // ----

        
        /**
         * Removes and destroys the last element from the container
         * reduces size by one. 
         */
        size_type size () const {
            return data_size;
        }

        // ----
        // swap
        // ----

        /**
         * @param exchanges the contents of the my_deque this 
         * with the contents of the my_deque that.
         */
        void swap (my_deque& that) {
            if(allocator == that.allocator){
                std::swap(_container, that._container);
                std::swap(data_size, that.data_size);
                std::swap(container_size, that.container_size);
                std::swap(main_front, that.main_front);
                std::swap(sub_front, that.sub_front);
                std::swap(total_capacity, that.total_capacity);
                std::swap(backward_capacity, that.backward_capacity); //not sure if we need this.
                std::swap(forward_capacity, that.forward_capacity);
            }else{
                my_deque x(*this);
                *this = that;
                that  = x;
            }


            assert(valid());
        }};

#endif // Deque_h
