#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
    LoanBookHeapNode* parent = pN->getParent();

    while (parent != NULL && parent->getBookData()->getName() > pN->getBookData()->getName())
    {
        // �θ� ���� ���ο� ����� ���� �����͸� �ٲߴϴ�.
        LoanBookData* temp = parent->getBookData();
        parent->setBookData(pN->getBookData());
        pN->setBookData(temp);

        // ���ο� ��带 �θ� ���� �����ϰ�, �θ� ��带 �����մϴ�.
        pN = parent;
        parent = pN->getParent();
    }
}


void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
    while (pN != NULL) {
        LoanBookHeapNode* leftChild = pN->getLeftChild();
        LoanBookHeapNode* rightChild = pN->getRightChild();

        // ���� �ڽ� ���� ������ �ڽ� ��� �߿��� �� ���� ��带 ã���ϴ�.
        LoanBookHeapNode* smallerChild = NULL;
        if (leftChild != NULL && rightChild != NULL) {
            smallerChild = (leftChild->getBookData()->getName() < rightChild->getBookData()->getName()) ? leftChild : rightChild;
        }
        else if (leftChild != NULL) {
            smallerChild = leftChild;
        }
        else if (rightChild != NULL) {
            smallerChild = rightChild;
        }

        // �θ� ��尡 �ڽ� ��庸�� ū ���, �θ� ���� �ڽ� ����� ��ġ�� �ٲߴϴ�.
        if (smallerChild != NULL && pN->getBookData()->getName() > smallerChild->getBookData()->getName()) {
            LoanBookData* temp = pN->getBookData();
            pN->setBookData(smallerChild->getBookData());
            smallerChild->setBookData(temp);

            // ��ġ�� �ٲ� �Ŀ��� ���� �Ӽ��� �����ϱ� ���� heapifyDown �޼ҵ带 ��������� ȣ���մϴ�.
            pN = smallerChild;
        }
        else {
            // �θ� ��尡 �ڽ� ��庸�� �۰ų� ���� ���, ���� �Ӽ��� �����ǹǷ� �ݺ����� �����մϴ�.
            break;
        }
    }
}

bool LoanBookHeap::Insert(LoanBookData* data) {
    
    LoanBookHeapNode* newone = new LoanBookHeapNode();
    newone->setBookData(data);

    if (!root)
        root = newone;
    else {
        // ���� �Ʒ� ������ ���� ������ ��带 ã�ƾ� �մϴ�.
        // ���� ���� ������ �����ϱ� ���� ���� ��ġ�� ã�ƾ� �մϴ�.
        // ���� ������ ǥ���ϴ� ������ ����� �� �ֽ��ϴ�.

        int levelOrder = 1; // ���� ������ ��Ÿ���� ���� (��Ʈ�� 1�� ����)

        // ��Ʈ���� �����Ͽ� ���� �Ʒ� ������ ���� ������ ��带 ã���ϴ�.
        LoanBookHeapNode* currentNode = root;
        while (currentNode->getLeftChild() != NULL && currentNode->getRightChild() != NULL) {
            levelOrder++;
            // ���� ������ ���� �̵�
            if (levelOrder % 2 == 1) { // Ȧ�� ������ ��, �������� �̵�
                currentNode = currentNode->getLeftChild();
            }
            else { // ¦�� ������ ��, ���������� �̵�
                currentNode = currentNode->getRightChild();
            }
        }

        // �� ��带 ã�� ��ġ�� �߰�
        if (levelOrder % 2 == 1) { // Ȧ�� ������ ��, ���� �ڽ����� �߰�
            currentNode->setLeftChild(newone);
            newone->setParent(currentNode);
        }
        else { // ¦�� ������ ��, ������ �ڽ����� �߰�
            currentNode->setRightChild(newone);
            newone->setParent(currentNode);
        }

        // 3. ���Ե� ��带 ���� ������ ��ġ�� ������
        heapifyUp(newone);
    }

    return true; // ���� ����
}