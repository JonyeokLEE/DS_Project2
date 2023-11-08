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
    if (!root)
        return;
    root->setBookData(pN->getBookData());

    if (pN->getParent())
    {
        if (pN->getParent()->getLeftChild() == pN)
        {
            pN->getParent()->setLeftChild(nullptr);
            pN->setParent(nullptr);
            LevelOrder.erase(LevelOrder.end() - 1);
        }
        else if (pN->getParent()->getRightChild() == pN)
        {
            pN->getParent()->setRightChild(nullptr);
            pN->setParent(nullptr);
            LevelOrder.erase(LevelOrder.end() - 1);
        }
    }
    else
    {
        LevelOrder.erase(LevelOrder.end() - 1);
        root = nullptr;
        return;
    }

    LoanBookHeapNode* curr = root;



    int size = 1;
    while (curr && size <= LevelOrder.size())
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

            curr = child;
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

bool LoanBookHeap::SortandPrint(ofstream& write)
{
    return false;
}

/*
bool LoanBookHeap::SortandPrint(ofstream& write)
{
    vector<LoanBookHeapNode*> sorted;
    for (int i = 1; i < LevelOrder.size(); i++)
    {
        sorted.push_back(LevelOrder.at(i));
    }
    sort(sorted.begin(), sorted.end(), [](LoanBookHeapNode* a, LoanBookHeapNode* b) {
        return a->getBookData()->getName() < b->getBookData()->getName();
        });
    for (int i = 0; i < sorted.size(); i++)
    {
        sorted.at(i)->getBookData()->PrintData(write);
    }
}
*/

/*
void LoanBookHeap::LevelOrderPrint()
{
    if (!root)
    {
        cout << "Heap is Empty" << endl;
        return;
    }
    queue <LoanBookHeapNode*> q;
    LoanBookHeapNode* curr = root;
    cout << "Heap: ";
    while (curr)
    {
        cout << curr->getBookData()->getName() << " ";
        if (curr->getLeftChild())
            q.push(curr->getLeftChild());
        if (curr->getRightChild())
            q.push(curr->getRightChild());
        if (q.empty()) return;

        curr = q.front();
        q.pop();
    }
}
void LoanBookHeap::vectorPrint()
{
    if (LevelOrder.empty())
    {
        cout << "Vector is Empty" << endl;
        return;
    }
    cout << "Vector: ";
    for (int i = 1; i < LevelOrder.size(); i++)
    {
        cout << LevelOrder.at(i)->getBookData()->getName() << " ";
    }
}


void LoanBookHeap::SortAndPrint(int BookCode)
{
    if (!root)
    {
        cout << "Vector is Empty" << endl;
        return;
    }
    vector<LoanBookHeapNode*> sorted;
    for (int i = 1; i < LevelOrder.size(); i++)
    {
        sorted.push_back(LevelOrder.at(i));
    }
    sort(sorted.begin(), sorted.end(), [](LoanBookHeapNode* a, LoanBookHeapNode* b) {
        return a->getBookData()->getName() < b->getBookData()->getName();
        });
    cout << "Sorted: ";
    for (int i = 0; i < sorted.size(); i++)
    {
        cout << sorted.at(i)->getBookData()->getName() << " ";
    }
}
*/