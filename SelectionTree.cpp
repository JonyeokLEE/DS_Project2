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



bool SelectionTree::Insert(LoanBookData* newData) {
    
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


bool SelectionTree::Delete() {

}

bool SelectionTree::printBookData(int bookCode) {
    

    return true;
}
