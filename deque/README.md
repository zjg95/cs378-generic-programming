# Deque
Design and implement the class my_deque<T, A> to conform to std::deque<T, A>.


A deque is an attractive compromise between a vector and a list.

#### vector is:
linear when adding elements to the beginning or the middle,
amortized constant when adding elements to the end,
linear when removing elements from the beginning or the middle,
constant when removing elements from the end,
constant when indexing elements


#### list is:
constant when adding elements,
constant when removing elements,
linear when indexing elements


#### deque is:
amortized constant when adding elements to the beginning or the end,
linear when adding elements to the middle,
constant when removing elements from the beginning or the end,
linear when removing elements from the middle,
constant when indexing elements


A deque is very similar to a vector except that the elements are stored in the center of a two-dimensional array instead of at the beginning a one-dimensional array.
