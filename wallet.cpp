#include<iostream>
#include "wallet.hpp"
#include "expense.cpp"
#include "income.cpp"
#include "linked_list.cpp"
#include <fstream>
#include <cstdlib>
#include<stdio.h>

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
void Wallet::deleteExpense(string Date, ifstream& fin){
    display_record(fin,Date);
    string id,temp,line;
    ifstream fin1;
    fin1.open("expenses.txt",ios::app|ios::in);
    ofstream tempFile;
    tempFile.open("temp.txt",ios::app|ios::out);
    int skip=0;
    cout << "Enter the ID you want to delete: ";
    cin>>id;
    while (getline(fin1, line)) {
        if ((line != id) && !(skip > 0)) {
           tempFile << line << endl;
        }
        else {
          if(skip == 0) {
              skip = 4;
          }
          else {
              --skip;
          }
       }
    }
    system("PAUSE");
    fin1.close();
    tempFile.close();
    remove("expenses.txt");
    rename("temp.txt", "expenses.txt");
    cout << "DELETED."<<endl;
}
double Wallet::displayBalance(){
    return balance;
}
string Wallet::displayUsername() {
    return username;
}

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

void Wallet::display_record(ifstream &filen1){
    Node *head = NULL;
    string record, element, choose2;
    int choose;
    int counter = 4;
    bool correct = false;
    cout << "Choose date, month or year: " << endl;
    cin >> choose;
    cout << "Enter the specified date: " << endl;
    cin >> choose2;
    while(!filen1.eof()){
        string element;
        for(int i = 0; i < 5; i++){
            getline(filen1, record);
            head = Insert(head, record);
        }
        element = GetNth(head,counter);
        for(int i = 0; i < 6; i++){
            if(element[i] == choose2[i]){
                correct = true;
            }
            else{
                correct = false;
                break;
            }
        }
        if(correct){
            print(head);
        }
        deleteAll(&head);

    }
    filen1.close();
    }

void Wallet::display_record(ifstream &filen1,string choose2){
    Node *head = NULL;
    string record, element;
    int counter = 4;
    bool correct = false;
    while(!filen1.eof()){
        string element;
        for(int i = 0; i < 5; i++){
            getline(filen1, record);
            head = Insert(head, record);
        }
        element = GetNth(head,counter);
        for(int i = 0; i < 6; i++){
            if(element[i] == choose2[i]){
                correct = true;
            }
            else{
                correct = false;
                break;
            }
        }
        if(correct){
            print(head);
        }
        deleteAll(&head);

    }
    filen1.close();
    }

void Wallet::deleteIncome(string Date){}
void Wallet::editExpense(string Date){}
void Wallet::editIncome(string Date){}
void Wallet::search(string Date){}
void Wallet::sort(){}
void Wallet::displaySummary(){
}
void Wallet::warning(){}
void Wallet::displayChart(){}
void Wallet::setBudget(){}
void Wallet::changeCurrency(){}
