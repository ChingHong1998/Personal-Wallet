#include "Wallet.h"

Wallet::Wallet()
{
    //ctor
}

Wallet::Wallet(string name, double bal,double bud, string cur) : username(name),balance(bal),budget(bud),currency(cur) {
}

double Wallet::getBudget(){
    return budget;
}

string Wallet::displayUsername() {
    return username;
}

double Wallet::displayBalance(){
    return balance;
}

string Wallet::getCurrency(){return this->currency;}

void Wallet::warning(){
    if(this->balance < this->budget) {
        cout << "***********WARNING*************"<<endl;
        cout << "Your Balance is under the budget you set, which is "<<this->budget<<endl<<endl;
    }
}

void Wallet::addExpense(){
    cin.ignore();
    cout<<string(50, '.')<<endl;
    cout << "You Are Currently Adding An Expense Record...." << endl;
    Expense * expense = new Expense;
    cout<<"Enter Your Amount: ";
    string amount;
    do {
        getline(cin, amount);
    }while(isNotValidInt(amount));
    if(isEnough(toDouble(amount))) {
        cout<<"Category : "<<endl;
        expense->display_category();

        string category;
        do {
            cout<<"Enter Your Category[1~5]: ";
            getline(cin,category);
        }while(toDouble(category)>5 || toDouble(category)<=0);
        cout<<"Enter The Detail: ";
        string detail;
        getline(cin,detail);
        expense->add_record(toDouble(amount),detail,category);
        cout << "\nAdded!";
        balance -= toDouble(amount);
        update_data();
    }
    else
        cout<< "Not enough balance"<<endl;
}

void Wallet::addIncome(){
    cin.ignore();
    cout<<string(50, '.')<<endl;
    Income * income = new Income;
    cout << "You Are Currently Adding An Income Record...." << endl;
    cout<<"Enter Your Amount: ";
    string amount;
    do {
        getline(cin, amount);
    }while(isNotValidInt(amount));
    cout<<"Category: " << endl;
    income->display_category();
    string category;
    do {
        cout<<"Enter Your Category[1~5]: ";
        getline(cin,category);
    }while(toDouble(category)>5 || toDouble(category)<=0);
    cout<<"Enter The Detail: ";
    string detail;
    getline(cin, detail);
    income->add_record(toDouble(amount),detail,category);
    cout << "\nAdded!";
    balance += toDouble(amount);
    update_data();
}

bool Wallet::isEnough(double amount) {
    return (amount < balance);
}

void Wallet::update_data() {
    ofstream temp;
    temp.open("temp1.txt", ios::app|ios::in);
    temp << "Username: " << username<<endl;
    temp << "Balance: " << balance<<endl;
    temp << "Budget: " << budget<<endl;
    temp << "Currency: " << currency <<endl;
    temp.close();
    remove("Wallet.txt");
    rename("temp1.txt", "Wallet.txt");
}

