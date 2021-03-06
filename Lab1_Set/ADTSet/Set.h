#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -11111
typedef int TElem;
class SetIterator;

class Set {
	//DO NOT CHANGE THIS PART
	friend class SetIterator;

    private:
        TElem* setElements;
        int firstElement,nrOfElements;
        //list of elems, start element, nr of elems

    public:
        //implicit constructor
        Set();


        bool add(TElem e);
        /*
        Adds an element to the set.
        Returns: 
            - true if the element is added
            - false if the element already exists and cannot be added
        Complexity: O(n)
        */
        
        bool remove(TElem e);
        /*
        Removes an element from the set.
        Returns:
            - true if the element is removed
            - false if the element doesn't exist and cannot be removed
        Complexity: O(n)
        */
        
        bool search(TElem elem) const;
        /*
        Checks if an element exists in the set.
        Returns:
            - true if the element exists
            - false if the element doesn't exist
        Complexity: O(1)
        */

        int size() const;
        /*
        Finds the number of existing elements in the set.
        Returns the size of the set.
        Complexity: O(1)
        */
        
        bool isEmpty() const;
        /*
        Checks whether the set is empty.
        Returns:
            - true if the set is empty (there are no elements)
            - false if the set is not empty
        Complexity: O(1)
        */
        
        SetIterator iterator() const;
        /*
        Returns an iterator to the set.
        */

        //returns the difference between the maximum and the minimum element (assume integer values)
        //if the Set is empty the range is -1
        //Complexity: O(1)
        int getRange() const;

        // destructor
        ~Set();

};





