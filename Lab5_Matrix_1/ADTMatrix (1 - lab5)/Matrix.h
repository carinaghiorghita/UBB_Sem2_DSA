#pragma once
#include <exception> 
#include <cmath>
//DO NOT CHANGE THIS PART
typedef int TElem;
class MatrixIterator;

#define NULL_TELEM 0
typedef struct node {
	TElem element;
	int line;
	int column;
	node* next;
};

typedef struct hashT {
	node** elements;
	int size;
};

class Matrix {

private:
	friend class MatrixIterator;
	
	int lines;
	int columns;
	hashT ht;
	int m;

	//Complexity:Theta(1)
	int hashFunction(TElem e) const;
	//Complexity:Theta(new capacity)=Theta(m)
	void resize();

public:
	//constructor
	//Complexity: BC=WC=AC=Theta(m)
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	//Complexity: BC=WC=AC=Theta(1)
	int nrLines() const;

	//returns the number of columns
	//Complexity: BC=WC=AC=Theta(1)
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	//Complexity: BC=O(1) when the element is the first one on the first position
	//			  WC=AC=O(n) when all the nodes are in a single linked-list in the hashtable and the node we need is the last one
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	//Complexity: BC=O(1) when the element is the first one on the first position
	//			  WC=AC=O(m+n) when all the nodes are in the last linked-list in the hashtable and the node we need is the last one
	TElem modify(int i, int j, TElem e);

	//creates an iterator over all the elements of the Matrix on a given line (no matter if they are NULL_TELEM or not)
	//throws exception if line is not a valid line
	//Complexity: BC=WC=AC=Theta(1)
	MatrixIterator iterator(int line) const;

};
