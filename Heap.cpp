#include "Heap.h"

void Min_heap::insert(Tile* tile) {
	if (heap[0] == nullptr) {
		heap[0] = tile;
	}  else {
		heap.push_back(tile);
		swim(heap.size() - 1);
	}
}

Tile* Min_heap::delMin() {
	if (heap.size() > 1) {
		int N = heap.size() - 1;
		exch(0, N);
		Tile* minTile = heap.back();
		heap.pop_back();
		sink(0);
		return minTile;
	}
	else if (heap.size() == 1) {
		Tile* minTile = heap.back();
		heap[0] = nullptr;
		return minTile;
	}
	return nullptr;
}

void Min_heap::changeFValue(int k, float newFValue) {
	int N = heap.size() - 1;
	heap[k]->f = newFValue;

	int parent = (k - 1) / 2;
	if (k > 0 && heap[parent]->f > heap[k]->f) {
		swim(k);
	}
	else {
		sink(k);
	}
}

int Min_heap::changeFValueIndex(int k, float newFValue) {
	return 0;
}

void Min_heap::exch(int i, int j) {
	std::swap(heap[i], heap[j]);
}

void Min_heap::swim(int k) {
	while (k > 0) {
		int parent = (k - 1) / 2;
		if (heap[parent]->f > heap[k]->f) {
			exch(k, parent);
			k = parent;
		}
		else {
			break;
		}
	}
	latestInsertedIndex = k;
}

void Min_heap::sink(int k) {
	int N = heap.size();
	while (2 * k + 1 < N) {  // så længe der findes et venstre barn
		int child = 2 * k + 1; // venstre barn
		if (child + 1 < N && heap[child + 1]->f < heap[child]->f) {
			child++; // vælg højre barn hvis det er mindre
		}
		if (heap[k]->f <= heap[child]->f) {
			break;
		}
		exch(k, child);
		k = child;
	}
	latestInsertedIndex = k;
}

void Min_heap::clear() {
	heap.clear();
	latestInsertedIndex = 0;
	heap.push_back(nullptr);
}