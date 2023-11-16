#include "Manager.h"

Manager::Manager()
{
    flog.open("log.txt", ios::app); //open "log.txt" to write in succession
    bptree = new BpTree(&flog);
    stree = new SelectionTree(&flog);
    stree->settingSelection(); //setting Selection Tree
}

Manager::Manager(int bpOrder)
{
    flog.open("log.txt", ios::app); //open "log.txt" to write in succession
    bptree = new BpTree(&flog);
    stree = new SelectionTree(&flog);
    stree->settingSelection(); //setting Selection Tree
}

Manager::~Manager()
{
    delete bptree;
    delete stree; //delete Pointer
}

void Manager::run(const char* command)
{
	fin.open(command); //open Command File
	if(!fin) //if fail to open
	{
        printErrorCode(100);
		return;
	}
    string cmd;

    while (!fin.eof()) //Untill the end of File
    {
        getline(fin, cmd); //get a line of command file
        if (cmd == ("LOAD")) //LOAD Command
        {
            bool success = LOAD();
            if (success) //if success LOAD
            {
                printSuccessCode("LOAD");
            }
            else
            {
                printErrorCode(100);
            }
        }
        else if (cmd.substr(0, 3) == ("ADD")) //ADD command
        {
            bool success = ADD(cmd.substr(4));
            if (!success) //if success LOAD
            {
                printErrorCode(200);
            }
        }
        else if (cmd.substr(0, 9) == ("SEARCH_BP")) //SEARCH_BP command
        {
            bool success = SEARCH_BP(cmd.substr(10));
        }
        else if (cmd == ("PRINT_BP")) //PRINT_BP Command
        {
            bool success = PRINT_BP();
        }
        else if (cmd.substr(0, 8) == ("PRINT_ST")) //PRINT_ST command
        {
            int CodeToFind = stoi(cmd.substr(9));
            bool success = PRINT_ST(CodeToFind);
            if (!success)
            {
                printErrorCode(500);
            }
        }
        else if (cmd == ("DELETE")) //DELETE command
        {
            bool success = DELETE();
            if (success) //if success LOAD
            {
                printSuccessCode("DELETE");
            }
            else
            {
                printErrorCode(600);
            }
        }
        else if (cmd == ("EXIT")) //EXIT command
        {
            printSuccessCode("EXIT");
            break;
        }
        else //Wrong command
        {
            printErrorCode(700);
        }
    }
    fin.close();
    flog.close(); //Close FIles
    return; //finish
}

bool Manager::LOAD() //LOAD command
{
    ifstream readdata; //To read "loan_book.txt"
    readdata.open("loan_book.txt");
    if (!readdata)
    {
        return false;
    }
    bool success = false; //to know is LOAD Success?
    string line; //to read data
    while (getline(readdata, line))
    {
        vector<string> result; //to store the values into vector array
        stringstream ss(line);
        string temp;

        while (getline(ss, temp, '\t')) //seperate values on the basis of tab
        {
            result.push_back(temp);
        }

        if (result.size() != 5) //if number of value is not 5
        {
            return false;
        }

        string name = result[0];
        int code = stoi(result[1]);
        string author = result[2];
        int year = stoi(result[3]);
        int loan_count = stoi(result[4]); //store the value from command

        LoanBookData* newone = new LoanBookData();
        newone->setBookData(name, code, author, year, loan_count); //set Data

        //store the data with its code and count
        if (code == 0 || code == 100 || code == 200)
        {
            if (loan_count < 3)
            {
                success = bptree->Insert(newone);
            }
            else
            {
                success = stree->Insert(newone);
            }
        }
        else if (code == 300 || code == 400)
        {
            if (loan_count < 4)
            {
                success = bptree->Insert(newone);
            }
            else
            {
                success = stree->Insert(newone);
            }
        }
        else if (code == 500 || code == 600 || code == 700)
        {
            if (loan_count < 2)
            {
                success = bptree->Insert(newone);
            }
            else
            {
                success = stree->Insert(newone);
            }
        }
        else
        {
            return false;
        }
    }
    readdata.close(); //close the file
    if (success)
    {
        return true;
    }
    else
        return false;
}

