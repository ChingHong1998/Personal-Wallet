#include<iostream>
#include "wallet.hpp"
#include "expense.cpp"

using namespace std;

/* Can create a saving wallet*/

Wallet::Wallet() : balance(0) {}
Wallet::~Wallet() {}

void Wallet::addExpense(){
    Expense * expense = new Expense;
    cout<<"Enter your amount: ";
    double amount;
    cin >> amount;
    cout<<"Enter the detail: ";
    string detail;
    cin >> detail;
    cout<<"Enter your category: ";
    string category;
    cin >> category;
    expense->add_record(amount,detail,category);
    cout << "\nAdded!";
}

void Wallet::addIncome(float Amount,  string Date, string Detail, int Category){}
void Wallet::deleteExpense(string Date){}
void Wallet::deleteIncome(string Date){}
void Wallet::editExpense(string Date){}
void Wallet::editIncome(string Date){}
void Wallet::search(string Date){}
void Wallet::sort(){}
void Wallet::displayBalance(){}
void Wallet::displaySummary(){}
void Wallet::warning(){}
void Wallet::displayChart(){}
void Wallet::setBudget(){}
void Wallet::changeCurrency(){}

