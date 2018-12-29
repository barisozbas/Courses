#ifndef ALGORITHMSORTQUICK_H
#define ALGORITHMSORTQUICK_H

#include "SelectionAlgorithm.h"

using namespace std;

class AlgorithmSortQuick : public SelectionAlgorithm {
public:
	int select();
	int quickselect(int*,int,int,int);
	AlgorithmSortQuick(int);
};


#endif // !ALGORITHMSORTQUICK_
