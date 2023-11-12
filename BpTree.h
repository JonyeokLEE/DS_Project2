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
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;
	int insertCount;
	vector<LoanBookData*> SaveToPrint;
public:
	BpTree() {
		root = NULL;
		this->order = 3;
		this->fout = nullptr;
		this->insertCount = 0;
	}
	BpTree(ofstream *fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
		this->insertCount = 0;
	}
	~BpTree()
	{
	}
	/* essential */
	bool		Insert(LoanBookData* newData);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(string name);

	bool searchExistence(string name);

	bool searchBook(string name);
	bool searchRange(string start, string end);

	bool printAll();

	bool deleteBook(string name);
	
};

#endif
