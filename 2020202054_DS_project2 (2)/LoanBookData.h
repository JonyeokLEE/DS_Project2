#pragma once
#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

class LoanBookData
{
private:
    string name;
    int code;
    string author;
    int year;
    int loan_count;

public:
    LoanBookData() { this->loan_count = 0; }
    ~LoanBookData() {};

    void setBookData(string name, int code, string author, int year, int loan_count) {
        this->name = name;
        this->code = code;
        this->author = author;
        this->year = year;
        this->loan_count = loan_count;
    } //function to set data at once

    void setName(string name) { this->name = name; }
    void setCode(int code) { this->code = code; }
    void setAuthor(string author) { this->author = author; }
    void setYear(int year) { this->year = year; }
    void setCount(int count) { this->loan_count = count; }
    //to set data

    void updateCount() { this->loan_count += 1; }
    //update loan_count
    void DeleteCount() { this->loan_count = -1; }
    //delete(set to -1) loan_count

    string getName() { return name; }
    int getCode() { return code; }
    string getAuthor() { return author; }
    int getYear() { return year; }
    int getLoanCount() { return loan_count; }
    //function to get data

    void PrintData(ofstream& write) //function to print data
    {
        write << getName() << "/";
        if (code == 0) write << "000/";
        else write << getCode() << "/";
        write << getAuthor() << "/" <<getYear()<<"/"<< getLoanCount() << endl;
    }
};