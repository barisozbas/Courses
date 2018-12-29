#include "TestBed.h"
#include <ctime>


TestBed::TestBed() {
}

void TestBed::setAlgorithm(int a , int k ) {
	if(a == 1) {
		algorithm = new AlgorithmSortAll(k);
	}
	if (a == 2) {
		algorithm = new AlgorithmSortK(k);
	}
	if (a == 3) {
		algorithm = new AlgorithmSortHeap(k);
	}
	if (a == 4) {
		algorithm = new AlgorithmSortQuick(k);
	}
}


void TestBed::execute() {
	int ans;
	clock_t start = clock();

	ans = algorithm->select();

	clock_t end = clock();
	double cpu_time = static_cast <double>(end - start);

	cout << "Result: " << ans << endl;
	cout << "Duration(sec): " << cpu_time << endl;

}

TestBed::~TestBed() {
	delete algorithm;
}