void Wallet::editExpense(ifstream &filen1){
    Expense *expense = new Expense();
    vector <Expense> expensesVector = expense->returnExpensesVector();
    cout<<string(50, '.')<<endl;
    cout << "You Are Currently Editing An Expense Record...." << endl;
    cout << "Enter the date you want to edit[DDMMYY]: ";
    display_day_record(filen1);
    filen1.close();
    cout << "Enter the ID You want to Edit: ";
    string id;
    getline(cin,id);
    bool noThisID = true;
    for(int i = 0; i<expensesVector.size();i++) {
        if(expensesVector[i].getID() == id)
            noThisID = false;
    }
    if(!noThisID) {
        for(int i = 0; i<expensesVector.size();i++) {
            if(expensesVector[i].getID() == id) {
                balance += toDouble(expensesVector[i].getAmount());
                string amount="";
                string category="";
                string detail="";
                system("CLS");
                expensesVector[i].display();
                cout<< "^^^^^^^Before^^^^^^^\nEditing... (Hit Enter to skip the part)\n";
                cout<< "Amount: ";
                do {
                    getline(cin, amount);
                }while(isNotValidInt(amount));
                expensesVector[i].display_category();
                cout<< "Category: ";
                getline(cin,category);
                cout<< "Detail: ";
                getline(cin,detail);
                expensesVector[i].remake(amount,category,detail);
                cout<< ".......After........."<<endl;
                expensesVector[i].display();
                balance -= toDouble(amount);
                cout<<"Edit successful";
                break;
            }
        }
    }
    else
        cout << "No This ID"<<endl;
    expense->saveBack(expensesVector);
    expensesVector.clear();
    update_data();
}
void Wallet::editIncome(ifstream &filen1){
    Income *income = new Income();
    vector <Income> incomesVector = income->returnIncomeVector();
    cout<<string(50, '.')<<endl;
    cout << "You Are Currently Editing An Income Record...." << endl;
    cout << "Enter the date you want to edit[DDMMYY]: ";
    display_day_record(filen1);
    filen1.close();
    cout << "Enter the ID You want to Edit: ";
    string id;
    getline(cin,id);
    bool noThisID = true;
    for(int i = 0; i<incomesVector.size();i++) {
        if(incomesVector[i].getID() == id)
            noThisID = false;
    }
    if(!noThisID) {
        for(int i = 0; i<incomesVector.size();i++) {
            if(incomesVector[i].getID() == id) {
                balance -= toDouble(incomesVector[i].getAmount());
                string amount="";
                string category="";
                string detail="";
                system("CLS");
                incomesVector[i].display();
                cout<< "^^^^^^^Before^^^^^^^\nEditing... (Hit Enter to skip the part)\n";
                cout<< "Amount: ";
                do {
                    getline(cin, amount);
                }while(isNotValidInt(amount));
                incomesVector[i].display_category();
                cout<< "Category: ";
                getline(cin,category);
                cout<< "Detail: ";
                getline(cin,detail);
                cout << endl;
                incomesVector[i].remake(amount,category,detail);
                cout<< ".......After........."<<endl;
                incomesVector[i].display();
                balance += toDouble(amount);
                cout<<"Edit successful";
                break;
            }
        }
    }
    else
        cout << "No This ID"<<endl;
    income->saveBack(incomesVector);
    incomesVector.clear();

    update_data();
}
void Wallet::display_day_record(ifstream &filen1){
    cin.ignore();
    Node *head = NULL;
    string record, element;
    int counter = 4;
    string choose2;
    getline(cin,choose2);
    bool correct = false;
    int found =0;
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
            print(head,4);
            cout << endl;
            found++;
        }

        deleteAll(&head);
    }
    if(found==0) {
        cout<<"No record found.\n";
    }
    filen1.close();
}

void Wallet::deleteExpense(ifstream& fin){
    Expense *expense = new Expense();
    vector<Expense> expensesVector = expense->returnExpensesVector();
    string id;
    cout<<string(50, '.')<<endl;
    cout << "You Are Currently Deleting An Expense Record...." << endl;
    cout << "Enter the day you want to delete[DDMMYY]: ";
    display_day_record(fin);
    cout << "Enter the ID You want to delete: ";
    getline(cin,id);
    bool noThisId = true;
    for(int i = 0; i< expensesVector.size();i++) {
        if(id == expensesVector[i].getID())
            noThisId = false;
    }
    if(!noThisId) {
    for(int i = 0; i< expensesVector.size();i++) {
        if(id == expensesVector[i].getID()) {
            balance += toDouble(expensesVector[i].getAmount());
            expensesVector.erase(expensesVector.begin()+i);
            cout << "Deleted.\n";
            break;
        }
        }
    } else
    cout<<"No This ID!"<<endl;
    fin.close();
    expense->saveBack(expensesVector);
    expensesVector.clear();

    update_data();
}

void Wallet::deleteIncome(ifstream& fin){
    Income *income = new Income();
    vector<Income> incomesVector = income->returnIncomeVector();
    string id;
    cout<<string(50, '.')<<endl;
    cout << "You Are Currently Deleting An Income Record...." << endl;
    cout << "Enter the day you want to delete[DDMMYY]: ";
    display_day_record(fin);
    cout << "Enter the ID You want to delete: ";
    getline(cin,id);
    bool noThisId = true;
    for(int i = 0; i< incomesVector.size();i++) {
        if(id == incomesVector[i].getID())
            noThisId = false;
    }
    if(!noThisId) {
    for(int i = 0; i< incomesVector.size();i++) {
        if(id == incomesVector[i].getID()) {
            balance += toDouble(incomesVector[i].getAmount());
            incomesVector.erase(incomesVector.begin()+i);
            cout << "Deleted.\n";
            break;
        }
        }
    } else
    cout<<"No This ID!"<<endl;
    income->saveBack(incomesVector);
    incomesVector.clear();
    cout << "Deleted.\n";
    update_data();
}

void Wallet::displayAll(ifstream &fin) {
    cin.ignore();
    cout<<string(50, '.')<<endl;
    cout << "You Are Currently Viewing All Expense Record...." << endl;
    string temp;
    Queue q1;
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
        cout<<"\tCategory: "<<q1.getFront()<<endl;
        q1.dequeue();
        cout<<"\tDetail: "<<q1.getFront()<<endl<<endl;
        q1.dequeue();
    }
    fin.close();
}

