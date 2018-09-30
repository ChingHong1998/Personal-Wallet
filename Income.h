#ifndef INCOME_H
#define INCOME_H
#include <string>
#include <iostream>
#include <fstream>
#include "Stack.h"
#include "funct.h"
using namespace std;

class Income:public funct
{
    public:
        Income();
        void display_category();
        void add_record(double amount, string detail, string category);
        string getID();
        void setID(string);
        string createID();
        void saveBack(vector <Income> vec);
        string getAmount() ;
        string getDate() ;
        string getDetail() ;
        string getCategory();
        void display();
        void remake(string,string,string);
        void setAmount(string);
        void setDetail(string);
        void setDate(string);
        void setCategory(string);
        vector <Income> returnIncomeVector();
        void merge(vector <Income>& theArray, int first, int mid, int last, int choice );
        void mergeSort(vector <Income> &theArray, int first, int last, int choice);
        int leftmost(vector <Income> array, int min, int max, int value);
        int rightmost(vector <Income> array, int min, int max, int value);
    protected:

    private:
        string ID;
        double amount;
        string detail;
        string date;
        string category;
};

#endif // INCOME_H
