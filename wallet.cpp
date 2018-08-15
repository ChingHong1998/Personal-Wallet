#include<iostream>
#include "wallet.hpp"
#include "expense.cpp"
#include "income.cpp"
#include <fstream>
#include <cstdlib>

using namespace std;

/* Can create a saving wallet*/

Wallet::Wallet(string name, double bal) : username(name),balance(bal) {
}

Wallet::~Wallet() {

}

void Wallet::addExpense(){
    Expense * expense = new Expense;
    cout<<"Enter your amount: ";
    double amount;
    cin >> amount;
    if(isEnough(amount)) {
        cout<<"Enter the detail: ";
        string detail;
        cin.ignore();
        getline(cin,detail);
        cout<<"Enter your category: ";
        string category;
        getline(cin,category);
        expense->add_record(amount,detail,category);
        cout << "\nAdded!";
        balance -= amount;
        update_data();
    }
    else
        cout<< "Not enough balance"<<endl;
        system("PAUSE");
}

void Wallet::addIncome(){
    Income * income = new Income;
    cout<<"Enter your amount: ";
    double amount;
    cin >> amount;
    cin.ignore();
    cout<<"Enter the detail: ";
    string detail;
    getline(cin, detail);
    cout<<"Enter your category: ";
    string category;
    getline(cin, category);
    income->add_record(amount,detail,category);
    cout << "\nAdded!";
    balance += amount;
    update_data();
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
bool Wallet::isEnough(double amount) {
    return (amount < balance);
}
void Wallet::update_data() {
    ofstream temp;
    temp.open("temp.txt", ios::app|ios::in);
    temp << "Username: " << username<<endl;
    temp << "Balance: " << balance<<endl;
    temp.close();
    remove("Wallet.txt");
    rename("temp.txt", "Wallet.txt");
}
