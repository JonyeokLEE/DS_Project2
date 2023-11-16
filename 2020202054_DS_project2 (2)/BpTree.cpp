#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) //INSERT
{
	if (!root) //there is not any node in BpTree
	{
		BpTreeNode* firstNode = new BpTreeDataNode();
		firstNode->insertDataMap(newData->getName(), newData); //insert
		root = firstNode; //set root
		insertCount++; //update count
		return true;
	}
	if (searchExistence(newData->getName())) //if there is Node which is same with New Node
	{
		return true;
	}
	else
	{
		if (insertCount > 1) //if entered nodes are two
		{
			BpTreeNode* StartPoint = searchDataNode(newData->getName()); //search location of DataNode
			StartPoint->insertDataMap(newData->getName(), newData); //insert that place
			insertCount++; //update count
			if (excessDataNode(StartPoint)) //if to split data node
			{
				splitDataNode(StartPoint); //split data node
				StartPoint = StartPoint->getParent(); //go to parent
				while (excessIndexNode(StartPoint)) //split index node until it is okay
				{
					splitIndexNode(StartPoint); //split index node
					StartPoint = StartPoint->getParent(); //go to parent
				}
			}
		}
		else //if entered node is one
		{
			root->insertDataMap(newData->getName(), newData); //just insert to data node
			insertCount++; //update count
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

void BpTree::splitDataNode(BpTreeNode* pDataNode) //function to split data node
{
	BpTreeNode* rootParent = new BpTreeIndexNode();
	BpTreeNode* SplitParent = new BpTreeIndexNode(); //splited node's parent
	if (pDataNode == root) //if this datanode is root
	{
		rootParent->setMostLeftChild(pDataNode); //create parent
		pDataNode->setParent(rootParent);
		root = rootParent; //update root
	}
	else //else
	{
		delete rootParent; //just delete
	}

	auto p = (pDataNode->getDataMap()->begin()); //p
	auto BeParent = ++(pDataNode->getDataMap()->begin()); //Map to be parent
	auto q = (pDataNode->getDataMap()->rbegin()); //q

	BpTreeNode* qNode = new BpTreeDataNode();
	qNode->insertDataMap(q->first, q->second);
	qNode->insertDataMap(BeParent->first, BeParent->second);
	//create qNode and insert BeParent and q

	SplitParent = pDataNode->getParent(); //SplitParent is splited node's parent
	SplitParent->insertIndexMap(BeParent->first, qNode); //insert Index Map
	qNode->setParent(SplitParent); //set parent

	if (pDataNode->getNext() != nullptr) //if pDataNode has next Node before
	{
		pDataNode->getNext()->setPrev(qNode);
		qNode->setNext(pDataNode->getNext());
	}
	pDataNode->setNext(qNode);
	qNode->setPrev(pDataNode);
	//set there relationship

	pDataNode->deleteMap(BeParent->first);
	pDataNode->deleteMap(q->first); //delete data of BeParent and q in pDataNode
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) //function to split index node
{
	BpTreeNode* rootParent = new BpTreeIndexNode(); //root's parent
	BpTreeNode* SplitParent = new BpTreeIndexNode(); //splited node's parent

	if (pIndexNode == root) //if splited index node is root
	{
		rootParent->setMostLeftChild(pIndexNode);
		pIndexNode->setParent(rootParent);
		root = rootParent;
	}
	else //else
	{
		delete rootParent; //just delete
	}

	auto p = (pIndexNode->getIndexMap()->begin());
	auto BeParent = ++(pIndexNode->getIndexMap()->begin());
	auto q = (pIndexNode->getIndexMap()->rbegin()); //set Map like splitdatanode fuction

	BpTreeNode* qNode = new BpTreeIndexNode(); //make qNode and insert data
	qNode->setMostLeftChild(BeParent->second);
	qNode->insertIndexMap(q->first, q->second);

	SplitParent = pIndexNode->getParent();
	SplitParent->insertIndexMap(BeParent->first, qNode);
	BeParent->second->setParent(qNode);
	q->second->setParent(qNode);
	qNode->setParent(SplitParent);
	//set their relationship

	pIndexNode->deleteMap(BeParent->first);
	pIndexNode->deleteMap(q->first); //delete data
}

BpTreeNode* BpTree::searchDataNode(string name)
{
	BpTreeNode* pCur = root; //start from root
	string toFind = name;

	while (pCur->getMostLeftChild()) //find the way until datanode
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
	return pCur; //return this datanode
}

bool BpTree::searchExistence(string name) //function to know there alredy exists node with name?
{
	if (!root)
		return false;

	BpTreeNode* pCur = root; //starting point
	string toFind = name;

	while (pCur->getMostLeftChild()) //find the way until datanode
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
	if (pCur->getDataMap()->find(name) == pCur->getDataMap()->end()) //fail to find
	{
		return false;
	}
	else //already exist?
	{
		pCur->getDataMap()->find(name)->second->updateCount(); //just update count
		return true;
	}
}

bool BpTree::searchBook(string name) {
	if (!root)
		return false;

	BpTreeNode* pCur = root;

	string toFind = name;

	while (pCur->getMostLeftChild()) //find the way until datanode
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

	if (pCur->getDataMap()->find(name) == pCur->getDataMap()->end()) //fail to find
	{
		*fout << "========ERROR========" << endl;
		*fout << "300" << endl;
		*fout << "=====================" << endl << endl;
		return false;
	}
	else if (pCur->getDataMap()->find(name)->second->getLoanCount() == -1) //if node is alreay deleted
	{
		*fout << "========ERROR========" << endl;
		*fout << "300" << endl;
		*fout << "=====================" << endl << endl;
		return false;
	}
	else //find
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
	char change = end[0] + 1;
	toEnd.append(1, change);

	while (pCur->getMostLeftChild()) //find the way until datanode with starting point
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

	auto save = pCur->getDataMap()->begin(); //starting point

	BpTreeNode* CurrentNode = pCur;
	while (CurrentNode) //traversal datanode
	{
		if (save->first >= toFind) //if it is in range?
		{
			if (save->first.front() >= toEnd.at(toEnd.size()-1)) //out of range
				break;
			else //in range
			{
				if (save->second->getLoanCount() != -1) //and it is not deleted
				{
					SaveToPrint.push_back(save->second); //save to vector
				}
				count++; //update count
			}
		}
		save++; //to next map
		if (CurrentNode->getDataMap()->end() == save) //if it is end
		{
			CurrentNode = CurrentNode->getNext(); //move to next node
			if (!CurrentNode) break; //there is no node -> break
			save = CurrentNode->getDataMap()->begin(); //begin at its starting point

		}
	}
	if (count == 0) //there is no data in this range
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
		SaveToPrint.clear(); //clear vector (for next time)
		return true;
	}
}
bool BpTree::printAll() //Print all data in bptree
{
	if (!root)
		return false;
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild()) //just get to most left data node
	{

		pCur = pCur->getMostLeftChild(); // p = A0
	}
	int count = 0;
	auto save = pCur->getDataMap()->begin();
	BpTreeNode* CurrentNode = pCur;
	while (CurrentNode) //same with search range
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
		//store data in vector
	}
	if (count == 0) //noting to print
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
		SaveToPrint.clear(); //clear vector for next time
		return true;
	}
}
bool BpTree::deleteBook(string name)
{
	if (!root)
		return false;

	BpTreeNode* pCur = root;

	string toFind = name;

	while (pCur->getMostLeftChild()) //find the way until datanode
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

	if (pCur->getDataMap()->find(name) == pCur->getDataMap()->end()) //there is no datanode which is i find
	{
		return false;
	}
	else
	{
		pCur->getDataMap()->find(name)->second->DeleteCount(); //delete count
		return true;
	}
}

