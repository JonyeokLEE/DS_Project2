#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
    LoanBookHeapNode* parent = pN->getParent();

    while (parent != NULL && parent->getBookData()->getName() > pN->getBookData()->getName())
    {
        // 부모 노드와 새로운 노드의 도서 데이터를 바꿉니다.
        LoanBookData* temp = parent->getBookData();
        parent->setBookData(pN->getBookData());
        pN->setBookData(temp);

        // 새로운 노드를 부모 노드로 설정하고, 부모 노드를 갱신합니다.
        pN = parent;
        parent = pN->getParent();
    }
}


void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
    while (pN != NULL) {
        LoanBookHeapNode* leftChild = pN->getLeftChild();
        LoanBookHeapNode* rightChild = pN->getRightChild();

        // 왼쪽 자식 노드와 오른쪽 자식 노드 중에서 더 작은 노드를 찾습니다.
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

        // 부모 노드가 자식 노드보다 큰 경우, 부모 노드와 자식 노드의 위치를 바꿉니다.
        if (smallerChild != NULL && pN->getBookData()->getName() > smallerChild->getBookData()->getName()) {
            LoanBookData* temp = pN->getBookData();
            pN->setBookData(smallerChild->getBookData());
            smallerChild->setBookData(temp);

            // 위치가 바뀐 후에도 힙의 속성을 유지하기 위해 heapifyDown 메소드를 재귀적으로 호출합니다.
            pN = smallerChild;
        }
        else {
            // 부모 노드가 자식 노드보다 작거나 같은 경우, 힙의 속성이 유지되므로 반복문을 종료합니다.
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
        // 가장 아래 레벨의 가장 오른쪽 노드를 찾아야 합니다.
        // 힙의 레벨 순서를 유지하기 위해 삽입 위치를 찾아야 합니다.
        // 레벨 순서를 표현하는 변수를 사용할 수 있습니다.

        int levelOrder = 1; // 레벨 순서를 나타내는 변수 (루트는 1로 시작)

        // 루트부터 시작하여 가장 아래 레벨의 가장 오른쪽 노드를 찾습니다.
        LoanBookHeapNode* currentNode = root;
        while (currentNode->getLeftChild() != NULL && currentNode->getRightChild() != NULL) {
            levelOrder++;
            // 다음 레벨의 노드로 이동
            if (levelOrder % 2 == 1) { // 홀수 레벨일 때, 왼쪽으로 이동
                currentNode = currentNode->getLeftChild();
            }
            else { // 짝수 레벨일 때, 오른쪽으로 이동
                currentNode = currentNode->getRightChild();
            }
        }

        // 새 노드를 찾은 위치에 추가
        if (levelOrder % 2 == 1) { // 홀수 레벨일 때, 왼쪽 자식으로 추가
            currentNode->setLeftChild(newone);
            newone->setParent(currentNode);
        }
        else { // 짝수 레벨일 때, 오른쪽 자식으로 추가
            currentNode->setRightChild(newone);
            newone->setParent(currentNode);
        }

        // 3. 삽입된 노드를 힙의 적절한 위치로 재정렬
        heapifyUp(newone);
    }

    return true; // 삽입 성공
}