void Wallet::display_record(ifstream &filen1, int choose){
    cin.ignore();
    Node *head = NULL;
    string record, element, choose2;
    int counter = 4;
    bool correct = false;
    int found = 0;
    if(choose == 2){
        cout << "Please enter the specified date in DD format: ";
    }else if(choose == 3){
        cout << "Please enter the specified month in MM format: ";
    }else{
        cout << "Please enter the specified year in YY format: ";
    }
    getline(cin,choose2);
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
        if(choose == 3){
            k = 2;
        }
        if(choose == 4){
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
            print(head,4);
            cout << endl;
            found++;
        }
        deleteAll(&head);
    }
    if(found==0) {
        cout<< "No records found."<<endl;
    }
    filen1.close();
}

void Wallet::sort_expense_amount(int sort_choice){
        Expense *expense = new Expense();
        vector <Expense> expensesVector = expense->returnExpensesVector();
        expense->mergeSort(expensesVector, 0, expensesVector.size() - 1, sort_choice);
        for(int i = 0; i < expensesVector.size(); i++){
            cout << "\tID: " << expensesVector[i].getID() << endl;
            cout << "\tDate: " << expensesVector[i].getDate() << endl;
            cout << "\tAmount: " << expensesVector[i].getAmount() << endl;
            cout << "\tCategory: " << expensesVector[i].getCategory() << endl;
            cout << "\tDetail: " << expensesVector[i].getDetail() << endl;
            cout << endl;
        }
}

void Wallet::sort_expense_date(int sort_choice){
    Expense *expense = new Expense();
    vector <Expense> expensesVector = expense->returnExpensesVector();
    Expense temparr[1];
    double year1, month1, date1, id1, year2, month2, date2, id2;
    for(int i = 0; i < expensesVector.size() - 1; i++){
        for(int x = 0; x < expensesVector.size() - 1; x++){
            year1 = toDouble(expensesVector[x].getID().substr(4,2)); year2 = toDouble(expensesVector[x+1].getID().substr(4,2));
            month1 = toDouble(expensesVector[x].getID().substr(2,2)); month2 = toDouble(expensesVector[x+1].getID().substr(2,2));
            date1 = toDouble(expensesVector[x].getID().substr(0,2)); date2 = toDouble(expensesVector[x+1].getID().substr(0,2));
            id1 = toDouble(expensesVector[x].getID().substr(6,1)); id2 = toDouble(expensesVector[x+1].getID().substr(6,1));
                if(sort_choice == 3){
                    if((year1 < year2)){
                        temparr[0] = expensesVector[x+1];
                        expensesVector[x+1] = expensesVector[x];
                        expensesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 < month2)){
                        temparr[0] = expensesVector[x+1];
                        expensesVector[x+1] = expensesVector[x];
                        expensesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 == month2) && (date1 < date2)){
                        temparr[0] = expensesVector[x+1];
                        expensesVector[x+1] = expensesVector[x];
                        expensesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 == month2) && (date1 == date2) && (id1 > id2)){
                        temparr[0] = expensesVector[x+1];
                        expensesVector[x+1] = expensesVector[x];
                        expensesVector[x] = temparr[0];
                    }
                }
                if(sort_choice == 4){
                    if((year1 > year2)){
                        temparr[0] = expensesVector[x+1];
                        expensesVector[x+1] = expensesVector[x];
                        expensesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 > month2)){
                        temparr[0] = expensesVector[x+1];
                        expensesVector[x+1] = expensesVector[x];
                        expensesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 == month2) && (date1 > date2)){
                        temparr[0] = expensesVector[x+1];
                        expensesVector[x+1] = expensesVector[x];
                        expensesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 == month2) && (date1 == date2) && (id1 > id2)){
                        temparr[0] = expensesVector[x+1];
                        expensesVector[x+1] = expensesVector[x];
                        expensesVector[x] = temparr[0];
                    }
                }
            }
        }
        for(int i = 0; i < expensesVector.size(); i++){
            cout << "\tID: " << expensesVector[i].getID() << endl;
            cout << "\tDate: " << expensesVector[i].getDate() << endl;
            cout << "\tAmount: " << expensesVector[i].getAmount() << endl;
            cout << "\tCategory: " << expensesVector[i].getCategory() << endl;
            cout << "\tDetail: " << expensesVector[i].getDetail() << endl;
            cout << endl;
        }
        expensesVector.clear();
        cout << "Sorted" << endl;
}

