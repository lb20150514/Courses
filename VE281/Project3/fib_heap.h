#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include <cmath>
#include "priority_queue.h"

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a 
//           Fibonacci heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class fib_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  fib_heap(COMP comp = COMP());

  // EFFECTS: Deconstruct the heap with no memory leak.
  // MODIFIES: this
  // RUNTIME: O(n)
  ~fib_heap();
  
  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(1)
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: Amortized O(log(n))
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(1)
  virtual const TYPE &get_min() const;

  // EFFECTS: Get the number of elements in the heap.
  // RUNTIME: O(1)
  virtual size_type size() const;

  // EFFECTS: Return true if the heap is empty.
  // RUNTIME: O(1)
  virtual bool empty() const;
  
private:
  // Note: compare is a functor object
  COMP compare;

private:
	struct Node() {
		TYPE val;
		unsigned degree;
		std::list<Node*> child;

		Node(TYPE val): val(val), degree(0) {}
	}
	unsigned num = 0;
	Node* min = NULL;
	std::list<Node*> root;
};

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> ::fib_heap(COMP comp) {
	compare = comp;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> ::enqueue(const TYPE &val) {
	Node* ele = new Node(val);
	if (!min) {
		this->root.push_back(ele);
		this->min = ele;
	}
	else {
		// insert!
		if (val < this->min->val) this->min = ele;
	}
	this->num++;
}

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP> ::dequeue_min() {
	// Fill in the body.
}

template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP> ::get_min() const {
	return this->min->val;
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP> ::empty() const {
	return this->size() == 0;
}

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP> ::size() const {
	return this->num;
}

#endif //FIB_HEAP_H
