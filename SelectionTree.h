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
    //vector<int> savedCode;
    ofstream* fout;
    void destructor(SelectionTreeNode* pCur)
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
    SelectionTree() {
        this->root = NULL;
        this->fout = NULL;
    }
    SelectionTree(ofstream* fout) {
        this->root = NULL;
        this->fout = fout;
    }
    ~SelectionTree() {
        CallDestructor();
    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    void settingSelection();
    void SelectionUp();

    bool Insert(LoanBookData* newData);
    bool Delete();
    //void LevelOrderPrint();
    //void vectorPrint();
    //void vectorPrintEach(int code);
    bool printBookData(int bookCode);
};