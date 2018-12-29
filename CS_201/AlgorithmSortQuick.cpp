#include "AlgorithmSortQuick.h"



AlgorithmSortQuick::AlgorithmSortQuick(int k) : SelectionAlgorithm(k){
	this->kth = k;
}

int AlgorithmSortQuick::select() {
	int array_length = 0;
	cin >> array_length;

	int* arr = new int[array_length];

	int temp;
	for (int i = 0; i < array_length; i++) {
		cin >> temp;
		arr[i] = temp;
	}



	if (array_length <= 10) {
		int i, q, key;
		for (i = 1; i < array_length; i++) {
			key = arr[i];
			q = i - 1;
			while (q >= 0 && arr[q] > key) {
				arr[q + 1] = arr[q];
				q = q - 1;
			}
			arr[q + 1] = key;
		}
	}//insertion sort if length less or equal to 10 

    return quickselect(arr, 0, array_length-1, kth);



}

int AlgorithmSortQuick::quickselect(int arr[], int l, int r, int k) {
	if (k > 0 && k <= r - l + 1) {
		int position = l, element = arr[r];

		for (int a = l; a <= r - 1; a++) {
			if (arr[a] <= element) {
				int temp = arr[position];
				arr[position] = arr[a];
				arr[a] = temp;
				position++;
			}
		}
		int temp = arr[position];
		arr[position] = arr[r];
		arr[r] = temp;

		if (position - l == k - 1)
			return arr[position+1];
		
		if (position - l > k - 1)
			return quickselect(arr, l, position - 1, k);

		else
			return quickselect(arr, position + 1, r, k - position + l - 1);


	}
	return -1; //if k is more than the elements
}
