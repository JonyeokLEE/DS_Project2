#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {


	return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	
}

BpTreeNode* BpTree::searchDataNode(string name) {
	if (!root)
		return nullptr;

	BpTreeNode* pCur = root;

	string toFind = name;

	while (pCur->getMostLeftChild())
	{

		if (pCur->getIndexMap()->size() == 2) // A0 [(K1,A1) , (K2,A2)] 
		{
			if (pCur->getIndexMap()->begin()->first > toFind) //name < k1
			{
				pCur = pCur->getMostLeftChild(); // p = A0
			}
			else // k1 <= name
			{
				if (pCur->getIndexMap()->end()->first > toFind) // k1 <= name < k2
				{
					pCur = pCur->getIndexMap()->begin()->second; // p = A1
				}
				else // k2 <= name
				{
					pCur = pCur->getIndexMap()->end()->second; //p = A2
				}
			}
		}
		else // A0 [(K1,A1)] 
		{
			if (pCur->getIndexMap()->begin()->first > toFind) //name < k1
			{
				pCur = pCur->getMostLeftChild(); // p = A0
			}
			else // k1 <= name
			{
				pCur = pCur->getIndexMap()->begin()->second; // p = A1
			}
		}
	}
	//found
	return pCur;
}

bool BpTree::searchBook(string name) {
	
}

bool BpTree::searchRange(string start, string end) {
	
}
