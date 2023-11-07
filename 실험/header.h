#pragma once
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

class LoanBookData
{
private:
    string name;
    int code;
    string author;
    int year;
    int loan_count;

public:
    LoanBookData() { this->loan_count = 0; }
    ~LoanBookData() {};

    void setBookData(string name, int code, string author, int year) {
        this->name = name;
        this->code = code;
        this->author = author;
        this->year = year;
    }

    void setName(string name) { this->name = name; }
    void setCode(int code) { this->code = code; }
    void setAuthor(string author) { this->author = author; }
    void setYear(int year) { this->year = year; }
    void updateCount() { this->loan_count += 1; }

    string getName() { return name; }
    int getCode() { return code; }
    string getAuthor() { return author; }
    int getYear() { return year; }
    int getLoanCount() { return loan_count; }
    /*
    void PrintData(ofstream& write)
    {
        write << getName() << "/" << getCode() << "/" << getAuthor() << "/" << getLoanCount() << endl;
    }*/
};

class LoanBookHeapNode
{
private:
    LoanBookData* pData;
    LoanBookHeapNode* pLeft;
    LoanBookHeapNode* pRight;
    LoanBookHeapNode* pParent;

public:
    LoanBookHeapNode() {
        this->pData = NULL;
        this->pLeft = NULL;
        this->pRight = NULL;
        this->pParent = NULL;
    }
    ~LoanBookHeapNode() {

    }

    void setBookData(LoanBookData* data) { this->pData = data; }
    void setLeftChild(LoanBookHeapNode* pL) { this->pLeft = pL; }
    void setRightChild(LoanBookHeapNode* pR) { this->pRight = pR; }
    void setParent(LoanBookHeapNode* pP) { this->pParent = pP; }

    LoanBookData* getBookData() { return pData; }
    LoanBookHeapNode* getLeftChild() { return pLeft; }
    LoanBookHeapNode* getRightChild() { return pRight; }
    LoanBookHeapNode* getParent() { return pParent; }
};

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

    void LevelOrderPrint();

    void vectorPrint();

    void SortAndPrint(int BookCode);

    //bool SortandPrint(ofstream& write);
};

class SelectionTreeNode
{
private:
    LoanBookData* pData;
    SelectionTreeNode* pLeft;
    SelectionTreeNode* pRight;
    SelectionTreeNode* pParent;
    LoanBookHeap* hRoot;


public:
    SelectionTreeNode() {
        this->pData = NULL;
        this->pLeft = NULL;
        this->pRight = NULL;
        this->pParent = NULL;
        this->hRoot = NULL;
    }
    ~SelectionTreeNode() {

    }

    void setBookData(LoanBookData* data) { this->pData = data; }
    void setLeftChild(SelectionTreeNode* pL) { this->pLeft = pL; }
    void setRightChild(SelectionTreeNode* pR) { this->pRight = pR; }
    void setParent(SelectionTreeNode* pP) { this->pParent = pP; }
    void setHeap(LoanBookHeap* pHR) { this->hRoot = pHR; }

    // function to output heap data stored in LoanBookHeap according to book classification code
    LoanBookHeapNode* deepCopy(LoanBookHeapNode* root) {
        if (root == NULL) return nullptr;

        LoanBookHeapNode* copy = new LoanBookHeapNode();
        copy->setLeftChild(deepCopy(root->getLeftChild()));
        copy->setRightChild(deepCopy(root->getRightChild()));


        copy->getBookData()->setName(root->getBookData()->getName());
        copy->getBookData()->setCode(root->getBookData()->getCode());
        copy->getBookData()->setAuthor(root->getBookData()->getAuthor());
        copy->getBookData()->setYear(root->getBookData()->getYear());

        return copy;
    }

    LoanBookData* getBookData() { return pData; }
    SelectionTreeNode* getLeftChild() { return pLeft; }
    SelectionTreeNode* getRightChild() { return pRight; }
    SelectionTreeNode* getParent() { return pParent; }
    LoanBookHeap* getHeap() { return hRoot; }
};

class SelectionTree
{
private:
    SelectionTreeNode* root;
    vector<SelectionTreeNode*> selvector;
    //vector<int> savedCode;
    ofstream* fout;
    int enteredRun;

public:
    SelectionTree() {
        this->root = NULL;
        this->fout = NULL;
        enteredRun = 7;
    }
    SelectionTree(ofstream* fout) {
        this->root = NULL;
        this->fout = fout;
        enteredRun = 7;
    }
    ~SelectionTree() {

    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    void settingSelection();
    void SelectionUp();

    bool Insert(LoanBookData* newData);
    bool Delete();
    void LevelOrderPrint();
    void vectorPrint();
    //bool printBookData(int bookCode);
};