void Wallet::sort_income_amount(int sort_choice){
        Income *income = new Income();
        vector <Income> incomesVector = income->returnIncomeVector();
        income->mergeSort(incomesVector, 0, incomesVector.size() - 1, sort_choice);
        for(int i = 0; i < incomesVector.size(); i++){
            cout << "\tID: " << incomesVector[i].getID() << endl;
            cout << "\tDate: " << incomesVector[i].getDate() << endl;
            cout << "\tAmount: " << incomesVector[i].getAmount() << endl;
            cout << "\tCategory: " << incomesVector[i].getCategory() << endl;
            cout << "\tDetail: " << incomesVector[i].getDetail() << endl;
            cout << endl;
        }
}

void Wallet::sort_income_date(int sort_choice){
    Income *income = new Income();
    vector <Income> incomesVector = income->returnIncomeVector();
    Income temparr[1];
    double year1, month1, date1, id1, year2, month2, date2, id2;
    for(int i = 0; i < incomesVector.size() - 1; i++){
        for(int x = 0; x < incomesVector.size() - 1; x++){
            year1 = toDouble(incomesVector[x].getID().substr(4,2)); year2 = toDouble(incomesVector[x+1].getID().substr(4,2));
            month1 = toDouble(incomesVector[x].getID().substr(2,2)); month2 = toDouble(incomesVector[x+1].getID().substr(2,2));
            date1 = toDouble(incomesVector[x].getID().substr(0,2)); date2 = toDouble(incomesVector[x+1].getID().substr(0,2));
            id1 = toDouble(incomesVector[x].getID().substr(6,1)); id2 = toDouble(incomesVector[x+1].getID().substr(6,1));
                if(sort_choice == 3){
                    if((year1 < year2)){
                        temparr[0] = incomesVector[x+1];
                        incomesVector[x+1] = incomesVector[x];
                        incomesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 < month2)){
                        temparr[0] = incomesVector[x+1];
                        incomesVector[x+1] = incomesVector[x];
                        incomesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 == month2) && (date1 < date2)){
                        temparr[0] = incomesVector[x+1];
                        incomesVector[x+1] = incomesVector[x];
                        incomesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 == month2) && (date1 == date2) && (id1 > id2)){
                        temparr[0] = incomesVector[x+1];
                        incomesVector[x+1] = incomesVector[x];
                        incomesVector[x] = temparr[0];
                    }
                }
                if(sort_choice == 4){
                    if((year1 > year2)){
                        temparr[0] = incomesVector[x+1];
                        incomesVector[x+1] = incomesVector[x];
                        incomesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 > month2)){
                        temparr[0] = incomesVector[x+1];
                        incomesVector[x+1] = incomesVector[x];
                        incomesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 == month2) && (date1 > date2)){
                        temparr[0] = incomesVector[x+1];
                        incomesVector[x+1] = incomesVector[x];
                        incomesVector[x] = temparr[0];
                    }else if((year1 == year2) && (month1 == month2) && (date1 == date2) && (id1 > id2)){
                        temparr[0] = incomesVector[x+1];
                        incomesVector[x+1] = incomesVector[x];
                        incomesVector[x] = temparr[0];
                    }
                }
            }
        }
        for(int i = 0; i < incomesVector.size(); i++){
            cout << "\tID: " << incomesVector[i].getID() << endl;
            cout << "\tDate: " << incomesVector[i].getDate() << endl;
            cout << "\tAmount: " << incomesVector[i].getAmount() << endl;
            cout << "\tCategory: " << incomesVector[i].getCategory() << endl;
            cout << "\tDetail: " << incomesVector[i].getDetail() << endl;
            cout << endl;
        }
        incomesVector.clear();
        cout << "Sorted" << endl;
}

