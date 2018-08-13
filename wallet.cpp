#include<iostream>
#include "wallet.hpp"
#include "expense.cpp"
#include "income.cpp"

using namespace std;

/* Can create a saving wallet*/

Wallet::Wallet(string name, double bal) : username(name),balance(bal) {
}

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

void Wallet::addIncome(){
    Income * income = new Income;
    cout<<"Enter your amount: ";
    double amount;
    cin >> amount;
    cout<<"Enter the detail: ";
    string detail;
    cin >> detail;
    cout<<"Enter your category: ";
    string category;
    cin >> category;
    income->add_record(amount,detail,category);
    cout << "\nAdded!";
}
void Wallet::deleteExpense(string Date){}
void Wallet::deleteIncome(string Date){}
void Wallet::editExpense(string Date){}
void Wallet::editIncome(string Date){}
void Wallet::search(string Date){}
void Wallet::sort(){}
double Wallet::displayBalance(){
    return balance;
}
string Wallet::displayUsername() {
    return username;
}
void Wallet::displaySummary(){}
void Wallet::warning(){}
void Wallet::displayChart(){}
void Wallet::setBudget(){}
void Wallet::changeCurrency(){}

