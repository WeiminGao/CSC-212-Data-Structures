// Provided by:   ____________Weimin Gao__________
// Email Address: _________g1w2m1@gamil.com________
// FILE: Source.cpp

#include "newnode.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
using namespace std;

namespace main_savitch_5
{
	size_t list_length(const node* head_ptr) //O(n)
		// Library facilities used: cstdlib
	{
		const node *cursor;
		size_t answer;

		answer = 0;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			++answer;

		return answer;
	}

	void list_head_insert(node*& head_ptr, const node::value_type& entry) //O(1)
	{
		head_ptr = new node(entry, head_ptr);
	}

	void list_insert(node* previous_ptr, const node::value_type& entry) //O(3)
	{
		node *insert_ptr;

		insert_ptr = new node(entry, previous_ptr->link());
		previous_ptr->set_link(insert_ptr);
	}

	node* list_search(node* head_ptr, const node::value_type& target) //O(n)
		// Library facilities used: cstdlib
	{
		node *cursor;

		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			if (target == cursor->data())
				return cursor;
		return NULL;
	}

	const node* list_search(const node* head_ptr, const node::value_type& target) //O(n)
		// Library facilities used: cstdlib
	{
		const node *cursor;

		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			if (target == cursor->data())
				return cursor;
		return NULL;
	}

	node* list_locate(node* head_ptr, size_t position) //O(n)
		// Library facilities used: cassert, cstdlib
	{
		node *cursor;
		size_t i;

		assert(0 < position);
		cursor = head_ptr;
		for (i = 1; (i < position) && (cursor != NULL); i++)
			cursor = cursor->link();
		return cursor;
	}

	const node* list_locate(const node* head_ptr, size_t position) //O(n)
		// Library facilities used: cassert, cstdlib
	{
		const node *cursor;
		size_t i;

		assert(0 < position);
		cursor = head_ptr;
		for (i = 1; (i < position) && (cursor != NULL); i++)
			cursor = cursor->link();
		return cursor;
	}

	void list_head_remove(node*& head_ptr) // O(4)
	{
		node *remove_ptr;

		remove_ptr = head_ptr;
		head_ptr = head_ptr->link();
		delete remove_ptr;
	}

	void list_remove(node* previous_ptr) // O(4)
	{
		node *remove_ptr;

		remove_ptr = previous_ptr->link();
		previous_ptr->set_link(remove_ptr->link());
		delete remove_ptr;
	}

	void list_clear(node*& head_ptr) // O(n)
		// Library facilities used: cstdlib
	{
		while (head_ptr != NULL)
			list_head_remove(head_ptr);
	}

	void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr) //O(n)
		// Library facilities used: cstdlib
	{
		head_ptr = NULL;
		tail_ptr = NULL;

		// Handle the case of the empty list.
		if (source_ptr == NULL)
			return;

		// Make the head node for the newly created list, and put data in it.
		list_head_insert(head_ptr, source_ptr->data());
		tail_ptr = head_ptr;

		// Copy the rest of the nodes one at a time, adding at the tail of new list.
		source_ptr = source_ptr->link();
		while (source_ptr != NULL)
		{
			list_insert(tail_ptr, source_ptr->data());
			tail_ptr = tail_ptr->link();
			source_ptr = source_ptr->link();
		}
	}

	size_t list_occurrences(const node* head_ptr, const node::value_type& target) // O(n)
	{ //same as list_reasech, but return the occurrences of target, such as "n". 
		int n = 0;
		const node *cursor;

		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			if (target == cursor->data())
				n++;
		return n;
	}

	void list_tail_attach(node*& head_ptr, const node::value_type& entry) // O(7)
	{
		int length;
		node *last_ptr; //try find last node.
		last_ptr = head_ptr;
		length = list_length(head_ptr); //size_t list_length 
		if (length <= 0) list_head_insert(head_ptr, entry); //void list_head_insert (bucause empty)
		else 
		{
			last_ptr = list_locate(head_ptr, length); //find last node.
			list_insert(last_ptr, entry);
		} //const node* list_locate and void list_insert (find last point and insert)
		
	}

	void list_tail_remove(node*& head_ptr)// O(8)
	{
		int length;
		node *last_ptr; // same as tail_attach.
		last_ptr = head_ptr;
		length = list_length(head_ptr); //size_t list_length 
		assert(length > 0); // head_ptr is the head pointer of a linked list, with at least one node.
		if (length == 1) list_head_remove(head_ptr); //only one node.
		else 
		{
			last_ptr = list_locate(head_ptr, length-1); //const node* list_locate 
			list_remove(last_ptr);//void list_head_remove
		}// more than one node.
	}

	node* list_copy_front(const node* source_ptr, std::size_t n)// O(n) 
	{
		int length;
		length = list_length(source_ptr); //find size of source.
		assert(length >= n); //Precondition.
        //Below as list_copy but a little bit difference.
		//First time I tried to use list_copy toolkit, however it's not work because we want to stop at "n" . 
		node *head_ptr = NULL;
		node *tail_ptr = NULL;

		if (source_ptr == NULL)
			return tail_ptr;

		list_head_insert(head_ptr, source_ptr->data());
		tail_ptr = head_ptr;

        while (n != 0)
		{
			list_insert(tail_ptr, source_ptr->data());
			tail_ptr = tail_ptr->link();
			source_ptr = source_ptr->link();
			n--;
		} 
		//same as list_copy, but stop at "n", rather than at last node of source. (copy the first n nodes from the source_ptr)
		return head_ptr->link(); //return head node point to, if not code will print first data of node twice.
	}

}

// I have trouble to find Big-O notation in code, but I just try it.
// I just follow that each line is "1", and each for or while loop is "n". 
// Then add them to get Big-O notation.