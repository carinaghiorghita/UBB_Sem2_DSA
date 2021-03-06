#include "Matrix.h"
#include <exception>
class MatrixIterator
{
	friend class Matrix;
private:
	const Matrix& matrix;
	int currentIndex;
	int line;
	MatrixIterator(const Matrix& m, int line);

public:
	// Complexity: WC=BC=AC=Theta(1)
	void first();

	// Complexity: WC=BC=AC=Theta(1)
	// Throws exception if the current element is not valid
	void next();

	//Complexity: BC=O(1) when the element is the first one on the first position
	//			  WC=AC=O(m+n) when the element is the last one on the last position of the hashtable
	// Throws exception if the current element is not valid
	TElem getCurrent() const;

	// Complexity: WC=BC=AC=Theta(1)
	bool valid() const;
};
