#include "Set.h"
#include "SetITerator.h"

Set::Set() {
	this->firstElement = NULL_TELEM;
	this->nrOfElements = 0;
	this->setElements = new TElem[1];
}


bool Set::add(TElem elem) {
	if (search(elem))return false;
	if (isEmpty())
	{
		this->firstElement = elem;
		this->nrOfElements = 1;
		this->setElements[0] = true;
	}
	if (elem < this->firstElement)
	{
		int move = this->firstElement - elem,index;
		int* array = new TElem[this->nrOfElements];
		for (index = 0; index < this->nrOfElements; ++index)array[index] = this->setElements[index];
		this->firstElement = elem;
		this->nrOfElements += move;
		delete[] this->setElements;
		this->setElements = new TElem[this->nrOfElements];
		this->setElements[0] = true;
		for (index = 1; index < move; ++index)this->setElements[index] = false;
		for (index = move; index < this->nrOfElements;++index) this->setElements[index] = array[index - move];
		delete[] array;
	}
	else if (elem < this->nrOfElements + this->firstElement - 1)this->setElements[elem - this->firstElement] = true;
	else
	{
		int oldSize = this->nrOfElements,index;
		int* array = new TElem[this->nrOfElements];
		for (index = 0; index < this->nrOfElements; ++index)array[index] = this->setElements[index];
		this->nrOfElements = elem - this->firstElement + 1; 
		delete[] this->setElements;
		this->setElements = new TElem[this->nrOfElements];
		for (index = 0; index < oldSize; ++index)this->setElements[index] = array[index];
		for (index = oldSize; index < this->nrOfElements-1;++index)this->setElements[index] = false;
		this->setElements[this->nrOfElements-1] = true;
		delete[] array;
	}
	return true;
}


bool Set::remove(TElem elem) {
	if (!search(elem))return false;
	if (elem == this->firstElement)
	{
		int index;
		int* array = new TElem[this->nrOfElements];
		for (index = 0; index < this->nrOfElements; ++index)array[index] = this->setElements[index];
		this->firstElement++;
		this->nrOfElements--;
		delete[] this->setElements;
		this->setElements = new TElem[this->nrOfElements];
		for (index = 0; index < this->nrOfElements; ++index)this->setElements[index] = array[index + 1];
		delete[] array;
	}
	else if (elem == this->nrOfElements - 1)
	{
		while (!this->setElements[this->nrOfElements - 1])
			this->nrOfElements--;
	}
	else this->setElements[elem - this->firstElement] = false;
	return true;
}

bool Set::search(TElem elem) const {
	if (elem < this->firstElement)return false;
	if (elem > this->firstElement + this->nrOfElements-1)return false;
	return this->setElements[elem-this->firstElement];
}


int Set::size() const {
	int nrElem = 0,index;
	for (index = 0; index < this->nrOfElements; ++index)
		if(this->setElements[index])nrElem++;
	return nrElem;
}


bool Set::isEmpty() const {
	return size()==0;
}


int Set::getRange() const
{
	if (isEmpty())return -1;
	return this->nrOfElements-1;
}

Set::~Set() {
	delete[] this->setElements;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


