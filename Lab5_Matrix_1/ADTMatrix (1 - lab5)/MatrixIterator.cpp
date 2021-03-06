#include "MatrixIterator.h"
#include "Matrix.h"
#include <exception>
#include <iostream>
using namespace std;

MatrixIterator::MatrixIterator(const Matrix& m, int line) : matrix(m)
{
	this->currentIndex = 0;
	this->line = line;
}

void MatrixIterator::first() {
	this->currentIndex = 0;
}


void MatrixIterator::next() {
	exception myex;
	if (!this->valid()) throw myex;
	this->currentIndex++;
}


bool MatrixIterator::valid() const {
	if (this->currentIndex >=matrix.lines) return false;
	return true;
}


TElem MatrixIterator::getCurrent() const
{
	exception myex;
	if (!this->valid()) throw myex;
	return this->matrix.element(line,currentIndex);
}
