#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
    // 1. ���ο� ��� ����
    SelectionTreeNode* newNode = new SelectionTreeNode();
    newNode->setBookData(newData);

    // 2. ��Ʈ�� ���� ��� ���ο� ��带 ��Ʈ�� ����
    if (root == NULL) {
        root = newNode;
    }
    else {
        SelectionTreeNode* currentNode = root;
        while (currentNode != NULL) {
            // ��ҹ��ڸ� �������� �ʴ� ������ ��
            string newName = newData->getName();
            string currentNodeName = currentNode->getBookData()->getName();

            // ���ο� �������� ���� ����� �������� ���� ��� �������� �̵�
            if (newName < currentNodeName) {
                if (currentNode->getLeftChild() == NULL) {
                    currentNode->setLeftChild(newNode);
                    newNode->setParent(currentNode);
                    break;
                }
                currentNode = currentNode->getLeftChild();
            }
            // ���ο� �������� ���� ����� �������� ũ�ų� ���� ��� ���������� �̵�
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

    // 3. ���ο� ������ �߰��� �� Min Winner Tree�� �����ϱ� ���� �ʿ��� �۾� ����
    // Heap�� ������Ʈ�ϰ� Min Winner Tree�� ������Ʈ�ؾ� �մϴ�.

    return true; // ���� ����
}


bool SelectionTree::Delete() {

}

bool SelectionTree::printBookData(int bookCode) {
    // ���� �ڵ忡 �ش��ϴ� ��带 ã���ϴ�.
    // �� ���ÿ����� Ʈ���� ��ȸ�ϴ� ����� ����մϴ�.
    // TODO: ���� �ڵ忡 �ش��ϴ� ��带 ã�� �ڵ带 �ۼ��ϼ���.

    // ���� �ڵ忡 �ش��ϴ� ��尡 �����ϴ� ���, �ش� ����� ���� �����͸� ����մϴ�.
    if (node != NULL) {
        LoanBookData* data = node->getBookData();
        // TODO: ���� �����͸� ����ϴ� �ڵ带 �ۼ��ϼ���.
    }
    else {
        // ���� �ڵ忡 �ش��ϴ� ��尡 �������� �ʴ� ���, ���� �޽����� ����մϴ�.
        std::cout << "Error: Book with code " << bookCode << " not found." << std::endl;
    }

    return true;
}