void Wallet::search_expense(){
    cin.ignore();
    Expense *expense = new Expense;
    string start_pt, end_pt;
    int found = 0;
    cout << "Enter the date you want to search in [DDMMYY]: \nFrom: ";
    getline(cin,start_pt);
    cout << "Until: ";
    getline(cin,end_pt);
    double start_in_number = toDouble(start_pt.substr(4,2)+start_pt.substr(2,2)+start_pt.substr(0,2));
    double end_in_number = toDouble(end_pt.substr(4,2)+end_pt.substr(2,2)+end_pt.substr(0,2));
    vector <Expense> vec = expense->returnExpensesVector();
    for(int i = 0; i < vec.size(); i++){
        double temp = toDouble(vec[i].getID().substr(4,2)+vec[i].getID().substr(2,2)+vec[i].getID().substr(0,2));
        if(temp >= start_in_number && temp <= end_in_number){
            found++;
            cout << "\tID: " << vec[i].getID() << endl;
            cout << "\tDate: " << vec[i].getDate() << endl;
            cout << "\tAmount: " << vec[i].getAmount() << endl;
            cout << "\tCategory: " << vec[i].getCategory() << endl;
            cout << "\tDetail: " << vec[i].getDetail() << endl;
            cout << endl;
        }
    }
    if(found==0) {
        cout<< "No records found."<<endl;
    }
}
void Wallet::search2_expense(){
    Expense *expense = new Expense();
    int found =0;
    vector <Expense> vec = expense->returnExpensesVector();
    expense->mergeSort(vec, 0, vec.size() - 1, 1);
    cout << "Enter the amount you want to search: \nFrom: ";
    int start_amount, end_amount, start, ending;
    cin >> start_amount;
    cout << "Until: ";
    cin >> end_amount;
    start = expense->leftmost(vec, 0, vec.size() - 1, start_amount);
    ending = expense->rightmost(vec, 0, vec.size() - 1, end_amount);
    for(int i = start; i <= ending; i++){
        found++;
        cout << "\tID: " << vec[i].getID() << endl;
        cout << "\tDate: " << vec[i].getDate() << endl;
        cout << "\tAmount: " << vec[i].getAmount() << endl;
        cout << "\tCategory: " << vec[i].getCategory() << endl;
        cout << "\tDetail: " << vec[i].getDetail() << endl;
        cout << endl;
    }
    if(found==0) {
        cout<< "No records found."<<endl;
    }
    cin.ignore();
}
void Wallet::search_income(){
    cin.ignore();
    Income *income = new Income;
    int found = 0;
    string start_pt, end_pt;
    cout << "Enter the date you want to search in [DDMMYY]: \nFrom: ";
    getline(cin,start_pt);
    cout << "Until: ";
    getline(cin,end_pt);
    double start_in_number = toDouble(start_pt.substr(4,2)+start_pt.substr(2,2)+start_pt.substr(0,2));
    double end_in_number = toDouble(end_pt.substr(4,2)+end_pt.substr(2,2)+end_pt.substr(0,2));
    vector <Income> vec = income->returnIncomeVector();
    for(int i = 0; i < vec.size(); i++){
        double temp = toDouble(vec[i].getID().substr(4,2)+vec[i].getID().substr(2,2)+vec[i].getID().substr(0,2));
        if(temp >= start_in_number && temp <= end_in_number){
            found++;
            cout << "\tID: " << vec[i].getID() << endl;
            cout << "\tDate: " << vec[i].getDate() << endl;
            cout << "\tAmount: " << vec[i].getAmount() << endl;
            cout << "\tCategory: " << vec[i].getCategory() << endl;
            cout << "\tDetail: " << vec[i].getDetail() << endl;
            cout << endl;
        }
    }
    if(found==0) {
        cout<< "No records found."<<endl;
    }
}
void Wallet::search2_income(){
    Income *income = new Income();
    int found=0;
    vector <Income> vec = income->returnIncomeVector();
    income->mergeSort(vec, 0, vec.size() - 1, 1);
    cout << "Enter the amount you want to search: \n From: ";
    int start_amount, end_amount, start, ending;
    cin >> start_amount;
    cout << " Until: ";
    cin >> end_amount;
    start = income->leftmost(vec, 0, vec.size() - 1, start_amount);
    ending = income->rightmost(vec, 0, vec.size() - 1, end_amount);
    for(int i = start; i <= ending; i++){
        found++;
        cout << "\tID: " << vec[i].getID() << endl;
        cout << "\tDate: " << vec[i].getDate() << endl;
        cout << "\tAmount: " << vec[i].getAmount() << endl;
        cout << "\tCategory: " << vec[i].getCategory() << endl;
        cout << "\tDetail: " << vec[i].getDetail() << endl;
        cout << endl;
    }
    if(found==0) {
        cout<< "No records found."<<endl;
    }
}
void Wallet::ChartExpense(){
    cin.ignore();
    Expense *expense = new Expense();
    string x[5] = {"Food", "Transport", "Clothes", "Accommodation", "Others"};
    vector <Expense> vec = expense->returnExpensesVector();
    int total = 0, first = 0, second = 0, third = 0, forth = 0, fifth = 0;
    for(int i = 0; i < vec.size(); i++){
        if(vec[i].getCategory() == x[0]){
            first += toDouble(vec[i].getAmount());
        }else if(vec[i].getCategory() == x[1]){
            second += toDouble(vec[i].getAmount());
        }else if(vec[i].getCategory() == x[2]){
            third += toDouble(vec[i].getAmount());
        }else if(vec[i].getCategory() == x[3]){
            forth += toDouble(vec[i].getAmount());
        }else if(vec[i].getCategory() == x[4]){
            fifth += toDouble(vec[i].getAmount());
        }
        total += toDouble(vec[i].getAmount());
    }
    int arr_all[5] = {first, second, third, forth, fifth};
    int highest = arr_all[0];
    for(int i = 0; i < 5; i++){
        if(arr_all[i] > highest){
            highest = arr_all[i];
        }
    }
    int dividen;
    if(highest < 50){
        dividen = 1;
    }else if(highest < 100){
        dividen = 5;
    }else if(highest < 500){
        dividen = 10;
    }else if(highest < 1000){
        dividen = 50;
    }else if(highest < 5000){
        dividen = 100;
    }else if(highest < 10000){
        dividen = 500;
    }else{
        dividen = 1000;
    }
    highest = highest / dividen;
    int max_point = highest * dividen;
    int min_point = max_point - dividen;
    for(int i = 0; i < 5; i++){
        arr_all[i] = (arr_all[i] / dividen);
        if(arr_all[i] == 0){
            arr_all[i] = 1;
        }
    }
    cout << "@ represents " << dividen << " units" << endl;
    for(int i = 0; i < 5; i++){
        cout << x[i].at(0) << " = " << x[i] << endl;
    }
    cout << endl;
    cout << endl;
    cout << "           Currency" << endl;
    cout << "               ^" << endl;
    for(int rows = highest; rows >= 1; rows--){
        cout << setw(8) << max_point << " -" << setw(4) << min_point << " |  ";
        max_point = min_point - 1;
        min_point = max_point - dividen + 1;
        for(int cols=0; cols <5; cols++){
            if(arr_all[cols] >= rows){
                cout << "         @ ";
            }else{
                cout << "           ";
            }
        }
        cout << endl;
    }
    cout << "               ";
    for(int cols = 0; cols < 5; cols++){
        cout << "-------------";
    }
    cout << "> Categories" << endl;
    cout << "                 ";
    for(int cols = 0; cols < 5; cols++){
        cout << "          " << x[cols].at(0);
    }
}

