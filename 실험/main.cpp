#include "header.h"
using namespace std;
int main() {
    int command = 1;
   // cin >> command;
    if(command==1){
    SelectionTree sel;
    sel.settingSelection();
    // Create and insert book data into the heap
    LoanBookData book1;
    book1.setBookData("Q", 200, "Author 1", 2023);
    sel.Insert(&book1);

    LoanBookData book2;
    book2.setBookData("F", 500, "Author 2", 2023);
    sel.Insert(&book2);

    LoanBookData book3;
    book3.setBookData("D", 300, "Author 3", 2023);
    sel.Insert(&book3);

    LoanBookData book4;
    book4.setBookData("C", 200, "Author 4", 2023);
    sel.Insert(&book4);

    LoanBookData book5;
    book5.setBookData("A", 700, "Author 5", 2023);
    sel.Insert(&book5);

    
    LoanBookData book6;
    book6.setBookData("T", 200, "Author 1", 2023);
    sel.Insert(&book6);

    LoanBookData book7;
    book7.setBookData("Z", 100, "Author 2", 2023);
    sel.Insert(&book7);

    LoanBookData book8;
    book8.setBookData("P", 200, "Author 3", 2023);
    sel.Insert(&book8);

    LoanBookData book9;
    book9.setBookData("O", 200, "Author 4", 2023);
    sel.Insert(&book9);
    
    LoanBookData book10;
    book10.setBookData("I", 300, "Author 5", 2023);
    sel.Insert(&book10);
    LoanBookData book11;
    book11.setBookData("B", 200, "Author 5", 2023);
    sel.Insert(&book11);

    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();


    sel.Delete();
    sel.vectorPrintEach(000);
    sel.vectorPrintEach(100);
    sel.vectorPrintEach(200);
    sel.vectorPrintEach(300);
    sel.vectorPrintEach(400);
    sel.vectorPrintEach(500);
    sel.vectorPrintEach(600);
    sel.vectorPrintEach(700);
    sel.LevelOrderPrint();
    sel.vectorPrint();

    }
    if (command == 2)
    {
        LoanBookHeap heap;

        // Create and insert book data into the heap
        LoanBookData book1;
        book1.setBookData("Q", 100, "Author 1", 2023);
        heap.Insert(&book1);

        LoanBookData book2;
        book2.setBookData("F", 100, "Author 2", 2023);
        heap.Insert(&book2);

        LoanBookData book3;
        book3.setBookData("D", 100, "Author 3", 2023);
        heap.Insert(&book3);

        LoanBookData book4;
        book4.setBookData("C", 100, "Author 4", 2023);
        heap.Insert(&book4);

        LoanBookData book5;
        book5.setBookData("A", 100, "Author 5", 2023);
        heap.Insert(&book5);


        LoanBookData book6;
        book6.setBookData("Z", 100, "Author 1", 2023);
        heap.Insert(&book6);

        LoanBookData book7;
        book7.setBookData("T", 100, "Author 2", 2023);
        heap.Insert(&book7);

        LoanBookData book8;
        book8.setBookData("P", 100, "Author 3", 2023);
        heap.Insert(&book8);

        LoanBookData book9;
        book9.setBookData("O", 100, "Author 4", 2023);
        heap.Insert(&book9);

        LoanBookData book10;
        book10.setBookData("I", 100, "Author 5", 2023);
        heap.Insert(&book10);
        LoanBookData book11;
        book11.setBookData("B", 100, "Author 5", 2023);
        heap.Insert(&book11);

        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;

        heap.heapifyDown(heap.getLastNode());
        cout << endl;
        heap.LevelOrderPrint();
        cout << endl;
        heap.vectorPrint();
        cout << endl;
        heap.SortAndPrint(100);
        cout << endl;
    }
    
    
    return 0;
}
