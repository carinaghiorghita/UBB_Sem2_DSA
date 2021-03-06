#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <vector>
#include <exception>

SortedMultiMap::SortedMultiMap(Relation r) {
	this->R = r;
	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
}

void SortedMultiMap::add(TKey c, TValue v) {
	node* n = this->head;
	node* newNode = new node;
	newNode->info = make_pair(c, v);
	if (this->isEmpty())
	{
		newNode->prev = newNode->next = NULL;
		this->head = this->tail = newNode;
		this->length++;
		return;
	}
	if (this->R(c, n->info.first))
	{
		this->head->prev = newNode;
		newNode->next = this->head;
		newNode->prev = NULL;
		this->head = newNode;
		this->length++;
		return;
	}
	while (n->next && !this->R(c, n->next->info.first))
	{
		if (n->info.first == c && n->info.second == v) return;
		n = n->next;
	}
	if (n->next == NULL)
	{
		n->next = newNode;
		newNode->prev = n;
		newNode->next = NULL;
		this->tail = newNode;
	}
	else
	{
		n->next->prev = newNode;
		newNode->next = n->next;
		n->next = newNode;
		newNode->prev = n;
	}
	this->length++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> v = vector<TValue>();
	node *n = this->head;
	while (n)
	{
		if (n->info.first == c) v.push_back(n->info.second);
		n = n->next;
	}
	return v;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	if (this->isEmpty())return false;
	node* n = this->head;
	if (n->info.first == c && n->info.second == v)
	{
		if (this->size() == 1)
		{
			this->head = this->tail = NULL;
			delete n;
			this->length = 0;
			return true;
		}
		else
		{
			this->head = n->next;
			this->head->prev = NULL;
			delete n;
			this->length--;
			return true;
		}
	}
	while (n!=this->tail)
	{
		if (n->info.first == c && n->info.second == v)
		{
			n->prev->next = n->next;
			n->next->prev = n->prev;
			delete n;
			this->length--;
			return true;
		}
		n = n->next;
	}
	if (n->info.first == c && n->info.second == v)
	{
		this->tail = n->prev;
		this->tail->next = NULL;
		delete n;
		this->length--;
		return true;
	}
    return false;
}


int SortedMultiMap::size() const {
	return this->length;
}

bool SortedMultiMap::isEmpty() const {
	if (this->head == NULL and this->tail == NULL) return true;
	return false;
}

TValue SortedMultiMap::mostFrequent() const
{
	if (isEmpty())return NULL_TVALUE;
	int maxFrequency = 0,i,found, mostFreqVal=NULL_TVALUE;
	//first element of pair is the TValue, the second one is its frequency in the multimap
	vector< std::pair<TValue,int> > vect;
	node* n=this->head;
	while (n)
	{
		found = 0;
		for(i=0;i<vect.size()&&!found;++i)
			if (n->info.second == vect[i].first)
			{
				vect[i].second++;
				if (vect[i].second > maxFrequency)
				{
					maxFrequency = vect[i].second;
					mostFreqVal = vect[i].first;
				}
				found = 1;
			}
		if (!found)vect.push_back(make_pair(n->info.second, 1));
		if (maxFrequency == 0)
		{
			maxFrequency = 1;
			mostFreqVal = n->info.second;
		}
		n = n->next;
	}
	return mostFreqVal;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	while (this->head)
	{
		node *aux = this->head;
		this->head = this->head->next;
		free(aux);
	}
}
