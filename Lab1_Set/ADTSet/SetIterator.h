#pragma once
#include "Set.h"

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	const Set& set;
	SetIterator(const Set& s);

	int* elements;
	int firstElem;

public:
	void first();
	/*
	Sets the iterator on the first element of the set.
	Complexity: O(1)
	*/

	void next();
	/*
	Sets the iterator on the next element in the set.
	Complexity: O(n)
	*/

	TElem getCurrent();
	/*
	Returns the current element of the set.
	Complexity: O(1)
	*/

	bool valid() const;
	/*
	Checks if the iterator is valid (we haven't iterated the whole set)
	Returns:
		- true if the iterator is valid 
		- false if the iterator is not valid 
	Complexity: O(1)
	*/
};


