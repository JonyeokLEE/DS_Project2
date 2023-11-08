#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"
#include <vector>
#include <algorithm>

class LoanBookHeap
{
private:
    LoanBookHeapNode* root;
    vector<LoanBookHeapNode*> LevelOrder;

public:
    LoanBookHeap() {
        this->root = NULL;
    };
    ~LoanBookHeap() {

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
