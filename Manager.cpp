#include "Manager.h"

Manager::Manager()
{
    flog.open("log.txt", ios::app);
    bptree = new BpTree(&flog);
    stree = new SelectionTree(&flog);
    stree->settingSelection();
}

Manager::Manager(int bpOrder)
{
    flog.open("log.txt", ios::app);
    bptree = new BpTree(&flog);
    stree = new SelectionTree(&flog);
    stree->settingSelection();
}

Manager::~Manager()
{
    delete bptree;
    delete stree;
}

void Manager::run(const char* command)
{
	fin.open(command);
	if(!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
    string cmd;
    //bool stop = false;
    while (!fin.eof()) //if stop == true -> EXIT
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
        else if (cmd.substr(0, 9) == ("SEARCH_BP")) //QPOP command
        {
            bool success = SEARCH_BP(cmd.substr(10));
        }
        else if (cmd == ("PRINT_BP")) //SEARCH Command
        {
            bool success = PRINT_BP();
        }
        else if (cmd.substr(0, 8) == ("PRINT_ST")) //PRINT command
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
    return;
}

bool Manager::LOAD()
{
    ifstream readdata; //To read "data.txt"
    readdata.open("loan_book3.txt");
    if (!readdata)
    {
        return false;
    }
    bool success = false;
    string line;
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
        int loan_count = stoi(result[4]);

        LoanBookData* newone = new LoanBookData();
        newone->setBookData(name, code, author, year, loan_count);
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

bool Manager::ADD(string command)
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

    if (result.size() != 4) //if number of value is not 5
    {
        return false;
    }


    string name = result[0];
    int code = stoi(result[1]);
    string author = result[2];
    int year = stoi(result[3]);
    int count = 0;
    LoanBookData* newone = new LoanBookData();
    newone->setBookData(name, code, author, year, count);
    success = bptree->Insert(newone);
    BpTreeNode* AfterInsert = bptree->searchDataNode(name);
    count = AfterInsert->getDataMap()->find(name)->second->getLoanCount();
    newone->setCount(count);
    if (code == 0 || code == 100 || code == 200)
    {
        if (AfterInsert->getDataMap()->find(name)->second->getLoanCount() >= 3)
        {
            success = bptree->deleteBook(name);
            success = stree->Insert(newone);
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
    if (success)
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

bool Manager::SEARCH_BP(string ToSearch)
{
    string line = ToSearch;
    bool success = false;
    int SpaceCount = 0;
    SpaceCount = count(line.begin(), line.end(), '\t');
    if (SpaceCount == 0)
    {
        success = SEARCH_BP_BOOK(ToSearch);
    }
    else if (SpaceCount == 1)
    {
        vector<string> result; //to store the values into vector array
        stringstream ss(line);
        string temp;
        while (getline(ss, temp, '\t'))
        {
            result.push_back(temp);
        }
        if (result.size() != 2) //if number of value is not 2
        {
            return false;
        }
        string start = result[0];
        string end = result[1];
        success = SEARCH_BP_RANGE(start, end);
    }
    else
        return false;
    if (success)
        return true;
    else return false;
}

bool Manager::SEARCH_BP_BOOK(string book) 
{
    if (bptree->searchBook(book))
        return true;
    else
        return false;
}

bool Manager::SEARCH_BP_RANGE(string start, string end) 
{
    if (bptree->searchRange(start, end))
        return true;
    else
        return false;
}

bool Manager::PRINT_BP() 
{
    if (bptree->printAll())
        return true;
    else
        return false;
}

bool Manager::PRINT_ST(int CodeToFind) 
{
    int tofind = CodeToFind;
    if (tofind < 0 || tofind>700)
    {
        return false;
    }
    if (stree->printBookData(CodeToFind))
        return true;
    else
        return false;
}

bool Manager::DELETE() 
{
    if (stree->Delete())
        return true;
    else
        return false;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
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

