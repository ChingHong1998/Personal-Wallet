#include<iostream>
#include "wallet.hpp"
#include "expense.cpp"
#include "income.cpp"
#include "linked_list.cpp"
#include <fstream>
#include <cstdlib>
#include <vector>
#include<stdio.h>
#include "queue.cpp"


using namespace std;

/* Can create a saving wallet*/


//insert data to vector and return it
vector<Expense> returnExpensesVector() {
    ifstream fin;
    vector<Expense> expensesVector;
    expensesVector.clear();
    string temp;
    try {
        fin.open("expenses.txt",ios::in|ios::app);
        if (fin.bad())
            throw &fin;
        else {
            while((!fin.eof()) && fin.good()) {
                Expense expense;
                getline(fin,temp);
                expense.setID(temp);
                getline(fin,temp);
                expense.setDate(temp);
                getline(fin,temp);
                expense.setAmount(temp);
                getline(fin,temp);
                expense.setCategory(temp);
                getline(fin,temp);
                expense.setDetail(temp);
                expensesVector.push_back(expense);
            }
            cout << "Pushed finished"<<endl;
        }
    }
    catch (ifstream &x) {
        cerr<<"Error occurs when open the file.";
    }
    fin.close();
    return expensesVector;
}

//save data from vector
void saveBack(vector<Expense> vec) {
    ofstream fout;
    try {
        fout.open("temp.txt",ios::app);
        if (fout.bad())
            throw &fout;
        else {
            for(int i = 0; i<vec.size()-1;i++) {
                fout<<vec[i].getID()<<endl;
                fout<<vec[i].getDate()<<endl;
                fout<<vec[i].getAmount()<<endl;
                fout<<vec[i].getCategory()<<endl;
                fout<<vec[i].getDetail()<<endl;
            }
        }
    }
    catch (ifstream &x) {
        cerr<<"Error occurs when write to the file.";
    }
    fout.close();
    remove("expenses.txt");
    rename("temp.txt","expenses.txt");
    cout<<"Save successful\n";
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
        cin.ignore();
        cout<<"Category : "<<endl;
        expense->display_category();
        cout<<"Enter your category: ";
        string category;
        getline(cin,category);
        cout<<"Enter the detail: ";
        string detail;
        getline(cin,detail);
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

void Wallet::display_all_expenses() {
    ifstream fin;
    string temp;
    Queue q1;
    fin.open("expenses.txt",ios::in);
    while(getline(fin,temp)) {
        q1.enqueue(temp);
    }
    while(!q1.isEmpty()) {
        cout<<"\tID: "<<q1.getFront()<<endl;
        q1.dequeue();
        cout<<"\tDate: "<<q1.getFront()<<endl;
        q1.dequeue();
        cout<<"\tAmount: "<<q1.getFront()<<endl;
        q1.dequeue();
        temp = q1.getFront();
        cout<<"\tCategory: "<<q1.getFront()<<endl;
        q1.dequeue();
        cout<<"\tDetail: "<<q1.getFront()<<endl<<endl;
        q1.dequeue();
    }
    fin.close();
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

void Wallet::editExpense(string Date){
    vector <Expense> expensesVector = returnExpensesVector();
    system("CLS");
    ifstream fin;
    fin.open("expenses.txt",ios::in|ios::app);
    display_record(fin,Date);
    fin.close();
    cout << "Enter the ID You want to Edit: ";
    string id;
    getline(cin,id);
    for(int i = 0; i<expensesVector.size()-1;i++) {
        if(expensesVector[i].getID() == id) {
            string date="";
            string amount="";
            string category="";
            string detail="";
            system("CLS");
            expensesVector[i].display();
            cout<< "^^^^^^^Before^^^^^^^\nEditing... (Hit Enter to skip the part)\n";
            cout<< "Date: ";
            getline(cin,date);
            cout<< "Amount: ";
            getline(cin,amount);
            expensesVector[i].display_category();
            cout<< "Category: ";
            getline(cin,category);
            cout<< "Detail: ";
            getline(cin,detail);
            expensesVector[i].remake(date,amount,category,detail);
            expensesVector[i].display();
            break;
        }
    }
    saveBack(expensesVector);
    expensesVector.clear();
    cout<<"Edit success";
}
void Wallet::editIncome(string Date){}
void Wallet::search(string Date){}
void Wallet::sort(){}
void Wallet::displaySummary(){}
void Wallet::warning(){}
void Wallet::displayChart(){}
void Wallet::setBudget(){}
void Wallet::changeCurrency(){}


