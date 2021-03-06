#include <assert.h>
#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
    assert(smm.mostFrequent() == NULL_TVALUE);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.mostFrequent() == 3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    smm.add(2, 2);
    assert(smm.mostFrequent() == 2);
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    smm.remove(2, 2);
    assert(smm.isEmpty());
}

