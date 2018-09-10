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
                getline(fin,temp);
                if(temp == "" || temp == "\n")
                    break;
                Expense expense;
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
        fout.open("temp.txt",ios::app | ios::out);
        if (fout.bad())
            throw &fout;
        else {
            for(int i = 0; i<vec.size();i++) {
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
    rename("temp.txt", "expenses.txt");
    cout<<"Save successful\n";
}

void merge(vector <Expense>& theArray, int first, int mid, int last, int choice ){
    vector <Expense> s = returnExpensesVector();
    int first1 = first;
    int last1 = mid;
    int first2 = mid+1;
    int last2 = last;

    int index;
    for(index=first; (first1<=last1) && (first2<=last2);++index) {
        if(choice == 1){
            if(toDouble(theArray[first1].getAmount()) < toDouble(theArray[first2].getAmount())) {
                s[index] = theArray[first1];
                ++first1;
            }
            else {
                s[index] = theArray[first2];
                ++first2;
            }
        }else if(choice == 2){
            if(toDouble(theArray[first1].getAmount()) > toDouble(theArray[first2].getAmount())) {
                s[index] = theArray[first1];
                ++first1;
            }
            else {
                s[index] = theArray[first2];
                ++first2;
            }
        }
    }

    while(first1 <=last1) {
        s[index] = theArray[first1];
        ++first1;
        ++index;
    }

    while(first2<=last2) {
        s[index] = theArray[first2];
        ++first2;
        ++index;
    }

    for(index=first;index<=last;++index){
        theArray[index] = s[index];
    }
}

void mergeSort(vector <Expense> &theArray, int first, int last, int choice){
   if(first < last) {
        int mid = (first+last)/2;
        mergeSort(theArray,first,mid,choice);
        mergeSort(theArray, mid + 1, last, choice);
        merge(theArray,first,mid,last,choice);
   }
}
int leftmost(vector <Expense> array, int min, int max, int value)
{
    if (min == max){
        return min;
    }
    int mid = (min + max) / 2;

    if (toDouble(array[mid].getAmount()) < value) {
        return leftmost(array, mid + 1, max, value);
    }
    else{
        return leftmost(array, min, mid, value);
    }
}

int rightmost(vector <Expense> array, int min, int max, int value)
{
    if (min == max){
        return min;
    }
    int mid = (min + max + 1) / 2;

    if (toDouble(array[mid].getAmount()) > value){
        return rightmost(array, min, mid - 1, value);
    }
    else{
        return rightmost(array, mid, max, value);
    }
}
void processSummary(string type) {
    vector<Expense> expensesVector = returnExpensesVector();
    double food=0;
    double transport=0;
    double clothes=0;
    double accommodation=0;
    double others=0;
    int startID, endID, startDate,endDate;
    if(type == "Daily") {
        startID = 0;
        endID = 6;
        startDate = 0;
        endDate = 10;
    } else if(type == "Monthly") {
        startID = 2;
        endID = 4;
        startDate = 4;
        endDate = 3;
    } else if(type == "Yearly") {
        startID = 4;
        endID = 2;
        startDate = 0;
        endDate = 0;
    }
    else
        cout<<"Error"<<endl;

    cout <<type<<" summary\n";
    string lastDate,lastDay;
    int i =0;
    for(lastDay= (expensesVector[i].getID().substr(startID,endID));i < expensesVector.size(); i++) {
        if((expensesVector[i].getID().substr(startID,endID)) == lastDay) {
            lastDate = expensesVector[i].getDate().substr(startDate,endDate) + " " + expensesVector[i].getDate().substr(20,4);
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
            lastDay = (expensesVector[i].getID().substr(startID,endID));
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
            lastDate = expensesVector[i].getDate().substr(startDate,endDate) + " " + expensesVector[i].getDate().substr(20,4);
        }

    }
    cout << "\nDate: " << lastDate <<endl;
    cout << "\tFood: " << food << endl;
    cout << "\tTransport: " << transport << endl;
    cout << "\tClothes: " << clothes << endl;
    cout << "\tAccommodation: " << accommodation << endl;
    cout << "\tOthers: " << others << endl;
    expensesVector.clear();
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
void Wallet::sort(int sort_choice){
        vector <Expense> expensesVector = returnExpensesVector();
        mergeSort(expensesVector, 0, expensesVector.size()- 1, sort_choice);
        saveBack(expensesVector);
}
void Wallet::displaySummary(){

    int choice;
    cout << "What kinds of summary:\n\t1. Daily\n\t2. Monthly\n\t3. Yearly\n\t4. Certain Period\nYour choice: ";
    cin >> choice;
    switch(choice) {
    case 1: {
        processSummary("Daily");
        break;
        }
    case 2:{
        processSummary("Monthly");
        break;
        }
    case 3: {
        processSummary("Yearly");
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
void Wallet::search(){
    string start_pt, end_pt;
    int start = 0, ending = 0;
    cout << "Enter the date you want to search in [DDMMYY]: \nFrom: ";
    cin >> start_pt;
    start_pt = start_pt + "1";
    cout << "Until: ";
    cin >> end_pt;
    vector <Expense> vec = returnExpensesVector();
    for(int i = 0; i < vec.size(); i++){
        string temp = vec[i].getID();
        if(temp == start_pt){
            start = i;
        }
    }
    for(int i = 0; i < vec.size(); i++){
        string temp = vec[i].getID();
        if(temp.substr(0,6) == end_pt){
            ending = i;
        }
    }
    for(int i = start; i <= ending; i++){
        cout << vec[i].getID() << endl;
        cout << vec[i].getDate() << endl;
        cout << vec[i].getAmount() << endl;
        cout << vec[i].getCategory() << endl;
        cout << vec[i].getDetail() << endl;
    }
}
void Wallet::search2(){
    sort(1);
    vector <Expense> vec = returnExpensesVector();
    cout << "Enter the amount you want to search: \n From: ";
    int start_amount, end_amount, start, ending;
    cin >> start_amount;
    cout << "Until: ";
    cin >> end_amount;
    start = leftmost(vec, 0, vec.size() - 1, start_amount);
    ending = rightmost(vec, 0, vec.size() - 1, end_amount);
    for(int i = start; i <= ending; i++){
        cout << vec[i].getID() << endl;
        cout << vec[i].getDate() << endl;
        cout << vec[i].getAmount() << endl;
        cout << vec[i].getCategory() << endl;
        cout << vec[i].getDetail() << endl;
    }
}
string Wallet::getBudget() { return tostr(this->budget);}

void Wallet::changeCurrency(){}


