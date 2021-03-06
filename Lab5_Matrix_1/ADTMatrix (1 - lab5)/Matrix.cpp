#include "Matrix.h"
#include "MatrixIterator.h"
#include <exception>
using namespace std;


int Matrix::hashFunction(TElem e) const
{
	return abs(e) % m;
}

void Matrix::resize()
{
	int prevCapacity = m;
	m *= 2;
	node** newHash = new node * [m];
	for (int i = 0; i <m; i++)
		newHash[i] = NULL;
	node* prevNode = NULL;
	for (int i = 0; i < prevCapacity; i++)
	{
		node* currentNode = ht.elements[i];
		while (currentNode != NULL)
		{
			prevNode = currentNode;
			int pos = hashFunction(currentNode->element);
			node* newNode = new node();
			newNode->element = currentNode->element;
			newNode->line = currentNode->line;
			newNode->column = currentNode->column;
			newNode->next = newHash[pos];
			newHash[pos] = newNode;
			currentNode = currentNode->next;
			delete prevNode;
		}
	}
	delete[] ht.elements;
	ht.elements = newHash;
}

Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->lines = nrLines;
	this->columns = nrCols;
	this->m = 10000;

	ht.size = 0;
	ht.elements = new node * [m];
	for (int i = 0; i < m; ++i)
		ht.elements[i] = NULL;
}


int Matrix::nrLines() const {
	return this->lines;
}


int Matrix::nrColumns() const {
	return this->columns;
}


TElem Matrix::element(int i, int j) const {
	exception myex;
	if (i >= this->lines || j >= this->columns || i < 0 || j < 0)throw myex;
	for (int pos = 0; pos < m; ++pos)
	{
		node* current = ht.elements[pos];

		while (current && (current->line < i || current->line == i && current->column <= j))
		{
			if (current->line == i && current->column == j) {
				return current->element; }
			current = current->next;
		}

	}
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	exception myex;
	if (i >= this->lines || j >= this->columns)throw myex;

	TElem prevElem=element(i,j);
	int pos = hashFunction(e),posprev=hashFunction(prevElem);

	if (pos == posprev)
	{
		node* current = ht.elements[pos];
		while (current && (current->line < i || current->line == i && current->column <= j))
		{
			if (current->line == i && current->column == j)
			{
				current->element = e;
				return prevElem;
			}
			current = current->next;
		}
	}
	else if (posprev != 0)
	{
		node* current = ht.elements[posprev];
		node* prev = NULL;
		while (current && (current->line < i || current->line == i && current->column <= j))
		{
			if (current->line == i && current->column == j)
			{
				if (prev)
				{
					prev->next = current->next;
				}
				else
				{
					ht.elements[pos] = current->next;
				}
			}
			current = current->next;
		}
		current = ht.elements[pos];
		prev = NULL;
		double x;
		x = static_cast<double>(ht.size) / static_cast<double>(m);
		while (x > 0.7 || m <= pos) resize();
		while (current && (current->line < i || current->line == i && current->column <= j))
		{
			prev = current; 
			current = current->next;
		}
		node* newNode = new node();
		newNode->line = i;
		newNode->column = j;
		newNode->element = e;
		if (prev)
		{
			prev->next = newNode;
			newNode->next = current;
		}
		else
		{
			ht.elements[pos] = newNode;
			ht.elements[pos]->next = NULL;
		}
		return prevElem;
	}
	else
	{
		node* current = ht.elements[pos];
		node* prev = NULL;
		while (current && (current->line < i || current->line == i && current->column <= j))
		{
			prev = current;
			current = current->next;
		}
		double x;
		x = static_cast<double>(ht.size) / static_cast<double>(m);
		if (x > 0.7) resize();
		node* newNode = new node();
		newNode->line = i;
		newNode->column = j;
		newNode->element = e;
		if (prev)
		{
			prev->next = newNode;
			if (current)newNode->next = current;
			else newNode->next = NULL;
		}
		else
		{
			ht.elements[pos] = newNode;
			ht.elements[pos]->next = NULL;
		}
		ht.size++;
		return prevElem;
	}
	
}

MatrixIterator Matrix::iterator(int line) const {
	
	exception myex;
	if (line >= this->lines || line < 0) throw myex;
	return MatrixIterator(*this,line);
}


