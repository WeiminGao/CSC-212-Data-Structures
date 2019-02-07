// Provided by:   ____________Weimin Gao__________
// Email Address: _________g1w2m1@gamil.com________
// FILE: Source.cpp
//
// FILE: pqueue2.cxx
// IMPLEMENTS: PriorityQueue (See pqueue2.h for documentation.)
// NOTE: You will need -lm at the end of your compile line to pick up
// the math library!

// INVARIANT for the PriorityQueue Class:
//   1. The member variable many_items is the number of items in the
//      PriorityQueue.
//   2. The items themselves are stored in the member variable heap,
//      which is a partially filled array organized to follow the usual
//      heap storage rules from Chapter 11 of the class notes.
// NOTE: Private helper functions are implemented at the bottom of this
// file along with their precondition/postcondition contracts.
 
#include <cassert>    // Provides assert function
#include <iomanip>    // Provides setw
#include <iostream>   // Provides cin, cout
#include <cmath>      // Provides log2
#include "pqueue2.h"
using namespace std;

PriorityQueue::PriorityQueue( )
{
	many_items = 0;
}

void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
	assert(size() < CAPACITY);
	size_t i=size();
	Item temp_data;
	unsigned int temp_priority;
	heap[i].data = entry;
	heap[i].priority = priority;
	many_items++;
    while (i > 0) {
			if (heap[parent_index(i)].priority < heap[i].priority) {
				temp_data = heap[parent_index(i)].data;
				temp_priority =heap[parent_index(i)].priority;
				heap[parent_index(i)].data = heap[i].data;
				heap[parent_index(i)].priority = heap[i].priority;
				heap[i].data = temp_data;
				heap[i].priority = temp_priority;
			}
			i = parent_index(i);
	}
}

PriorityQueue::Item PriorityQueue::get_front()// Reference: book page 545, "Pseudocode for Removing an Entry".
{
	assert(size() > 0);
	Item get_item;
	Item temp_data;
	unsigned int temp_priority;
	size_t j = 0, i;
	get_item = heap[0].data;//copy the entry at root of the heap
	heap[0].data = heap[size()-1].data;
	heap[0].priority = heap[size()-1].priority;//copy the last entry in the deepest level to the root. (called the "out-of-entry" entry)
	while (heap[j].priority <= heap[big_child_index(j)].priority) {//while (the out-of-place entry is less than one of its children)
		    i = big_child_index(j);
		    temp_data = heap[j].data;
			temp_priority = heap[j].priority;
			heap[j].data = heap[i].data;
			heap[j].priority = heap[i].priority;
			heap[i].data = temp_data;
			heap[i].priority = temp_priority;//Swap the out-of-place entry with its highest child.
		    j = i;
			if (2 * j + 1 >= many_items) break;//stop when the out-of-place entry reaches a leaf.
	}
	many_items--;//take last node out of the tree
	return get_item;//return a the root of the heap.
}

bool PriorityQueue::is_leaf(size_t i) const
// Precondition: (i < many_items)
// Postcondition: If heap[i] has no children in the heap, then the function
// returns true. Otherwise the function returns false.
{
	assert(i < many_items);
	if ((2 * i + 1) > many_items) return true; //
	else return false;
}

size_t PriorityQueue::parent_index(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the index of the parent of heap[i].
{
	assert((i > 0) && (i < many_items));
	return (i - 1) / 2;
}

unsigned int PriorityQueue::parent_priority(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the priority of the parent of heap[i].
{
	assert((i > 0) && (i < many_items));
	return heap[(i - 1) / 2].priority;

}

size_t PriorityQueue::big_child_index(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value is the index of one of heap[i]'s children.
// This is the child with the larger priority.
{
	assert(!is_leaf(i));
	size_t l_chil = 2 * i + 1, r_chil = 2 * i + 2;
	if (heap[r_chil].priority > heap[l_chil].priority && r_chil < many_items) return r_chil; //Before I uesed (heap[l_chil].priority < heap[r_chil].priority && r_chil < many_items) that causes special problem.
	else return l_chil;
}

unsigned int PriorityQueue::big_child_priority(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value heap[big_child_index(i)].priority
{
	assert(!is_leaf(i));
	return heap[big_child_index(i)].priority;
}

void PriorityQueue::swap_with_parent(size_t i)
// Precondition: (i > 0) && (i < many_items)
// Postcondition: heap[i] has been swapped with heap[parent_index(i)]
{
	assert((i > 0) && (i < many_items));
	Item temp_data;
	unsigned int temp_priority;
	temp_data = heap[i].data;
	temp_priority = heap[i].priority;
	heap[i].data = heap[(i - 1) / 2].data;
	heap[i].priority = heap[(i - 1) / 2].priority;
	heap[(i - 1) / 2].data = temp_data;
	heap[(i - 1) / 2].priority = temp_priority;

}

void PriorityQueue::print_tree(const char message[ ], size_t i) const
// Postcondition: If the message is non-empty, then that has been written
// to cout. After the message, the portion of the heap with root at node
// node i has been written to the screen. Each node's data is indented
// 4*d, where d is the depth of the node.
// NOTE: The default argument for message is the empty string, and the
// default argument for i is zero. For example, to print the entire
// tree of a PriorityQueue p, with a message of "The tree:", you can call:
//     p.print_tree("The tree:");
// This call uses the default argument i=0, which prints the whole tree.
{
    const char NO_MESSAGE[ ] = "";
    size_t depth;

    if (message[0] != '\0')
        cout << message << endl;

    if (i >= many_items)
        cout << "NO NODES." << endl;
    else
    {
        depth = int(log(double(i+1))/log(2.0));
        cout << setw(depth*4) << "";
        cout << heap[i].data;
        cout << " (priority " << heap[i].priority << ")" << endl;
        if (2*i + 1 < many_items)
            print_tree(NO_MESSAGE, 2*i + 1);
        if (2*i + 2 < many_items)
            print_tree(NO_MESSAGE, 2*i + 2);
    }
}
