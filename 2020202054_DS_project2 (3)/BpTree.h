#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include <fstream>
#include <iostream>
#include <vector>

class BpTree {
private:
	BpTreeNode* root; //root pointer
	int			order;		// m children
	ofstream* fout; //to write
	int insertCount; //to know it has only 
	vector<LoanBookData*> SaveToPrint; //to use when PRINT_BP_RANGE

public:
	BpTree()
	{
		root = NULL;
		this->order = 3;
		this->fout = nullptr;
		this->insertCount = 0;
	}
	BpTree(ofstream *fout, int order = 3) //constructor
	{
		root = NULL;
		this->order = order;
		this->fout = fout;
		this->insertCount = 0;
	}
	~BpTree() //destructor
	{
	}
	/* essential */
	bool		Insert(LoanBookData* newData); //insert new Node
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }

	//search function
	BpTreeNode* searchDataNode(string name);
	bool searchExistence(string name);
	bool searchBook(string name);
	bool searchRange(string start, string end);

	//to Print All Data
	bool printAll();

	//DELETE
	bool deleteBook(string name);
	
};

#endif
