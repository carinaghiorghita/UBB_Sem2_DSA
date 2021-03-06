#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>

using namespace std;

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TELEM pair<TKey, TValue>(-11111, -11111);
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);
struct node { TElem info; node* next; node* prev; };


class SortedMultiMap {
	friend class SMMIterator;
    private:
        node *head,*tail;
        Relation R;
        int length;
    public:

    // constructor
    // Complexity: WC=BC=AC=Theta(1)
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    // Complexity: AC=WC=O(length of map)
    //             BC=O(1) when the multimap is empty/the element is added to the beginning of the map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    // Complexity: AC=BC=WC=Theta(length of map)
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    // Complexity: AC=WC=O(length of map)
    //             BC=O(1) when the element to be removed is the first one in the map
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    // Complexity: AC=BC=WC=Theta(1)
    int size() const;

    //verifies if the sorted multi map is empty
    // Complexity: AC=BC=WC=Theta(1)
    bool isEmpty() const;

    //returns the TValue that appears most frequently in the SortedMultiMap. If multiple TValues appear most frequently, returns any of them. 
    //if the SortedMultiMap is empty, the operation returns NULL_TVALUE
    //Complexity: AC=BC=WC=Theta((length of map)*(number of TValues))
    TValue mostFrequent() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    // Complexity: AC=BC=WC=Theta(1)
    SMMIterator iterator() const;

    // destructor
    // Complexity: AC=BC=WC=Theta(length of map)
    ~SortedMultiMap();
};
