#include "AlgorithmSortHeap.h"

AlgorithmSortHeap::AlgorithmSortHeap(int k) : SelectionAlgorithm(k) {
	this->kth = k;
}

int AlgorithmSortHeap::select() {
	int array_length = 0;
	cin >> array_length;
	BinaryHeap *heap = new BinaryHeap(kth);
	int temp;
	for (int i = 0; i < kth; i++) {
		cin >> temp;
		heap->insert(temp);
	}

	int counter = 0;

	while (counter < array_length - kth) {
		counter++;
		cin >> temp;
		if (temp < heap->getMin()) {
			//ignore
		}
		else {
			heap->deleteMin();
			heap->insert(temp);
		}
	}
	int ans = heap->getMin();
	heap->~BinaryHeap();
	//heap deleted
	return ans;
}