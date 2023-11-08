#include "SelectionTree.h"

void SelectionTree::settingSelection()
{
    selvector.push_back(nullptr);
    for (int i = 1; i < 16; i++)
    {
        SelectionTreeNode* newNode = new SelectionTreeNode();
        selvector.push_back(newNode);

    }
    int count = 1;
    root = selvector.at(1);
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
        if (count > 7)
        {
            LoanBookHeap* newHeap = new LoanBookHeap();
            selvector.at(count)->setHeap(newHeap);
        }
        count++;
    }
}

void SelectionTree::SelectionUp()
{
    int level = 7;
    while (level > 0)
    {
        SelectionTreeNode* curr = selvector.at(level);
        SelectionTreeNode* left = selvector.at(2 * level);
        SelectionTreeNode* right = selvector.at(2 * level + 1);

        LoanBookData* copied = new LoanBookData();
        if (!left->getBookData() && !right->getBookData())
        {
            copied = nullptr;
            curr->setBookData(copied);
        }
        else if (!left->getBookData() && right->getBookData())
        {
            copied = right->getBookData();
            curr->setBookData(copied);
        }
        else if (!right->getBookData() && left->getBookData())
        {
            copied = left->getBookData();
            curr->setBookData(copied);
        }
        else
        {
            if (right->getBookData()->getName() < left->getBookData()->getName())
            {
                copied = right->getBookData();
                curr->setBookData(copied);
            }
            else
            {
                copied = left->getBookData();
                curr->setBookData(copied);
            }
        }

        curr->setBookData(copied);
        level--;
    }
}

bool SelectionTree::Insert(LoanBookData* newData) {

    //Run 새로 들어오면 연결시켜주고 관리
    int code = newData->getCode();
    bool entered = false;
    int location = newData->getCode() / 100 + 8;
    SelectionTreeNode* newone = selvector.at(location);

    newone->getHeap()->Insert(newData);
    newone->setBookData(selvector.at(location)->getHeap()->getRoot()->getBookData());
    SelectionUp();
    return true;
}


bool SelectionTree::Delete() {
    if (!root)
        return false;
    else
    {
        int location = root->getBookData()->getCode() / 100 + 8;
        selvector.at(location)->getHeap()->heapifyDown(selvector.at(location)->getHeap()->getLastNode());
        if (!selvector.at(location)->getHeap()->getRoot())
        {
            selvector.at(location)->setBookData(nullptr);
        }
        else
        {
            selvector.at(location)->setBookData(selvector.at(location)->getHeap()->getRoot()->getBookData());
        }

        SelectionUp();
        return true;
    }
}
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
/*
void SelectionTree::LevelOrderPrint()
{
    if (!root)
    {
        cout << "Heap is Empty" << endl;
        return;
    }
    queue <SelectionTreeNode*> qq;
    SelectionTreeNode* curr = root;
    cout << endl << "Selection: ";
    while (curr)
    {
        if (!curr->getBookData())
            cout << "- ";
        else
        {
            cout << curr->getBookData()->getName() << " ";
        }
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
    cout << endl << "Vector:    ";
    for (int i = 1; i < selvector.size(); i++)
    {
        if (!selvector.at(i)->getBookData())
            cout << "- ";
        else
        {
            cout << selvector.at(i)->getBookData()->getName() << " ";
        }

    }cout << endl << endl << endl;
}
void SelectionTree::vectorPrintEach(int code)
{
    bool entered = false;
    int location;
    for (int i = 8; i < 16; i++)
    {
        if (selvector.at(i)->getBookData() && code == selvector.at(i)->getHeap()->getRoot()->getBookData()->getCode())
        {
            entered = true;
            location = i;
        }
    }
    if (entered)
    {
        cout << "Code " << code << ": ";
        selvector.at(location)->getHeap()->LevelOrderPrint();
        cout << endl;
    }
    else
    {
        cout << "No Entered\n";
    }
}
*/


