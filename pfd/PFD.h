// --------------------------
// projects/pfd/PFD.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef PFD_h
#define PFD_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <cassert>
#include <string>   // string
#include <utility>  // pair
#include <vector>

using namespace std;

//!  A task struct. 
/*!
  A data structure to represent a task and its dependencies.
*/
struct task{
	/**
	 * prints a "task" struct
	 * @param w the output stream
	 * @param rhs the task to be printed
	 * @return the output stream
	 */
	friend ostream& operator<<(ostream& w, const task& rhs){
		w << "T" << rhs.number << "(";
		for (unsigned i = 0; i < rhs.dependencies; ++i){
			w << rhs.dependencies_list[i].number;
			if (i + 1 < rhs.dependencies)
				w << " ";
		}
		w << ")";
		return w;
	}

	unsigned int number; /*!< the numerical value of the task */
	unsigned int dependencies; /*!< the number of other tasks this object depends on */
	vector<task> dependencies_list; /*!< a list of tasks this object depends on */
	
	/**
	 * constructor
	 * @param n the numerical value of the task
	 * @return a new task struct
	 */
	task(int n) : number(n), dependencies(0){}

	/**
	 * less than operator
	 * @param rhs another task
	 * @return a boolean
	 */
	bool operator<(const task& rhs) const{
		assert(*this != rhs);
		if (dependencies != rhs.dependencies){
			return (dependencies < rhs.dependencies);
		}
		return number < rhs.number;
	}

	/**
	 * star operator
	 * @return the numerical value of the task
	 */
	int operator*() const{
		return number;
	}

	/**
	 * comparison operator
	 * @param rhs another task struct
	 * @return a boolean
	 */
	bool operator==(const task& rhs) const{
		return number == rhs.number;
	}

	/**
	 * not equal operator
	 * @param rhs another task struct
	 * @return a boolean
	 */
	bool operator!=(const task& rhs) const{
		return !(*this == rhs);
	}

	/**
	 * greater than operator
	 * @param rhs another task struct
	 * @return a boolean
	 */
	bool operator>(const task& rhs) const{
		assert(*this != rhs);
		return (*this != rhs && !(*this < rhs));
	}

	/**
	 * plus equals operator
	 * @param rhs another task struct
	 * @return a reference to this task struct, after adding the other to the dependencies list
	 */
	task& operator+=(const task& rhs){
		assert(*this != rhs);
		dependencies_list.push_back(rhs);
		++dependencies;
		return *this;
	}

	/**
	 * minus equals operator
	 * @param rhs another task struct
	 * @return a reference to this task struct, after removing the other from the dependencies list
	 */
	task& operator-=(const task& rhs){
		int index = 0;
		for (const task& t : dependencies_list){
			if (t == rhs){
				--dependencies;
				dependencies_list.erase(dependencies_list.begin() + index);
				break;
			}
			++index;
		}
		return *this;
	}
};

// ------------
// pfd_string_to_vector
// ------------

/**
 * read ints from string
 * @param s a string
 * @return a vector of ints parsed from the string
 */
vector<int> pfd_string_to_vector (const string& s);

// ------------
// pfd_stream_to_vector
// ------------

/**
 * convert a stream to a vector
 * @param r an input stream
 * @return a vector of ints parsed from the input stream
 */
vector<int> pfd_stream_to_vector(istream& r);

// ------------
// pfd_next_task
// ------------

/**
 * evaluate which task should come next
 * @param task_list the list of task structs
 * @return the numerical value of the next task struct
 */
int pfd_next_task(vector<task>& task_list);

// -------------
// pfd_print
// -------------

/**
 * print the output list
 * @param w an ostream
 * @param v the output list
 */
void pfd_print (ostream& w, const vector<int>& v);

// -------------
// pfd_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void pfd_solve (istream& r, ostream& w);

// ------------
// pfd_eval
// ------------

/**
 * evaluate which tasks should be completed in which order
 * @param task_list the list of task structs
 * @return a vector of ints in order of output
 */
vector<int> pfd_eval(vector<task> task_list);

#endif // PFD_h