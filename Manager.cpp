#include "Manager.h"

Manager::Manager()
{

}

Manager::Manager(int bpOrder)
{

}

Manager::~Manager()
{

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
            bool success = ADD();
            if (success) //if success LOAD
            {
                printSuccessCode("ADD");
            }
            else
            {
                printErrorCode(200);
            }
        }
        else if (cmd.substr(0, 9) == ("SEARCH_BP")) //QPOP command
        {
            bool success = SEARCH_BP(cmd.substr(10));
            if (success) //if success LOAD
            {
                printSuccessCode("SEARCH_BP");
            }
            else
            {
                printErrorCode(300);
            }
        }
        else if (cmd == ("PRINT_BP")) //SEARCH Command
        {
            bool success = PRINT_BP();
            if (success) //if success LOAD
            {
                printSuccessCode("PRINT_BP");
            }
            else
            {
                printErrorCode(400);
            }
        }
        else if (cmd.substr(0, 8) == ("PRINT_ST")) //PRINT command
        {
            int CodeToFind = stoi(cmd.substr(9));
            bool success = PRINT_ST(CodeToFind);
            if (success) //if success LOAD
            {
                printSuccessCode("PRINT_ST");
            }
            else
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
    readdata.open("loan_book.txt");
    if (!readdata)
    {
        return false;
    }

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
        newone->setBookData(name, code, author, year);
        bptree.Insert(newone);
    }
    readdata.close(); //close the file
    return true; //Success Load
}

bool Manager::ADD()
{
    string line;
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
    newone->setBookData(name, code, author, year);
    bptree.Insert(newone);
	return true;
}

bool Manager::SEARCH_BP(string ToSearch)
{
    string line = ToSearch;
    int SpaceCount = 0;
    SpaceCount = count(line.begin(), line.end(), ' ');
    if (SpaceCount == 0)
    {
        bptree.searchBook(ToSearch);
        return true;
    }
    else if (SpaceCount == 1)
    {
        vector<string> result; //to store the values into vector array
        stringstream ss(line);
        string temp;
        while (getline(ss, temp, ' ')) // 탭 또는 개행 문자를 파싱 기준으로 사용
        {
            result.push_back(temp);
        }
        if (result.size() != 2) //if number of value is not 5
        {
            return false;
        }
        string start = result[0];
        string end = result[1];
        bptree.searchRange(start, end);
    }
    else
        return false;
}

bool Manager::SEARCH_BP_BOOK(string book) 
{
    if (bptree.searchBook(book))
        return true;
    else
        return false;
}

bool Manager::SEARCH_BP_RANGE(string start, string end) 
{
    if (bptree.searchRange(start, end))
        return true;
    else
        return false;
}

bool Manager::PRINT_BP() 
{
	
}

bool Manager::PRINT_ST(int CodeToFind) 
{
    int tofind = CodeToFind;
    if (stree.printBookData(CodeToFind))
        return true;
    else
        return false;
}

bool Manager::DELETE() 
{

}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "=======================" << endl;
	flog << "ERROR " << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode(const char* cmd) //Print Success
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}

