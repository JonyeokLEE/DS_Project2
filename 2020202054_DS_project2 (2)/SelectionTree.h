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
    //vector to save each node's pointer
    //(just save its pointer easy to access node)
    //Using LinkedList with out array

    ofstream* fout; //to write

    void destructor(SelectionTreeNode* pCur)
    {
        if (!pCur) return;
        else
        {
            destructor(pCur->getRightChild());
            destructor(pCur->getLeftChild());
            delete pCur;
        } //post-order delete
    }
    void CallDestructor()
    {
        destructor(root); //started from root
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
    //function to set and get root

    void settingSelection(); //create selection tree form

    void SelectionUp(); //rearrange SelectionTree from down to up

    bool Insert(LoanBookData* newData); //insert
    bool Delete(); //delete

    bool printBookData(int bookCode); //print st
};