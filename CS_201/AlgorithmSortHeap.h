#ifndef ALGORITHMSORTHEAP_H
#define ALGORITHMSORTHEAP_H

#include "SelectionAlgorithm.h"
#include "BinaryHeap.h"

using namespace std;

class AlgorithmSortHeap : public SelectionAlgorithm {
public:
	int select();
	AlgorithmSortHeap(int);

};



#endif