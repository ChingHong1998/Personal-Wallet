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

Wallet::Wallet(string name, double bal,double bud) : username(name),balance(bal),budget(bud) {
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
    vector<Expense> expensesVector = returnExpensesVector();
    string id;
    display_record(fin,Date);
    cout << "Enter the ID You want to delete: ";
    cin.get();
    getline(cin,id);
    for(int i = 0; i< expensesVector.size()-1;i++) {
        if(id == expensesVector[i].getID()) {
            expensesVector.erase(expensesVector.begin()+i);
            break;
        }
    }
    saveBack(expensesVector);
    expensesVector.clear();
    cout << "Deleted.\n";

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
    temp << "Budget: " << budget<<endl;
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
    cout << "Enter the specified date/ month/ year: " << endl;
    cin >> choose2;
    while(!filen1.eof()){
        string element;
        for(int i = 0; i < 5; i++){
            getline(filen1, record);
            if(record == "" || record == "\n"){
                break;
            }
            head = Insert(head, record);
        }
        element = GetNth(head,counter);
        int k = 0;
        if(choose == 2){
            k = 2;
        }
        if(choose == 3){
            k = 4;
        }
        for(int i = 0; i < choose2.length() ; i++, k++){
            if(element[k] == choose2[i]){
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
void Wallet::sort(){}
void Wallet::displaySummary(){
    string fromDate,toDate;
    Queue dateQueue;
    double food=0;
    double transport=0;
    double clothes=0;
    double accommodation=0;
    double others=0;
    int choice;
    vector<Expense> expensesVector = returnExpensesVector();
    cout << "What kinds of summary:\n\t1. Daily\n\t2. Monthly\n\t3. Yearly\n\t4. Certain Period\nYour choice: ";
    cin >> choice;
    switch(choice) {
    case 1: {
        cout << "Daily summary\n";
        string lastDate,lastDay;

        int i =0;
        for(lastDay= (expensesVector[i].getID().substr(0,6));i < expensesVector.size(); i++) {
            if((expensesVector[i].getID().substr(0,6)) == lastDay) {
                lastDate = expensesVector[i].getDate().substr(0,10) + " " + expensesVector[i].getDate().substr(20,4);
                if(expensesVector[i].getCategory() == "Food")
                    food += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Transport")
                    transport += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Clothes")
                    clothes += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Accommodation")
                    accommodation += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Others")
                    others += toDouble(expensesVector[i].getAmount());
                continue;
            }
            else {
                cout << "\nDate: " << lastDate <<endl;
                cout << "\tFood: " << food << endl;
                cout << "\tTransport: " << transport << endl;
                cout << "\tClothes: " << clothes << endl;
                cout << "\tAccommodation: " << accommodation << endl;
                cout << "\tOthers: " << others << endl;
                food=0;
                transport=0;
                clothes=0;
                accommodation=0;
                others=0;
                lastDay = (expensesVector[i].getID().substr(0,6));
                if(expensesVector[i].getCategory() == "Food")
                    food += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Transport")
                    transport += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Clothes")
                    clothes += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Accommodation")
                    accommodation += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Others")
                    others += toDouble(expensesVector[i].getAmount());
                continue;
            }

        }
        cout << "\nDate: " << lastDate <<endl;
        cout << "\tFood: " << food << endl;
        cout << "\tTransport: " << transport << endl;
        cout << "\tClothes: " << clothes << endl;
        cout << "\tAccommodation: " << accommodation << endl;
        cout << "\tOthers: " << others << endl;
        break;
        }
    case 2:{
        cout << "Monthly summary\n";
        string lastMonth,lastDate;
        int i =0;
        for(lastMonth= expensesVector[i].getID().substr(2,4);i < expensesVector.size(); i++) {
            if(expensesVector[i].getID().substr(2,4) == lastMonth) {
                lastDate = expensesVector[i].getDate().substr(4,3) + " " + expensesVector[i].getDate().substr(20,4);
                if(expensesVector[i].getCategory() == "Food")
                    food += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Transport")
                    transport += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Clothes")
                    clothes += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Accommodation")
                    accommodation += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Others")
                    others += toDouble(expensesVector[i].getAmount());
                continue;
            }
            else {
                cout << "\nDate: " << lastDate <<endl;
                cout << "\tFood: " << food << endl;
                cout << "\tTransport: " << transport << endl;
                cout << "\tClothes: " << clothes << endl;
                cout << "\tAccommodation: " << accommodation << endl;
                cout << "\tOthers: " << others << endl;
                food=0;
                transport=0;
                clothes=0;
                accommodation=0;
                others=0;
                lastMonth = expensesVector[i].getID().substr(2,4);
                if(expensesVector[i].getCategory() == "Food")
                    food += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Transport")
                    transport += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Clothes")
                    clothes += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Accommodation")
                    accommodation += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Others")
                    others += toDouble(expensesVector[i].getAmount());
                continue;
            }
        }
        cout << "\nDate: " << lastDate <<endl;
        cout << "\tFood: " << food << endl;
        cout << "\tTransport: " << transport << endl;
        cout << "\tClothes: " << clothes << endl;
        cout << "\tAccommodation: " << accommodation << endl;
        cout << "\tOthers: " << others << endl;
        break;
        }
    case 3: {
        cout << "Yearly summary\n";
        string lastMonth,lastDate;
        int i =0;
        for(lastMonth= expensesVector[i].getID().substr(4,2);i < expensesVector.size(); i++) {
            if(expensesVector[i].getID().substr(4,2) == lastMonth) {
                lastDate = expensesVector[i].getDate().substr(20,4);
                if(expensesVector[i].getCategory() == "Food")
                    food += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Transport")
                    transport += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Clothes")
                    clothes += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Accommodation")
                    accommodation += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Others")
                    others += toDouble(expensesVector[i].getAmount());
                continue;
            }
            else {
                cout << "\nDate: " << lastDate <<endl;
                cout << "\tFood: " << food << endl;
                cout << "\tTransport: " << transport << endl;
                cout << "\tClothes: " << clothes << endl;
                cout << "\tAccommodation: " << accommodation << endl;
                cout << "\tOthers: " << others << endl;
                food=0;
                transport=0;
                clothes=0;
                accommodation=0;
                others=0;
                lastMonth = expensesVector[i].getID().substr(4,2);
                if(expensesVector[i].getCategory() == "Food")
                    food += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Transport")
                    transport += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Clothes")
                    clothes += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Accommodation")
                    accommodation += toDouble(expensesVector[i].getAmount());
                else if(expensesVector[i].getCategory() == "Others")
                    others += toDouble(expensesVector[i].getAmount());
                continue;
            }
        }
        cout << "\nDate: " << lastDate <<endl;
        cout << "\tFood: " << food << endl;
        cout << "\tTransport: " << transport << endl;
        cout << "\tClothes: " << clothes << endl;
        cout << "\tAccommodation: " << accommodation << endl;
        cout << "\tOthers: " << others << endl;
        break;
        }
    default:
        cout<< "Invalid Option" <<endl;
    }
}
void Wallet::warning(){
    if(this->balance < this->budget) {
        cout << "***********WARNING*************"<<endl;
        cout << "Your Balance is under the budget you set, which is "<<this->budget<<endl<<endl;
    }
}
void Wallet::displayChart(){}
void Wallet::setBudget(){
    cout<< "Enter your budget(It will show warning message when your balance below budget): ";
    cin >> budget;
}

string Wallet::getBudget() { return tostr(this->budget);}
void Wallet::changeCurrency(){}


