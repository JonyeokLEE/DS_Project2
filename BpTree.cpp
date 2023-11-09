#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {

	BpTreeNode* StartPoint = searchDataNode(newData->getName());
	
	StartPoint->insertDataMap(newData->getName(), newData);
	insertCount++;
	{
		if (insertCount > 2)
			if (excessDataNode(StartPoint))
			{
				splitDataNode(StartPoint);
				StartPoint = StartPoint->getParent();
			}
		while (excessIndexNode(StartPoint))
		{
			splitIndexNode(StartPoint);
			StartPoint = StartPoint->getParent();
		}
	}
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
	BpTreeNode* ToSplit = pDataNode;
	BpTreeNode* SplitParent = ToSplit->getParent();

	auto p = (ToSplit->getDataMap()->begin());
	auto BeParent = ++(ToSplit->getDataMap()->begin());
	auto q = (ToSplit->getDataMap()->rbegin());
	
	BpTreeNode* pNode = new BpTreeDataNode();
	pNode->insertDataMap(p->first,p->second);

	BpTreeNode* qNode = new BpTreeDataNode();
	qNode->insertDataMap(BeParent->first, BeParent->second);
	qNode->insertDataMap(q->first, q->second);
	SplitParent->insertIndexMap(BeParent->first, qNode);

	SplitParent->setMostLeftChild(pNode);
	pNode->setParent(SplitParent);
	qNode->setParent(SplitParent);

	pNode->setNext(qNode);
	qNode->setPrev(pNode);
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	BpTreeNode* ToSplit = pIndexNode;
	BpTreeNode* SplitParent = new BpTreeDataNode();
	if (ToSplit != root)
	{
		BpTreeNode* SplitParent = ToSplit->getParent();
	}

	auto p = (ToSplit->getIndexMap()->begin());
	auto BeParent = ++(ToSplit->getIndexMap()->begin());
	auto q = (ToSplit->getIndexMap()->rbegin());

	BpTreeNode* pNode = new BpTreeDataNode();
	pNode->setMostLeftChild(ToSplit->getMostLeftChild());
	pNode->insertIndexMap(p->first, p->second);

	BpTreeNode* qNode = new BpTreeDataNode();
	qNode->setMostLeftChild(BeParent->second);
	qNode->insertIndexMap(q->first, q->second);

	SplitParent->insertIndexMap(BeParent->first, qNode);
	SplitParent->setMostLeftChild(pNode);
	pNode->setParent(SplitParent);
	qNode->setParent(SplitParent);

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
				if (pCur->getIndexMap()->rbegin()->first > toFind) // k1 <= name < k2
				{
					pCur = pCur->getIndexMap()->begin()->second; // p = A1
				}
				else // k2 <= name
				{
					pCur = pCur->getIndexMap()->rbegin()->second; //p = A2
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
	if (!root)
		return false;

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
				if (pCur->getIndexMap()->rbegin()->first > toFind) // k1 <= name < k2
				{
					pCur = pCur->getIndexMap()->begin()->second; // p = A1
				}
				else // k2 <= name
				{
					pCur = pCur->getIndexMap()->rbegin()->second; //p = A2
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

	if (pCur->getDataMap()->find(name)->first != toFind)
	{
		return false;
	}
	else
	{
		pCur->getDataMap()->find(name)->second->PrintData(*fout);
		return true;
	}
	
}

bool BpTree::searchRange(string start, string end) {
	if (!root)
		return false;

	BpTreeNode* pCur = root;

	string toFind = start;
	string toEnd = end;

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
				if (pCur->getIndexMap()->rbegin()->first > toFind) // k1 <= name < k2
				{
					pCur = pCur->getIndexMap()->begin()->second; // p = A1
				}
				else // k2 <= name
				{
					pCur = pCur->getIndexMap()->rbegin()->second; //p = A2
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
	auto StartingMap = pCur->getDataMap();
	auto save = StartingMap->begin();
	for (auto iter = StartingMap->begin(); iter != StartingMap->end(); iter++)
	{
		if (iter->first >= toFind)
		{
			break;
		}
		save++;
	}

	int count = 0;

	BpTreeNode* CurrentNode = pCur;
	while (CurrentNode)
	{
		if (save->first > end)
			break;
		else
		{
			save->second->PrintData(*fout);
		}
		count++;
	}
	if (count == 0)
		return false;
	else
		return true;
}

