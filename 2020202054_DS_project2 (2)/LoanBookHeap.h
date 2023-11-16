#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"
#include <vector>

class LoanBookHeap
{
private:
    LoanBookHeapNode* root;
    vector<LoanBookHeapNode*> LevelOrder;
    //vector to save each node's pointer
    //(just save its pointer easy to access node)
    //Using LinkedList with out array

    void destructor(LoanBookHeapNode* pCur)
    {
        if (!pCur) return;
        else
        {
            destructor(pCur->getRightChild());
            destructor(pCur->getLeftChild());
            delete pCur;
            //post-order destructor
        }
    }
    void CallDestructor()
    {
        destructor(root); //call destructor from root
    }
public:
    LoanBookHeap() {
        this->root = NULL;
    };
    ~LoanBookHeap() {
        CallDestructor(); //destruct all data
    }

    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }
    LoanBookHeapNode* getLastNode() { return LevelOrder.at(LevelOrder.size() - 1); }
    //to set and get data

    void heapifyUp(LoanBookHeapNode* pN);
    //rearrange heap from down to up
    void heapifyDown(LoanBookHeapNode* pN);
    //rearrange heap from up to down

    bool Insert(LoanBookData* data); //insert to heap
    bool SortandPrint(ofstream& write); //sort upper case and print
};
