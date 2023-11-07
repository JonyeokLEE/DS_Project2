#include "header.h"

int main() {
    LoanBookHeap heap;
    SelectionTree sel;
    sel.settingSelection();
    // Create and insert book data into the heap
    LoanBookData book1;
    book1.setBookData("Q", 100, "Author 1", 2023);
    sel.Insert(&book1);

    LoanBookData book2;
    book2.setBookData("F", 100, "Author 2", 2023);
    sel.Insert(&book2);

    LoanBookData book3;
    book3.setBookData("D", 200, "Author 3", 2023);
    sel.Insert(&book3);

    LoanBookData book4;
    book4.setBookData("C", 300, "Author 4", 2023);
    sel.Insert(&book4);

    LoanBookData book5;
    book5.setBookData("A", 400, "Author 5", 2023);
    sel.Insert(&book5);

    
    LoanBookData book6;
    book6.setBookData("Z", 400, "Author 1", 2023);
    sel.Insert(&book6);

    LoanBookData book7;
    book7.setBookData("T", 500, "Author 2", 2023);
    sel.Insert(&book7);

    LoanBookData book8;
    book8.setBookData("P", 100, "Author 3", 2023);
    sel.Insert(&book8);

    LoanBookData book9;
    book9.setBookData("O", 200, "Author 4", 2023);
    sel.Insert(&book9);
    
    LoanBookData book10;
    book10.setBookData("I", 100, "Author 5", 2023);
    sel.Insert(&book10);
    LoanBookData book11;
    book11.setBookData("B", 100, "Author 5", 2023);
    sel.Insert(&book11);

    //sel.LevelOrderPrint();
    sel.vectorPrint();
    
    
    return 0;
}
