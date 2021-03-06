#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->current = this->map.head;
}

void SMMIterator::first(){
	this->current = this->map.head;
}

void SMMIterator::next(){
	if (!this->valid())return;
	this->current = this->current->next;
}

bool SMMIterator::valid() const{
	if (this->current) return true;
	return false;
}

TElem SMMIterator::getCurrent() const{
	if (this->valid())
	{
		int key = this->current->info.first;
		int value = this->current->info.second;
		return make_pair(key, value);
	}
	return NULL_TELEM;
}