void Wallet::ChartIncome(){
    cin.ignore();
    system("cls");
    Income *income = new Income();
    string x[5] = {"Salary", "Dividend", "Commission", "Interest", "Others"};
    vector <Income> vec = income->returnIncomeVector();
    int total = 0, first = 0, second = 0, third = 0, forth = 0, fifth = 0;
    for(int i = 0; i < vec.size(); i++){
        if(vec[i].getCategory() == x[0]){
            first += toDouble(vec[i].getAmount());
        }else if(vec[i].getCategory() == x[1]){
            second += toDouble(vec[i].getAmount());
        }else if(vec[i].getCategory() == x[2]){
            third += toDouble(vec[i].getAmount());
        }else if(vec[i].getCategory() == x[3]){
            forth += toDouble(vec[i].getAmount());
        }else if(vec[i].getCategory() == x[4]){
            fifth += toDouble(vec[i].getAmount());
        }
        total += toDouble(vec[i].getAmount());
    }
    int arr_all[5] = {first, second, third, forth, fifth};
    int highest = arr_all[0];
    for(int i = 0; i < 5; i++){
        if(arr_all[i] > highest){
            highest = arr_all[i];
        }
    }
    int dividen;
    if(highest < 50){
        dividen = 1;
    }else if(highest < 100){
        dividen = 5;
    }else if(highest < 500){
        dividen = 10;
    }else if(highest < 1000){
        dividen = 50;
    }else if(highest < 5000){
        dividen = 100;
    }else if(highest < 10000){
        dividen = 500;
    }else{
        dividen = 1000;
    }
    highest = highest / dividen;
    int max_point = highest * dividen;
    int min_point = max_point - dividen;
    for(int i = 0; i < 5; i++){
        arr_all[i] = (arr_all[i] / dividen);
        if(arr_all[i] == 0){
            arr_all[i] = 1;
        }
    }
    cout << "@ represents " << dividen << " units" << endl;
    for(int i = 0; i < 5; i++){
        cout << x[i].at(0) << " = " << x[i] << endl;
    }
    cout << endl;
    cout << endl;
    cout << "           Currency" << endl;
    cout << "               ^" << endl;
    for(int rows = highest; rows >= 1; rows--){
        cout << setw(8) << max_point << " -" << setw(4) << min_point << " |  ";
        max_point = min_point - 1;
        min_point = max_point - dividen + 1;
        for(int cols=0; cols <5; cols++){
            if(arr_all[cols] >= rows){
                cout << "         @ ";
            }else{
                cout << "           ";
            }
        }
        cout << endl;
    }
    cout << "               ";
    for(int cols = 0; cols < 5; cols++){
        cout << "-------------";
    }
    cout << "> Categories" << endl;
    cout << "                 ";
    for(int cols = 0; cols < 5; cols++){
        cout << "          " << x[cols].at(0);
    }
}

