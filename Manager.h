#pragma once
#include "SelectionTree.h"
#include "BpTree.h"
//#include "LoanBookData.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

class Manager
{
private:
	string cmd;
	BpTree* bptree;
	SelectionTree* stree;
	ifstream fin;
	ofstream flog;

public:
	Manager();
	Manager(int bpOrder);
	~Manager();
	

	void run(const char* command);
	bool LOAD();
	bool ADD(string command);

	bool SEARCH_BP(string ToSearch);

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST(int CodeToFind);

	bool DELETE();

	void printErrorCode(int n);
	void printSuccessCode(const char* cmd);

};

