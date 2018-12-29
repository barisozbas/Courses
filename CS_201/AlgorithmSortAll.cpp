#include "AlgorithmSortAll.h"

AlgorithmSortAll::AlgorithmSortAll(int k) : SelectionAlgorithm(k){
	this -> kth = k;
}


int AlgorithmSortAll::select() {
	int array_length = 0;
	cin >> array_length;
	int* arr = NULL;
	arr = new int[array_length];

	int temp;
	for (int i = 0; i < array_length; i++) {
		cin >> temp;
		arr[i] = temp;
	}

	int i, q, key;
	for (i = 1; i < array_length; i++)
	{
		key = arr[i];
		q = i - 1;
		while (q >= 0 && arr[q] > key){
			arr[q + 1] = arr[q];
			q = q - 1;
		}
		arr[q + 1] = key;
	}

	int ans = arr[kth];

	for (int i = 0; i < kth; i++) {
		arr[i] = 0;
	}
	delete [] arr;
	arr = 0;

	return ans;
    
}