void Wallet::changeCurrency(){
    int option1;
    cout<< "\n1. RM\n2. SGD\n3. RMB\n4. BAHT\n";
    cout<< "Please choose the currency that you wish to convert to:"<<endl;
    cin>>option1;
    int currency_unit;
    if(currency == "RM  ") {
        currency_unit=1;
    }
    else if(currency == "SGD "){
        currency_unit=2;
    }
    else if(currency == "RMB "){
        currency_unit=3;
    }
    else if(currency == "BAHT"){
        currency_unit=4;
    }
    switch(currency_unit){
    case 1:
        if(option1==1){
            balance=balance;}
        else if(option1==2){
            balance*=0.330719;
            budget*=0.330719;
            passCurrency(0.330719);
            this->setCurrency("SGD ");}
        else if(option1==3){
            balance*=1.65520;
            budget*=1.65520;
            passCurrency(1.65520);
            this->setCurrency("RMB ");
            }
        else if(option1==4){
            balance*=7.86428;
            budget*=7.86428;
            passCurrency(7.86428);
            this->setCurrency("BAHT");}
        break;
    case 2:
        if(option1==1){
            balance*=3.02523;
            budget*=3.02523;
            passCurrency(3.02523);
            this->setCurrency("RM  ");}
        else if(option1==2){
            balance=balance;}
        else if(option1==3){
            balance*=4.99080;
            budget*=4.99080;
            passCurrency(4.99080);
            this->setCurrency("RMB ");}
        else if(option1==4){
            balance*=23.7866;
            budget*=23.7866;
            passCurrency(23.7866);
            this->setCurrency("BAHT");}
    break;
    case 3:
        if(option1==1){
            balance*=0.606175;
            budget*=0.606175;
            passCurrency(0.606175);
            this->setCurrency("RM  ");}
        else if(option1==2){
            balance*=0.200368;
            budget*=0.200368;
            passCurrency(0.200368);
            this->setCurrency("SGD ");}
        else if(option1==3){
            balance=balance;}
        else if(option1==4){
            balance*=4.76526;
            budget*=4.76526;
            passCurrency(4.76526);
            this->setCurrency("BAHT");}
        break;
    case 4:
        if(option1==1){
            balance*=0.127219;
            budget*=0.127219;
            passCurrency(0.127219);
            this->setCurrency("RM  ");}
        else if(option1==2){
            balance*=0.0420549;
            budget*=0.0420549;
            passCurrency(0.0420549);
            this->setCurrency("SGD ");}
        else if(option1==3){
            balance*=0.209862;
            budget*=0.209862;
            passCurrency(0.209862);
            this->setCurrency("RMB ");}
        else if(option1==4){
            balance=balance;}
        break;
    default:
        cout<< "Invalid option" <<endl;
    }
}
void Wallet::passCurrency(double value) {
    Expense *expense = new Expense();
    vector<Expense> exVector = expense->returnExpensesVector();
    Income *income = new Income();
    vector<Income> exVector2 = income->returnIncomeVector();
    for(int i= 0 ; i < exVector2.size() ; i++)
    {
        double exp=toDouble(exVector2[i].getAmount());
        exp*=value;
        exVector2[i].setAmount(tostr(exp));
    }
    for(int i= 0 ; i < exVector.size() ; i++)
    {
        double exp=toDouble(exVector[i].getAmount());
        exp*=value;
        exVector[i].setAmount(tostr(exp));
    }
    income->saveBack(exVector2);
    expense->saveBack(exVector);
}

void Wallet::setCurrency(string cur){this->currency=cur;}

