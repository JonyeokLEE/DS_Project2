#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
    // 1. 새로운 노드 생성
    SelectionTreeNode* newNode = new SelectionTreeNode();
    newNode->setBookData(newData);

    // 2. 루트가 없는 경우 새로운 노드를 루트로 설정
    if (root == NULL) {
        root = newNode;
    }
    else {
        SelectionTreeNode* currentNode = root;
        while (currentNode != NULL) {
            // 대소문자를 구별하지 않는 도서명 비교
            string newName = newData->getName();
            string currentNodeName = currentNode->getBookData()->getName();

            // 새로운 도서명이 현재 노드의 도서명보다 작을 경우 왼쪽으로 이동
            if (newName < currentNodeName) {
                if (currentNode->getLeftChild() == NULL) {
                    currentNode->setLeftChild(newNode);
                    newNode->setParent(currentNode);
                    break;
                }
                currentNode = currentNode->getLeftChild();
            }
            // 새로운 도서명이 현재 노드의 도서명보다 크거나 같을 경우 오른쪽으로 이동
            else {
                if (currentNode->getRightChild() == NULL) {
                    currentNode->setRightChild(newNode);
                    newNode->setParent(currentNode);
                    break;
                }
                currentNode = currentNode->getRightChild();
            }
        }
    }

    // 3. 새로운 도서를 추가한 후 Min Winner Tree를 유지하기 위해 필요한 작업 수행
    // Heap을 업데이트하고 Min Winner Tree도 업데이트해야 합니다.

    return true; // 삽입 성공
}


bool SelectionTree::Delete() {

}

bool SelectionTree::printBookData(int bookCode) {
    // 도서 코드에 해당하는 노드를 찾습니다.
    // 이 예시에서는 트리를 순회하는 방식을 사용합니다.
    // TODO: 도서 코드에 해당하는 노드를 찾는 코드를 작성하세요.

    // 도서 코드에 해당하는 노드가 존재하는 경우, 해당 노드의 도서 데이터를 출력합니다.
    if (node != NULL) {
        LoanBookData* data = node->getBookData();
        // TODO: 도서 데이터를 출력하는 코드를 작성하세요.
    }
    else {
        // 도서 코드에 해당하는 노드가 존재하지 않는 경우, 오류 메시지를 출력합니다.
        std::cout << "Error: Book with code " << bookCode << " not found." << std::endl;
    }

    return true;
}
