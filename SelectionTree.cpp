#include "SelectionTree.h"

void SelectionTree::settingSelection()
{
    selvector.push_back(nullptr);
    for (int i = 1; i < 16; i++)
    {
        SelectionTreeNode* newNode = new SelectionTreeNode();
        selvector.push_back(newNode);
    }
    int count = 1;
    while (count < 16)
    {
        if (count < 8)
        {
            selvector.at(count)->setLeftChild(selvector.at(2 * count));
            selvector.at(count)->setRightChild(selvector.at(2 * count + 1));
        }
        if (count > 1)
        {
            selvector.at(count)->setParent(selvector.at(count/2));
        }
        count++;
    }
}

void SelectionTree::SelectionUp()
{
    for (int i = 7; i > 0; i--)
    {
        int j = 2 * i;
        if (selvector.at(j)->getBookData()->getName() < selvector.at(j + 1)->getBookData()->getName())
        {
            selvector.at(i)->setBookData(selvector.at(j + 1)->getBookData());
        }
        else
            selvector.at(i)->setBookData(selvector.at(j)->getBookData());
    }
}



bool SelectionTree::Insert(LoanBookData* newData) {
    
    //Run 새로 들어오면 연결시켜주고 관리


    SelectionUp();
}


bool SelectionTree::Delete() {
    if (!root)
        return false;

    else
    {
        int location = 0;
        for (int i = 8; i < 16; i++)
        {
            if (root->getBookData()->getName() == selvector.at(i)->getBookData()->getName())
            {
                location = i;
                break;
            }
        }
        selvector.at(location)->getHeap()->heapifyDown(selvector.at(location)->getHeap()->getRoot());
        SelectionUp();
        return true;
    }
}

bool SelectionTree::printBookData(int bookCode) {
    
    if (bookCode < 100 || bookCode >700 || bookCode % 100 != 0)
        return false;

    else
    {
        int location = 0;
        for (int i = 8; i < 16; i++)
        {
            if (root->getBookData()->getName() == selvector.at(i)->getBookData()->getName())
            {
                location = i;
                break;
            }
        }


        if (selvector.at(location)->getHeap()->getRoot() == nullptr)
            return false;
        if (!selvector.at(location)->getHeap()->SortandPrint(*fout))
            return false;
        else return true;
    }
}
