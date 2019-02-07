// Provided by:   ____________Weimin Gao__________
// Email Address: _________g1w2m1@gamil.com________
// FILE: Source.cpp
#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include "sequence2.h"
#include <algorithm>


using namespace std;
namespace main_savitch_4
{
	//Constructor and Default constructor
	sequence::sequence(size_type init_cap) 
	{
		data = new value_type[init_cap];
		capacity = init_cap;
		used = 0;
		current_index = 0;
	}
	//Copy constructor
	//Copy all member(data,capacity,used,current_index) of the original sequence.
	sequence::sequence(const sequence& source) {
		data = new value_type[source.capacity];
		capacity = source.capacity;
		used = source.used;
		current_index = source.current_index;
		copy(source.data, source.data + used, data);
	}
	//Destructor
	sequence::~sequence( ) {
		delete [ ] data;
	}
	void sequence::resize(size_type new_capacity) 
	{
		value_type* new_array;
		if (new_capacity == capacity) return;
		if (new_capacity < used) new_capacity = used;

		new_array = new value_type[new_capacity];
		copy(data, data + used, new_array);
		delete [ ] data;
		data = new_array;
		capacity = new_capacity;
	}
	void sequence::start( ) 
	{
		current_index = 0;
	}
	void sequence::advance( ) 
	{
		assert(is_item());
		current_index++;
	}
	void sequence::insert(const value_type& entry) 
	{
		size_type i;
		//assert(size() < capacity);
		if (size() >= capacity) resize(capacity + 1);
		if (!is_item()) current_index = 0;
		for (i = used; i > current_index; i--)
			data[i] = data[i - 1];
		data[current_index] = entry;
		used++;
	}
	void sequence::attach(const value_type& entry) 
	{
		size_type i;
		//assert(size() < capacity);
		if (size() >= capacity) resize(capacity + 1);
		//add "current_index = used" to pass last sequence test of test 1. When sequence is empty, current_index should be 0, which equal to used.
		if (!is_item()) { current_index = used; data[current_index] = entry; }  
		else {
			for (i = used; i > current_index + 1; i--)
				data[i] = data[i - 1];
			data[current_index + 1] = entry;
			current_index++;
		} 
		used++;
	}
	void sequence::remove_current() 
	{
		size_type i;
		assert(is_item());
		for (i = current_index + 1; i < used; i++)
			data[i - 1] = data[i];
		used--;
	}
	//Copy all member(data, capacity, used, current_index) of the original sequence.
	void sequence::operator =(const sequence& source) 
	{
		value_type *new_data;
		if (this == &source) return;
		if (capacity != source.capacity)
		{
			new_data = new value_type[source.capacity];
			delete[] data;
			data = new_data;
			capacity = source.capacity;
		}
		current_index = source.current_index;
		used = source.used;
		copy(source.data, source.data + used, data);
	}
	sequence::size_type sequence::size() const 
	{
		return used;
	}
	bool sequence::is_item() const 
	{
		return(current_index < used);
	}
	sequence::value_type sequence::current() const 
	{
		assert(is_item());
		return data[current_index];
	}

}

