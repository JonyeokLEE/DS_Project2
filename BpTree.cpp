#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {

	if (!root)
	{
		BpTreeNode* firstNode = new BpTreeDataNode();
		firstNode->insertDataMap(newData->getName(), newData);
		root = firstNode;
		insertCount++;
		return true;
	}
	if (searchExistence(newData->getName()))
	{
		return true;
	}
	else
	{
		if (insertCount > 1) {

			BpTreeNode* StartPoint = searchDataNode(newData->getName());
			StartPoint->insertDataMap(newData->getName(), newData);
			insertCount++;
			if (excessDataNode(StartPoint))
			{
				splitDataNode(StartPoint);
				StartPoint = StartPoint->getParent();
				while (excessIndexNode(StartPoint))
				{
					splitIndexNode(StartPoint);
					StartPoint = StartPoint->getParent();
				}
			}
		}
		else
		{
			root->insertDataMap(newData->getName(), newData);
			insertCount++;
		}
		return true;
	}

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
	BpTreeNode* rootParent = new BpTreeIndexNode();
	BpTreeNode* SplitParent = new BpTreeIndexNode();
	if (pDataNode == root)
	{
		rootParent->setMostLeftChild(pDataNode);
		pDataNode->setParent(rootParent);
		root = rootParent;
	}

	auto p = (pDataNode->getDataMap()->begin());
	auto BeParent = ++(pDataNode->getDataMap()->begin());
	auto q = (pDataNode->getDataMap()->rbegin());

	BpTreeNode* qNode = new BpTreeDataNode();
	qNode->insertDataMap(q->first, q->second);
	qNode->insertDataMap(BeParent->first, BeParent->second);
	SplitParent = pDataNode->getParent();
	SplitParent->insertIndexMap(BeParent->first, qNode);
	qNode->setParent(SplitParent);
	if (pDataNode->getNext() != nullptr)
	{
		pDataNode->getNext()->setPrev(qNode);
		qNode->setNext(pDataNode->getNext());
	}
	pDataNode->setNext(qNode);
	qNode->setPrev(pDataNode);

	pDataNode->deleteMap(BeParent->first);
	pDataNode->deleteMap(q->first);
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	BpTreeNode* rootParent = new BpTreeIndexNode();
	BpTreeNode* SplitParent = new BpTreeIndexNode();
	if (pIndexNode == root)
	{
		rootParent->setMostLeftChild(pIndexNode);
		pIndexNode->setParent(rootParent);
		root = rootParent;
	}

	auto p = (pIndexNode->getIndexMap()->begin());
	auto BeParent = ++(pIndexNode->getIndexMap()->begin());
	auto q = (pIndexNode->getIndexMap()->rbegin());

	BpTreeNode* qNode = new BpTreeIndexNode();
	qNode->setMostLeftChild(BeParent->second);
	qNode->insertIndexMap(q->first, q->second);
	SplitParent = pIndexNode->getParent();
	SplitParent->insertIndexMap(BeParent->first, qNode);
	BeParent->second->setParent(qNode);
	q->second->setParent(qNode);
	qNode->setParent(SplitParent);

	pIndexNode->deleteMap(BeParent->first);
	pIndexNode->deleteMap(q->first);
}

BpTreeNode* BpTree::searchDataNode(string name) {
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
	return pCur;
}

bool BpTree::searchExistence(string name) {
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
	if (pCur->getDataMap()->find(name) == pCur->getDataMap()->end())
	{
		return false;
	}
	else
	{
		pCur->getDataMap()->find(name)->second->updateCount();
		return true;
	}
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

	if (pCur->getDataMap()->find(name) == pCur->getDataMap()->end())
	{
		*fout << "========ERROR========" << endl;
		*fout << "300" << endl;
		*fout << "=====================" << endl << endl;
		return false;
	}
	else if (pCur->getDataMap()->find(name)->second->getLoanCount() == -1)
	{
		*fout << "========ERROR========" << endl;
		*fout << "300" << endl;
		*fout << "=====================" << endl << endl;
		return false;
	}
	else
	{
		*fout << "========SEARCH_BP========" << endl;
		pCur->getDataMap()->find(name)->second->PrintData(*fout);
		*fout << "==========================" << endl << endl;
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
	int count = 0;
	auto save = pCur->getDataMap()->begin();
	BpTreeNode* CurrentNode = pCur;
	while (CurrentNode)
	{
		if (save->first >= toFind)
		{
			if (save->first > toEnd)
				break;
			else
			{
				if (save->second->getLoanCount() != -1)
				{
					SaveToPrint.push_back(save->second);
				}
				count++;
			}
		}
		save++;
		if (CurrentNode->getDataMap()->end() == save)
		{
			CurrentNode = CurrentNode->getNext();
			if (!CurrentNode) break;
			save = CurrentNode->getDataMap()->begin();

		}
	}
	if (count == 0)
	{
		*fout << "========ERROR========" << endl;
		*fout << "300" << endl;
		*fout << "=====================" << endl << endl;
		return false;
	}
	else
	{
		*fout << "========SEARCH_BP========" << endl;
		for (int i = 0; i < SaveToPrint.size(); i++)
		{
			if(SaveToPrint.at(i)->getCode() != -1)
			{
				SaveToPrint.at(i)->PrintData(*fout);
			}
		}
		*fout << "==========================" << endl << endl;
		SaveToPrint.clear();
		return true;
	}
}
bool BpTree::printAll()
{
	if (!root)
		return false;
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild())
	{

		pCur = pCur->getMostLeftChild(); // p = A0
	}
	int count = 0;
	auto save = pCur->getDataMap()->begin();
	BpTreeNode* CurrentNode = pCur;
	while (CurrentNode)
	{
		if (save->second->getLoanCount() != -1)
		{
			SaveToPrint.push_back(save->second);
		}
		count++;
		save++;
		if (CurrentNode->getDataMap()->end() == save)
		{
			CurrentNode = CurrentNode->getNext();
			if (!CurrentNode) break;
			save = CurrentNode->getDataMap()->begin();
		}
	}
	if (count == 0)
	{
		*fout << "========ERROR========" << endl;
		*fout << "400" << endl;
		*fout << "=====================" << endl << endl;
		return false;
	}
	else
	{
		*fout << "========PRINT_BP========" << endl;
		for (int i = 0; i < SaveToPrint.size()&&SaveToPrint.at(i)->getCode()!=-1; i++)
		{
			SaveToPrint.at(i)->PrintData(*fout);
		}
		*fout << "==========================" << endl << endl;
		SaveToPrint.clear();
		return true;
	}
}
bool BpTree::deleteBook(string name)
{
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

	if (pCur->getDataMap()->find(name) == pCur->getDataMap()->end())
	{
		return false;
	}
	else
	{
		pCur->getDataMap()->find(name)->second->DeleteCount();
		return true;
	}
}

