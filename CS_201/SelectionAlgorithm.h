#ifndef SELECTIONALGORITHM_H
#define SELECTIONALGORITHM_H
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

class SelectionAlgorithm {
public:
	virtual int select();
	SelectionAlgorithm(int);
	int kth = 0;

};

#endif 
