#ifndef WALLET_H
#define WALLET_H
#include <iostream>
#include <vector>
#include <iomanip>
#include "funct.h"
#include "funct.h"
#include "Expense.h"
#include "Income.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;
class Wallet:public funct{
    public:
        Wallet();
        Wallet(string name, double bal,double bud,string cur);
        double getBudget();
        string displayUsername();
        string getCurrency();
        double displayBalance();
        void warning();
        void addExpense();
        void addIncome();
        bool isEnough(double amount);
        void update_data();
        void editExpense(string Date, ifstream &filen1);
        void editIncome(string Date, ifstream &filen1);
        void display_record(ifstream &filen1,string choose2);
        void deleteExpense(string Date,ifstream &fin);
        void deleteIncome(string Date,ifstream &fin);
        void displayAll(ifstream &fin);
        void display_record(ifstream &filen1);
        void sort_expense_amount(int sort_choice);
        void sort_expense_date(int sort_choice);
        void sort_income_amount(int sort_choice);
        void sort_income_date(int sort_choice);
        void search_expense();
        void search2_expense();
        void search_income();
        void search2_income();
        void ChartExpense();
        void ChartIncome();
        void changeCurrency();
        void setCurrency(string);
        void passCurrency(double);
        void displaySummaryExpense();
        void processSummaryExpense(string type);
        void displaySummaryIncome();
        void processSummaryIncome(string type);
        void setBudget();
    private:
        string username;
        double balance;
        double budget;
        string currency;
};

#endif // WALLET_H
