#include "commonFunctions.h"
#include <algorithm>
#include <cmath>


bool includes(std::vector<Tile>& set, Tile& object) {
	//initialize
	bool existence = false;
	
	//checks
	if (std::find(set.begin(), set.end(), object) != set.end()) {
		existence = true;
	}
	return existence;
}

//Other way to check if tile is includes
bool includesTile( std::vector<Tile*> set, Tile* object ) {
	if (set[0] == nullptr && set.size() == 1) {
		return false;
	}
	for (int i = 0; i < set.size() ; i++) {
		if (set[i]->xRow == object->xRow && set[i]->yRow == object->yRow) {
			return true;
		}
	}
	return false;
}




//distanse function
float heuristic(Tile* grid1, Tile* grid2) {
	// this works well with hexagon-grid
	float dx = float(grid2->xRow) - float(grid1->xRow);
	float dy = float(grid2->yRow) - float(grid1->yRow);
	float Epsilon = 0.0001;
	if(fabs( (dx / abs(dx)) - (dy / abs(dy)) )<=Epsilon ) {
		return abs(dx + dy);
	}else {
		return std::max(abs(dx), abs(dy));
	}
}




/*
//min_heap
class Min_heap {
public:
	std::vector<Tile*> heap;

	Min_heap() {
		heap.push_back(nullptr); // First element is unused to simplify index math
	}

	// Insert a new node into the heap
	void insert(Tile* tile) {
		heap.push_back(tile);
		swim(heap.size() - 1);
	}

	// Remove and return the node with the minimum f value
	Tile* delMin() {
		int N = heap.size() - 1;
		exch(1, N);
		Tile* minTile = heap.back();
		heap.pop_back();
		sink(1);
		return minTile;
	}
	// Change the F-value and order the heap
	void changeFValue(int k, float newFValue) {
		int N = heap.size() - 1;
		heap[k]->f = newFValue;
		// k even
		if (k % 2 == 0) {
			// if the new f-value is less than its parent then swim up
			if (heap[floor((k-1)/2)]->f > heap[k]->f ) {
				swim(k);
			} else if ( heap[floor((k - 1) / 2)]->f < heap[k]->f ) {
				// change with the smallest one 
				sink( k );
			}
		}
	}

private:
	

	// Exchange two nodes in the heap
	void exch(int i, int j) {
		std::swap(heap[i], heap[j]);
	}

	// The Tile swims up the array
	void swim( int k ) {
		while (k > 0  ) {
			if (k % 2 == 0) { // If index is even
				if ( heap[floor( (k-1)/2 )] -> f > heap[k]->f ) {
					exch( k, floor( (k - 1) / 2) );
					k = floor( (k - 1) / 2);
				} else {
					break;
				}
			} else { // If index is odd
				if (heap[floor( k / 2 )]->f > heap[k]->f) {
					exch(k, floor( k / 2));
					k = floor( k / 2 );
				} else {
					break;
				}
			}
			
		}
	}

	// Restore the heap order by sinking down
	void sink(int k) {
		int N = heap.size() - 1;
		// Decide Which Child has the smallest value
		while ( k <= N ) {
			// two childen
			if (2 * k + 2 <= N) { 
				// first child is smallest
				if (heap[2 * k + 2] -> f > heap[2 * k + 1]->f  ) { 
					if (heap[2 * k + 1 ]->f < heap[k]->f ) {
						exch(k, 2 * k + 1);
						k = 2 * k + 1;
					} else {
						break;
					}
				// second child is the smallest
				} else {
					if (heap[2 * k + 2]->f < heap[k]->f) {
						exch(k, 2 * k + 2);
						k = 2 * k + 2;
					} else {
						break;
					}
				}

			} else if (2*k+1 == N ) { // one child
				if (heap[2 * k + 1]->f < heap[k]->f) {
					exch(k, 2 * k + 1);
					k = 2 * k + 1;
				} else {
					break;
				}
			// no children 
			} else {
				break;
			}
		}
	}
};
*/
