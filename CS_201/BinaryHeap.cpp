
#include "BinaryHeap.h"

BinaryHeap::BinaryHeap(int capacity) {
    this->capacity = capacity;

	// The element at index 0 is not used!
	// The root element will be placed at index 1
	heap = new int[capacity+1];
	size = 0;
}

BinaryHeap::~BinaryHeap() {
	delete [] heap;
}

int parent(int i) { return i / 2; };
int left(int i) { return 2 * i ; };
int right(int i) { return 2 * i + 1; };


void BinaryHeap::insert(int element) {
	if (size == capacity) {
		cout << "\nOverflow detected\n";
		return;
	}
	size++;
	int i = size ;
	heap[i] = element;

	while (i != 1 && heap[parent(i)] > heap[i]) {
		swap(i, parent(i));
		i = parent(i);
	}

}

void BinaryHeap::deleteMin() {

	if (size < 1) {
		return;
	}
	if (size == 1) {
		size--;
		return;
	}
	int root = heap[1];
	heap[1] = heap[size];
	size--;
	percolateDown(1);
	return;
}

int BinaryHeap::getMin() {
	if (size < 1) {
		return -1;
	}
	else 
		return heap[1];

}

void BinaryHeap::percolateDown(int hole) {
	int l = left(hole);
	int r = right(hole);
	int smallest = hole;

	if (l < size+1 && heap[l] < heap[hole])
		smallest = l;
	if (r < size+1 && heap[r] < heap[smallest])
		smallest = r;
	if (smallest != hole) {
		swap(hole, smallest);
		percolateDown(smallest);
	}
}



void BinaryHeap::swap(int i, int j) {
	int t = heap[i];
	heap[i] = heap[j];
	heap[j] = t;
}
