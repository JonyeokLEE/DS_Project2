#pragma once
#include "SelectionTreeNode.h"
#include "LoanBookHeap.h"
#include <fstream>
#include <iostream>
#include <vector>

class SelectionTree
{
private:
    SelectionTreeNode* root;
    vector<SelectionTreeNode*> selvector;
    ofstream* fout;

public:
    SelectionTree(ofstream* fout) {
        this->root = NULL;
        this->fout = fout;
    }
    ~SelectionTree() {

    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    void settingSelection();
    void SelectionUp();

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);
};