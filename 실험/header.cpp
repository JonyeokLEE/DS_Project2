#include "header.h"

void SelectionTree::settingSelection()
{
    selvector.push_back(nullptr);
    for (int i = 1; i < 16; i++)
    {
        SelectionTreeNode* newNode = new SelectionTreeNode();
        selvector.push_back(newNode);
        
    }
    int count = 1;
    while (count < 16)
    {
        if (count < 8)
        {
            selvector.at(count)->setLeftChild(selvector.at(2 * count));
            selvector.at(count)->setRightChild(selvector.at(2 * count + 1));
        }
        if (count > 1)
        {
            selvector.at(count)->setParent(selvector.at(count / 2));
        }
        count++;
    }
}

void SelectionTree::SelectionUp()
{
    for (int i = 7; i > 0; i--)
    {
        int j = 2 * i;
        if(!selvector.at(j)&&!selvector.at(j+1))
        {
            selvector.at(i) = nullptr;
        }
        else if (!selvector.at(j) && selvector.at(j + 1))
        {
            selvector.at(i)->setBookData(selvector.at(j + 1)->getBookData());
        }
        else if (selvector.at(j) && !selvector.at(j + 1))
        {
            selvector.at(i)->setBookData(selvector.at(j)->getBookData());
        }
        else if (selvector.at(j)->getBookData()->getName() < selvector.at(j + 1)->getBookData()->getName())
        {
            selvector.at(i)->setBookData(selvector.at(j + 1)->getBookData());
        }
        else
            selvector.at(i)->setBookData(selvector.at(j)->getBookData());
    }
}



bool SelectionTree::Insert(LoanBookData* newData) {

    //Run 새로 들어오면 연결시켜주고 관리
    int code = newData->getCode();
    bool entered = false;
    int location;
    for (int i = 8; i < 16; i++)
    {
        if (selvector.at(i)->getHeap() == nullptr)
            break;
        if (code == selvector.at(i)->getHeap()->getRoot()->getBookData()->getCode())
        {
            entered = true;
            location = i;
        }
    }
    if (entered)
    {
        selvector.at(location)->getHeap()->Insert(newData);
    }
    else
    {
        enteredRun++;
        LoanBookHeap* newHeap = new LoanBookHeap();
        selvector.at(enteredRun)->setHeap(newHeap);
        newHeap->Insert(newData);
    }
    SelectionUp();
    return true;
}


bool SelectionTree::Delete() {
    if (!root)
        return false;

    else
    {
        int location = 0;
        for (int i = 8; i < 16; i++)
        {
            if (root->getBookData()->getName() == selvector.at(i)->getBookData()->getName())
            {
                location = i;
                break;
            }
        }
        selvector.at(location)->getHeap()->heapifyDown(selvector.at(location)->getHeap()->getRoot());
        SelectionUp();
        return true;
    }
}
void SelectionTree::LevelOrderPrint()
{
    if (!root)
    {
        cout << "Heap is Empty" << endl;
        return;
    }
    queue <SelectionTreeNode*> qq;
    SelectionTreeNode* curr = root;
    cout << "Selection: ";
    while (curr)
    {
        cout << curr->getBookData()->getName() << " ";
        if (curr->getLeftChild())
            qq.push(curr->getLeftChild());
        if (curr->getRightChild())
            qq.push(curr->getRightChild());
        if (qq.empty()) return;

        curr = qq.front();
        qq.pop();
    }
}
void SelectionTree::vectorPrint()
{
    if (selvector.empty())
    {
        cout << "Vector is Empty" << endl;
        return;
    }
    cout << "Vector: ";
    for (int i = 1; i < selvector.size(); i++)
    {
        cout << selvector.at(i)->getBookData()->getName() << " ";
    }
}
/*
bool SelectionTree::printBookData(int bookCode) {

    if (bookCode < 100 || bookCode >700 || bookCode % 100 != 0)
        return false;

    else
    {
        int location = 0;
        for (int i = 8; i < 16; i++)
        {
            if (root->getBookData()->getName() == selvector.at(i)->getBookData()->getName())
            {
                location = i;
                break;
            }
        }


        if (selvector.at(location)->getHeap()->getRoot() == nullptr)
            return false;
        if (!selvector.at(location)->getHeap()->SortandPrint(*fout))
            return false;
        else return true;
    }
}
*/

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

