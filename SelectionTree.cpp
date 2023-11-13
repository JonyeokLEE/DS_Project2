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
    root = selvector.at(1);
    while (count < 16)
    {
        SelectionTreeNode* curr = selvector.at(count);
        if (count < 8)
        {
            curr->setLeftChild(selvector.at(2 * count));
            curr->setRightChild(selvector.at(2 * count + 1));
        }
        if (count > 1)
        {
            curr->setParent(selvector.at(count / 2));
        }
        if (count > 7)
        {
            LoanBookHeap* newHeap = new LoanBookHeap();
            curr->setHeap(newHeap);
        }
        count++;
    }
}

void SelectionTree::SelectionUp()
{
    int level = 7;
    while (level > 0)
    {
        SelectionTreeNode* curr = selvector.at(level);
        SelectionTreeNode* left = curr->getLeftChild();
        SelectionTreeNode* right = curr->getRightChild();

        LoanBookData* copied = nullptr;
        if (!left->getBookData() && !right->getBookData())
        {
            copied = nullptr;
            curr->setBookData(copied);
        }
        else if (!left->getBookData() && right->getBookData())
        {
            copied = right->getBookData();
            curr->setBookData(copied);
        }
        else if (!right->getBookData() && left->getBookData())
        {
            copied = left->getBookData();
            curr->setBookData(copied);
        }
        else
        {
            if (right->getBookData()->getName() < left->getBookData()->getName())
            {
                copied = right->getBookData();
                curr->setBookData(copied);
            }
            else
            {
                copied = left->getBookData();
                curr->setBookData(copied);
            }
        }

        curr->setBookData(copied);
        level--;
    }
}

bool SelectionTree::Insert(LoanBookData* newData) {
    int location = newData->getCode() / 100 + 8;
    SelectionTreeNode* newone = selvector.at(location);

    newone->getHeap()->Insert(newData);
    newone->setBookData(selvector.at(location)->getHeap()->getRoot()->getBookData());
    SelectionUp();
    return true;
}


bool SelectionTree::Delete() {
    if (!root)
        return false;
    else if (!root->getBookData())
        return false;
    else
    {
        int location = root->getBookData()->getCode() / 100 + 8;
        SelectionTreeNode* curr = selvector.at(location);


        curr->getHeap()->heapifyDown(curr->getHeap()->getLastNode());
        if (!curr->getHeap()->getRoot())
        {
            curr->setBookData(nullptr);
        }
        else
        {
            curr->setBookData(curr->getHeap()->getRoot()->getBookData());
        }
        SelectionUp();
        return true;
    }
}

bool SelectionTree::printBookData(int bookCode) {

    if (bookCode < 0 || bookCode >700 || bookCode % 100 != 0)
        return false;

    else
    {
        if (!root->getBookData()) return false;
        int location = bookCode / 100 + 8;
        SelectionTreeNode* curr = selvector.at(location);

        if (curr->getHeap()->getRoot() == nullptr)
            return false;
        if (!curr->getHeap()->SortandPrint(*fout))
            return false;
        else return true;
    }
}


