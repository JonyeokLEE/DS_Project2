#include "SelectionTree.h"

void SelectionTree::settingSelection() //to setting selecion tree form
{
    selvector.push_back(nullptr); //empty first index

    for (int i = 1; i < 16; i++)
    {
        SelectionTreeNode* newNode = new SelectionTreeNode();
        selvector.push_back(newNode);
    } //create all node and store their pointer to vector

    int count = 1; //to start at index 1
    root = selvector.at(1); //set root

    while (count < 16) //untill end of selection tree
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
        //set their relationship

        //if leaf node, create Heap pointer and connect
        if (count > 7)
        {
            LoanBookHeap* newHeap = new LoanBookHeap();
            curr->setHeap(newHeap);
        }
        count++;
    }
}

void SelectionTree::SelectionUp() //rearrange selection tree down to up
{
    int level = 7; //start from leaf node
    while (level > 0) //untill root
    {
        SelectionTreeNode* curr = selvector.at(level);
        SelectionTreeNode* left = curr->getLeftChild();
        SelectionTreeNode* right = curr->getRightChild();

        LoanBookData* copied = nullptr; //to copy data
        if (!left->getBookData() && !right->getBookData())
        {
            //there is no children
            copied = nullptr;
            curr->setBookData(copied); //copy nullptr

        }
        else if (!left->getBookData() && right->getBookData()) //only right child
        {
            copied = right->getBookData();
            curr->setBookData(copied); //copy right child's data
        }
        else if (!right->getBookData() && left->getBookData()) //only left child
        {
            copied = left->getBookData();
            curr->setBookData(copied); //copy left child's data
        }
        else //both child
        {
            //compare right and left, and copy smaller one's data
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
    int location = newData->getCode() / 100 + 8; //calculate location
    SelectionTreeNode* newone = selvector.at(location); //create new node pointer

    newone->getHeap()->Insert(newData); //insert to heap
    newone->setBookData(selvector.at(location)->getHeap()->getRoot()->getBookData());
    //update root's data

    SelectionUp(); //rearrange selection tree
    return true;
}


bool SelectionTree::Delete() {

    if (!root) //there is not any node in heap
        return false;
    else if (!root->getBookData()) //there is not any data from root
        return false;
    else
    {
        int location = root->getBookData()->getCode() / 100 + 8;
        //get root's location

        SelectionTreeNode* curr = selvector.at(location);

        curr->getHeap()->heapifyDown(curr->getHeap()->getLastNode()); //delete it and rearrange heap
        if (!curr->getHeap()->getRoot())
        {
            curr->setBookData(nullptr);
        }
        else
        {
            curr->setBookData(curr->getHeap()->getRoot()->getBookData());
        }
        //and update new leaf

        SelectionUp(); //rearrange
        return true;
    }
}

bool SelectionTree::printBookData(int bookCode) {

    if (bookCode < 0 || bookCode >700 || bookCode % 100 != 0) //Wrong Code entered
        return false;

    else
    {
        //get to the leaf node and call SortAndPrint Function of Heap
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


