#include "header.h"

int main() {
    SelectionTree sel;
    sel.settingSelection();
    // Create and insert book data into the heap
    LoanBookData book1;
    book1.setBookData("Q", 000, "Author 1", 2023);
    sel.Insert(&book1);

    LoanBookData book2;
    book2.setBookData("F", 200, "Author 2", 2023);
    sel.Insert(&book2);

    LoanBookData book3;
    book3.setBookData("D", 300, "Author 3", 2023);
    sel.Insert(&book3);

    LoanBookData book4;
    book4.setBookData("C", 400, "Author 4", 2023);
    sel.Insert(&book4);

    LoanBookData book5;
    book5.setBookData("A", 500, "Author 5", 2023);
    sel.Insert(&book5);

    
    LoanBookData book6;
    book6.setBookData("T", 700, "Author 1", 2023);
    sel.Insert(&book6);

    LoanBookData book7;
    book7.setBookData("Z", 500, "Author 2", 2023);
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
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);

    sel.LevelOrderPrint();
    
    
    return 0;
}