bool Manager::ADD(string command) //ADD command
{
    string line = command;
    bool success = false;
    vector<string> result; //to store the values into vector array
    stringstream ss(line);
    string temp;

    while (getline(ss, temp, '\t')) //seperate values on the basis of tab
    {
        result.push_back(temp);
    }

    if (result.size() != 4) //if number of value is not 4
    {
        return false;
    }


    string name = result[0];
    int code = stoi(result[1]);
    string author = result[2];
    int year = stoi(result[3]);
    int count = 0;
    LoanBookData* newone = new LoanBookData();
    newone->setBookData(name, code, author, year, count); //store the value

    success = bptree->Insert(newone); //insert to BpTree
    BpTreeNode* AfterInsert = bptree->searchDataNode(name);
    count = AfterInsert->getDataMap()->find(name)->second->getLoanCount();
    newone->setCount(count); //get updated count

    //delete from Bptree and store to SelectionTree if its count is over
    if (code == 0 || code == 100 || code == 200)
    {
        if (AfterInsert->getDataMap()->find(name)->second->getLoanCount() >= 3)
        {
            success = bptree->deleteBook(name); //delete data from bptree
            success = stree->Insert(newone); //insert to stree
        }
    }
    else if (code == 300 || code == 400)
    {
        if (AfterInsert->getDataMap()->find(name)->second->getLoanCount() >= 4)
        {
            success = bptree->deleteBook(name);
            success = stree->Insert(newone);
        }
    }
    else if (code == 500 || code == 600 || code == 700)
    {
        if (AfterInsert->getDataMap()->find(name)->second->getLoanCount() >= 2)
        {
            success = bptree->deleteBook(name);
            success = stree->Insert(newone);
        }
    }
    else
    {
        return false;
    }
    if (success) //Print Success
    {
        flog << "========ADD========" << endl;
        flog << newone->getName() << "/";
        if (code == 0) flog << "000/";
        else flog << newone->getCode() << "/";
        flog << newone->getAuthor() << "/" << newone->getYear() << endl;
        flog << "====================" << endl << endl;
        return true;
    }
    else
        return false;
}

bool Manager::SEARCH_BP(string ToSearch) //SEARCH_BP command
{
    string line = ToSearch;
    bool success = false;
    vector<string> result; //to store the values into vector array
    stringstream ss(line);
    string temp;

    while (getline(ss, temp, '\t')) //seperate values on the basis of tab
    {
        result.push_back(temp);
    }

    if (result.size() > 3) //if number of value is not 3
    {
        return false;
    }
    if (result.size() == 1)
    {
        success = SEARCH_BP_BOOK(line); //run SEARCH_BP_BOOK
    }
    else if (result.size() == 2) //if there is two parameter in command
    {
        string start = result[0];
        string end = result[1];
        success = SEARCH_BP_RANGE(start, end); //run SEARCH_BP_RANGE
    }
    else
        return false;
    if (success)
        return true;
    else return false;
}

bool Manager::SEARCH_BP_BOOK(string book) 
{
    if (bptree->searchBook(book)) //if success
        return true;
    else
        return false;
}

bool Manager::SEARCH_BP_RANGE(string start, string end) 
{
    if (bptree->searchRange(start, end)) //if success
        return true;
    else
        return false;
}

bool Manager::PRINT_BP() //PRINT_BP command
{
    if (bptree->printAll()) //if success
        return true;
    else
        return false;
}

bool Manager::PRINT_ST(int CodeToFind) //PRINT_ST command
{
    int tofind = CodeToFind;
    if (tofind < 0 || tofind>700 || tofind%100!=0) //Wrong code is entered
    {
        return false;
    }
    if (stree->printBookData(CodeToFind))
        return true;
    else
        return false;
}

bool Manager::DELETE() //DELETE command
{   
    if (stree->Delete())
        return true;
    else
        return false;
}

void Manager::printErrorCode(int n) //ERROR CODE PRINT
{
	flog << "========ERROR========" << endl;
	flog << n << endl;
	flog << "=====================" << endl << endl;
}

void Manager::printSuccessCode(const char* cmd) //Print Success
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}

