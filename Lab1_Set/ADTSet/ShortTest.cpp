#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"

void testAll() { 
	Set s;
	assert(s.isEmpty() == true);
	assert(s.getRange() == -1);
	assert(s.size() == 0);
	assert(s.add(5)==true);
	assert(s.getRange() == 0);
	assert(s.add(1)==true);
	assert(s.getRange() == 4);
	assert(s.add(10)==true);
	assert(s.getRange() == 9);
	assert(s.add(7)==true);
	assert(s.getRange() == 9);
	assert(s.add(1)==false);
	assert(s.add(10)==false);
	assert(s.add(-3)==true);
	assert(s.getRange() == 13);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);

	assert(s.search(5) == true);
	assert(s.search(10) == true);
	assert(s.search(7) == true);
	assert(s.search(1) == false);
	assert(s.search(-3) == true);


	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	
	assert(sum == 19);
	
}