void Wallet::processSummaryExpense(string type) {
    cin.ignore();
    Expense *expense = new Expense();
    vector<Expense> expensesVector = expense->returnExpensesVector();
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
    else{
        cout<<"Error"<<endl;
    }
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
            cout << "\n\tDate: " << lastDate <<endl;
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
    cout << "\n\tDate: " << lastDate <<endl;
    cout << "\tFood: " << food << endl;
    cout << "\tTransport: " << transport << endl;
    cout << "\tClothes: " << clothes << endl;
    cout << "\tAccommodation: " << accommodation << endl;
    cout << "\tOthers: " << others << endl;
    expensesVector.clear();
}


void Wallet::displaySummaryExpense(){

    int choice;
    cout << "What kinds of summary:\n\t1. Daily\n\t2. Monthly\n\t3. Yearly\n\tYour choice: ";
    cin >> choice;
    switch(choice) {
    case 1: {
        processSummaryExpense("Daily");
        break;
        }
    case 2:{
        processSummaryExpense("Monthly");
        break;
        }
    case 3: {
        processSummaryExpense("Yearly");
        break;
        }
    default:
        cout<< "Invalid Option" <<endl;
    }
}
void Wallet::processSummaryIncome(string type) {
    Income *income = new Income();
    vector<Income> incomesVector = income->returnIncomeVector();
    double salary=0;
    double dividend=0;
    double commission=0;
    double interest=0;
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
    else{
        cout<<"Error"<<endl;
    }
    cout <<type<<" summary\n";
    string lastDate,lastDay;
    int i =0;
    for(lastDay= (incomesVector[i].getID().substr(startID,endID));i < incomesVector.size(); i++) {
        if((incomesVector[i].getID().substr(startID,endID)) == lastDay) {
            lastDate = incomesVector[i].getDate().substr(startDate,endDate) + " " + incomesVector[i].getDate().substr(20,4);
            if(incomesVector[i].getCategory() == "Salary")
                salary += toDouble(incomesVector[i].getAmount());
            else if(incomesVector[i].getCategory() == "Dividend")
                dividend += toDouble(incomesVector[i].getAmount());
            else if(incomesVector[i].getCategory() == "Commission")
                commission += toDouble(incomesVector[i].getAmount());
            else if(incomesVector[i].getCategory() == "Interest")
                interest += toDouble(incomesVector[i].getAmount());
            else if(incomesVector[i].getCategory() == "Others")
                others += toDouble(incomesVector[i].getAmount());
        }
        else {
            cout << "\n\tDate: " << lastDate <<endl;
            cout << "\tSalary: " << salary << endl;
            cout << "\tDividend: " << dividend << endl;
            cout << "\tCommission: " << commission << endl;
            cout << "\tInterest: " << interest << endl;
            cout << "\tOthers: " << others << endl;
            salary=0;
            dividend=0;
            commission=0;
            interest=0;
            others=0;
            lastDay = (incomesVector[i].getID().substr(startID,endID));
            if(incomesVector[i].getCategory() == "Salary")
                salary += toDouble(incomesVector[i].getAmount());
            else if(incomesVector[i].getCategory() == "Dividend")
                dividend += toDouble(incomesVector[i].getAmount());
            else if(incomesVector[i].getCategory() == "Commission")
                commission += toDouble(incomesVector[i].getAmount());
            else if(incomesVector[i].getCategory() == "Interest")
                interest += toDouble(incomesVector[i].getAmount());
            else if(incomesVector[i].getCategory() == "Others")
                others += toDouble(incomesVector[i].getAmount());
            lastDate = incomesVector[i].getDate().substr(startDate,endDate) + " " + incomesVector[i].getDate().substr(20,4);
        }

    }
    cout << "\n\tDate: " << lastDate <<endl;
    cout << "\tSalary: " << salary << endl;
    cout << "\tDividend: " << dividend << endl;
    cout << "\tCommission: " << commission << endl;
    cout << "\tInterest: " << interest << endl;
    cout << "\tOthers: " << others << endl;
    incomesVector.clear();
}


void Wallet::displaySummaryIncome(){
    int choice;
    cout << "What kinds of summary:\n\t1. Daily\n\t2. Monthly\n\t3. Yearly\n\tYour choice: ";
    cin >> choice;
    switch(choice) {
    case 1: {
        processSummaryIncome("Daily");
        break;
        }
    case 2:{
        processSummaryIncome("Monthly");
        break;
        }
    case 3: {
        processSummaryIncome("Yearly");
        break;
        }
    default:
        cout<< "Invalid Option" <<endl;
    }
}
void Wallet::setBudget(){
    cout<< "Enter your budget(It will show warning message when your balance below budget): ";
    cin >> budget;
}
