#include "SetIterator.h"
#include "Set.h"


SetIterator::SetIterator(const Set& m) : set(m)
{
	this->elements = this->set.setElements;
	this->firstElem = 0;
}


void SetIterator::first() {
	this->firstElem = 0;
}


void SetIterator::next() {
	do
	{
		this->firstElem++;
	} while (valid() && !this->elements[this->firstElem]);
}


TElem SetIterator::getCurrent()
{
	return this->set.firstElement + this->firstElem;
}

bool SetIterator::valid() const {
	if (this->set.size() == 0)return 0;
	if(this->firstElem== this->set.nrOfElements)
		return 0;
	return 1;
}



