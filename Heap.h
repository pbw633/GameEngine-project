#pragma once
#include <vector>
#include "Tile.h"

class Min_heap {
public:
	int latestInsertedIndex = 0;
	
	std::vector<Tile*> heap;

	Min_heap() {
		heap.push_back(nullptr); // First element is unused to simplify index math
	}

	// adds a tile to the heap
	void insert(Tile* tile);

	//clear the heap and insert a nullptr at the first so it is possible to use insert
	void clear();

	// Remove and return the node with the minimum f value
	Tile* delMin();

	// Change the F-value and order the heap
	void changeFValue(int k, float newFValue);
	int changeFValueIndex(int k, float newFValue);

private:

	// Exchange two nodes in the heap
	void exch(int i, int j);

	// The Tile swims up the array
	void swim(int k);

	// Restore the heap order by sinking down
	void sink(int k);

	
};