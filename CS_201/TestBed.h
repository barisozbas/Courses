#ifndef TESTBED_H
#define TESTBED_H
#include "SelectionAlgorithm.h"
#include "AlgorithmSortAll.h"
#include "AlgorithmSortK.h"
#include "AlgorithmSortHeap.h"
#include "AlgorithmSortQuick.h"

using namespace std;

class TestBed {
public:
	TestBed();
	void execute();
	void setAlgorithm(int, int);
	~TestBed();
	SelectionAlgorithm *algorithm;
private:
	int kth;

};


#endif // !TESTBED_H
