#include "AlgorithmSortK.h"

AlgorithmSortK::AlgorithmSortK(int k) : SelectionAlgorithm(k) {
	this->kth = k;
}

int AlgorithmSortK::select() {
	int array_length = 0;
	cin >> array_length;
	kth += 1;
	int* arr = 0;
	arr = new int[kth+1];

	int temp;
	for (int z = 0; z < kth; z++) {
		cin >> temp;
		arr[z] = temp;
	}

	int i, q, key;
	for (i = 1; i < kth; i++){
		key = arr[i];
		q = i - 1;
		while (q >= 0 && arr[q] > key) {
			arr[q + 1] = arr[q];
			q = q - 1;
		}
		arr[q + 1] = key;
	}

	int count = 0;
	while (count < array_length-kth){
		cin >> temp;
		for (i = kth - 1; (i >= 0 && arr[i] > temp); i--) {
				arr[i + 1] = arr[i];
		}
		arr[i + 1] = temp;
		count++;
	}
	
	int ans = arr[kth - 1];
	
	for (int i = 0; i < kth+1; i++) {
		arr[i] = 0;
	}
	delete[] arr;
	arr = 0;

	return ans ;
}