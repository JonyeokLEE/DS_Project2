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

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);

    bool Insert(LoanBookData* data);

    bool SortandPrint(ofstream& write);
};
