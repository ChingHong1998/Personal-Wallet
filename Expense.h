#ifndef EXPENSE_H
#define EXPENSE_H
#include <iostream>
#include <string>
#include <fstream>
#include "funct.h"
#include "Stack.h"
#include <ctime>
using namespace std;
class Expense:public funct{
    public:
        Expense();
        void display_category();
        void add_record(double amount, string detail, string category);
        string getID();
        void setID(string);
        string createID();
        void display();
        string getAmount() ;
        string getDate() ;
        string getDetail() ;
        string getCategory();
        void remake(string,string,string);
        void setAmount(string);
        void setDetail(string);
        void setDate(string);
        void setCategory(string);
        void saveBack(vector <Expense> vec);
        vector <Expense> returnExpensesVector();
        void merge(vector <Expense>& theArray, int first, int mid, int last, int choice );
        void mergeSort(vector <Expense> &theArray, int first, int last, int choice);
        int leftmost(vector <Expense> array, int min, int max, int value);
        int rightmost(vector <Expense> array, int min, int max, int value);
    protected:

    private:
        string ID;
        double amount;
        string detail;
        string date;
        string category;
};

#endif // EXPENSE_H
