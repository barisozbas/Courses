#include <iostream>
#include <string>
#include <fstream>
#include "TestBed.h"

using namespace std;
int main(int argc, char *argv[]) {
	string testfile;
	if (argc < 2) {
		cout << "Enter a test file name:" << endl;
		cin >> testfile;
	}
	else {
		testfile = argv[1];
	}
	ifstream file(testfile.c_str());
	if (file.is_open()) {
		cin.rdbuf(file.rdbuf());
	}
	else {
		cout << "Error: cannot read the test file!" << endl;
		return -1;
	}

	int algorithm_number = 0;
	cin >> algorithm_number;
	
	int k = 0;
	cin >> k;

	TestBed *test = new TestBed();
	test->setAlgorithm(algorithm_number, k);
	test->execute();
	test->~TestBed();
	return 0;
}