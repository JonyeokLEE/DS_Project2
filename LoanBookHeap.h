#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"
#include <vector>

class LoanBookHeap
{
private:
    LoanBookHeapNode* root;
    vector<LoanBookHeapNode*> LevelOrder;
    void destructor(LoanBookHeapNode* pCur)
    {
        if (!pCur) return;
        else
        {
            destructor(pCur->getRightChild());
            destructor(pCur->getLeftChild());
            delete pCur;
        }
    }
    void CallDestructor()
    {
        destructor(root);
    }
public:
    LoanBookHeap() {
        this->root = NULL;
    };
    ~LoanBookHeap() {
        CallDestructor();
    }

    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }
    LoanBookHeapNode* getLastNode() { return LevelOrder.at(LevelOrder.size() - 1); }

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);

    bool Insert(LoanBookData* data);

    //void LevelOrderPrint();

    //void vectorPrint();

    //void SortAndPrint(int BookCode);

    bool SortandPrint(ofstream& write);
};
