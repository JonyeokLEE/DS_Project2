#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) //rearrange heap from down to up
{
    LoanBookHeapNode* curr = pN;
    LoanBookHeapNode* parent = curr->getParent();
    //set node pointer

    while (curr != root && curr->getBookData()->getName() < parent->getBookData()->getName())
    {   //untill curr is not root and curr's name is smaller than parent's

        LoanBookData* temp = parent->getBookData();
        parent->setBookData(curr->getBookData());
        curr->setBookData(temp);
        //swap curr and its parent

        curr = parent; //update curr to parent
        parent = curr->getParent(); //update parent

    }
}


void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) //rearrange heap from up to down
{
    if (!root)
        return;
    root->setBookData(pN->getBookData()); //set last node's data of root

    //pN is last Node from heap, and it became root and heapifydown

    if (pN->getParent()) //if pN has parent
    {
        //where is pN from its parent??

        if (pN->getParent()->getLeftChild() == pN) //left
        {
            pN->getParent()->setLeftChild(nullptr);
            pN->setParent(nullptr); //clear data
            LevelOrder.erase(LevelOrder.end() - 1); //delete from vector
        }
        else if (pN->getParent()->getRightChild() == pN) //right
        {
            pN->getParent()->setRightChild(nullptr);
            pN->setParent(nullptr); //clear data
            LevelOrder.erase(LevelOrder.end() - 1); //delete from vector
        }
    }
    else //there is no parent
    {
        LevelOrder.erase(LevelOrder.end() - 1);
        root = nullptr; //just erase
        return;
    }

    LoanBookHeapNode* curr = root; //starting point

    while (curr)
    {
        LoanBookHeapNode* left = curr->getLeftChild();
        LoanBookHeapNode* right = curr->getRightChild(); //set childern pointer
        LoanBookHeapNode* child = new LoanBookHeapNode(); //to set chile

        if (left != NULL && right != NULL) {
            child = (left->getBookData()->getName() < right->getBookData()->getName()) ? left : right;
        } //set child smaller one


        else if (left != NULL && right == NULL) //only left child
        {
            child = left;
        }
        else if (left == NULL && right != NULL) //only right child
        {
            child = right;
        }
        else //there is no child -> finish
            break;

        if (curr->getBookData()->getName() > child->getBookData()->getName())
        {   //if curr's name is bigger than child's name
            LoanBookData* temp = child->getBookData();
            child->setBookData(curr->getBookData());
            curr->setBookData(temp);
            //swap and update curr
            curr = child;
        }
        else //if curr's name is smaller than child's name
            break;

    }
}


bool LoanBookHeap::Insert(LoanBookData* data) //insert
{
    LoanBookHeapNode* newNode = new LoanBookHeapNode();
    newNode->setBookData(data);
    //create new node and set data

    if (root == nullptr) //there is not any node in heap
    {
        root = newNode; //set root newNode
        LevelOrder.push_back(nullptr);
        LevelOrder.push_back(newNode); //update vector
        return true;
    }
    else
    {
        int last = LevelOrder.size(); //get last node's position
        LoanBookHeapNode* parent = LevelOrder.at(last / 2); //and its parent
        if (last % 2 == 1) //if parent's right child is empty
        {
            parent->setRightChild(newNode);
            newNode->setParent(parent);
            LevelOrder.push_back(newNode); //set right child
        }
        else
        {
            parent->setLeftChild(newNode);
            newNode->setParent(parent);
            LevelOrder.push_back(newNode); //set left child
        }
    }
    heapifyUp(newNode); //after insert, rearrange heap
    return true;
}


bool LoanBookHeap::SortandPrint(ofstream& write)
{
    if (!root) //there is no node
    {
        return false;
    }
    vector<LoanBookHeapNode*> sorted; //copied vector to sort
    for (int i = 1; i < LevelOrder.size(); i++)
    {
        sorted.push_back(LevelOrder.at(i));
    } //copy all the pointer in heap

    //and bubble sort with there name
    for (int i = sorted.size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (sorted.at(j)->getBookData()->getName() > sorted.at(j + 1)->getBookData()->getName()) {
                LoanBookData* temp = sorted.at(j)->getBookData();
                sorted.at(j)->setBookData(sorted.at(j + 1)->getBookData());
                sorted.at(j + 1)->setBookData(temp);
            }
        }
    }

    //PRINT
    write << "========PRINT_ST========" << endl;
    for (int i = 0; i < sorted.size(); i++)
    {
        sorted.at(i)->getBookData()->PrintData(write);
    }
    write << "=========================" << endl << endl;
    return true;
}