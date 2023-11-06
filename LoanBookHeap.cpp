#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN)
{
    LoanBookHeapNode* curr = pN;
    LoanBookHeapNode* parent = curr->getParent();
    while (curr != root && curr->getBookData()->getName() < parent->getBookData()->getName())
    {

        LoanBookData* temp = parent->getBookData();
        parent->setBookData(curr->getBookData());
        curr->setBookData(temp);

        curr = parent;
        parent = curr->getParent();

    }
}


void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
    LoanBookHeapNode* curr = pN;

    while (curr)
    {
        LoanBookHeapNode* left = curr->getLeftChild();
        LoanBookHeapNode* right = curr->getRightChild();
        LoanBookHeapNode* child = new LoanBookHeapNode();

        if (left != NULL && right != NULL) {
            child = (left->getBookData()->getName() < right->getBookData()->getName()) ? left : right;
        }
        else if (left != NULL && right == NULL) {
            child = left;
        }
        else if (left == NULL && right != NULL)
        {
            child = right;
        }
        else
            break;

        if (curr->getBookData()->getName() > child->getBookData()->getName())
        {
            LoanBookData* temp = child->getBookData();
            child->setBookData(curr->getBookData());
            curr->setBookData(temp);

            child = curr;
            curr = child->getParent();
        }

        else
            break;

    }
}


bool LoanBookHeap::Insert(LoanBookData* data)
{
    LoanBookHeapNode* newNode = new LoanBookHeapNode();
    newNode->setBookData(data);

    if (root == nullptr)
    {
        root = newNode;
        LevelOrder.push_back(nullptr);
        LevelOrder.push_back(newNode);
        return true;
    }
    else
    {
        int last = LevelOrder.size();
        LoanBookHeapNode* parent = LevelOrder.at(last / 2);
        if (last % 2 == 1)
        {
            parent->setRightChild(newNode);
            newNode->setParent(parent);
            LevelOrder.push_back(newNode);
        }
        else
        {
            parent->setLeftChild(newNode);
            newNode->setParent(parent);
            LevelOrder.push_back(newNode);
        }
    }
    heapifyUp(newNode);
    return true;
}