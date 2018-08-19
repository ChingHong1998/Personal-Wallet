#include<iostream>
#include "wallet.hpp"
#include "expense.cpp"
#include "income.cpp"
#include <fstream>
#include <cstdlib>

using namespace std;

/* Can create a saving wallet*/
struct Node{
    string data;
    struct Node* next;
};
Node *Insert(Node *head, string x){
    Node *temp = new Node();
    temp->data = x;
    temp->next = head;
    head = temp;
    return head;
}

void print(Node *p){
    if(p == NULL){
        return;
    }
    print(p->next);
    cout << p->data << endl;
}

string GetNth(Node *head, int index){
    struct Node* current = head;
    int counter = 0;
    while(current != NULL){
        if(counter == index){
            return current->data;
        }
        counter++;
        current = current->next;
    }
}
void deleteAll(Node** head)
{
     Node* current = *head;
     Node* next;
     while (current != NULL)
     {
         next = current->next;
         delete current;
         current = next;
     }
     *head = NULL;
}
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
void Wallet::displaySummary(){
}
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

void Wallet::display_record(ifstream &filen1){
    Node *head = NULL;
    string record, element, choose2;
    int choose;
    int counter = 3;
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


