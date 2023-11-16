#pragma once
#include "SelectionTree.h"
#include "BpTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream> //include header
using namespace std;

class Manager //Manager Class
{
private:
	string cmd; //to read Command
	BpTree* bptree; //Bptree pointer
	SelectionTree* stree; //SelectionTree Pointer
	ifstream fin; //to Read
	ofstream flog; //to Write

public:
	Manager();
	Manager(int bpOrder); //constructor
	~Manager(); //destructor
	

	void run(const char* command); //run
	bool LOAD(); //LOAD command
	bool ADD(string command); //ADD command

	bool SEARCH_BP(string ToSearch);

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end); //SEARCH_BP command

	bool PRINT_BP(); //PRINT_BP command
	bool PRINT_ST(int CodeToFind); //PRINT_ST command

	bool DELETE(); //DELETE command

	void printErrorCode(int n); //To Print Error Code
	void printSuccessCode(const char* cmd); //To Print Success Code

};

