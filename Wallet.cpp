#include "wallet.h"

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
    system("cls");
    cout << "You Are Currently Adding An Expense Record...." << endl;
    Expense * expense = new Expense;
    cout<<"Enter Your Amount: ";
    double amount;
    cin >> amount;
    if(isEnough(amount)) {
        cin.ignore();
        cout<<"Category : "<<endl;
        expense->display_category();
        cout<<"Enter Your Category: ";
        string category;
        getline(cin,category);
        cout<<"Enter The Detail: ";
        string detail;
        getline(cin,detail);
        expense->add_record(amount,detail,category);
        cout << "\nAdded!";
        balance -= amount;
        update_data();
    }
    else
        cout<< "Not enough balance"<<endl;
}

void Wallet::addIncome(){
    system("cls");
    Income * income = new Income;
    cout << "You Are Currently Adding An Income Record...." << endl;
    cout<<"Enter Your Amount: ";
    double amount;
    cin >> amount;
    cin.ignore();
    cout<<"Category: " << endl;
    income->display_category();
    cout << "Enter Your Category: ";
    string category;
    getline(cin, category);
    cout<<"Enter The Detail: ";
    string detail;
    getline(cin, detail);
    income->add_record(amount,detail,category);
    cout << "\nAdded!";
    balance += amount;
    update_data();
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
    temp << "Currency: " << currency <<endl;
    temp.close();
    remove("Wallet.txt");
    rename("temp.txt", "Wallet.txt");
}

void Wallet::editExpense(string Date, ifstream &filen1){
    Expense *expense = new Expense();
    vector <Expense> expensesVector = expense->returnExpensesVector();
    system("CLS");
    display_record(filen1,Date);
    cout << "Enter the ID You want to Edit: ";
    string id;
    cin.ignore();
    getline(cin,id);
    for(int i = 0; i<expensesVector.size();i++) {
        if(expensesVector[i].getID() == id) {
            balance += toDouble(expensesVector[i].getAmount());
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
            balance -= toDouble(amount);
            break;
        }
    }
    expense->saveBack(expensesVector);
    expensesVector.clear();
    cout<<"Edit success";
    update_data();
}
void Wallet::editIncome(string Date, ifstream &filen1){
    Income *income = new Income();
    vector <Income> expensesVector = income->returnExpensesVector();
    system("CLS");
    display_record(filen1,Date);
    cout << "Enter the ID You want to Edit: ";
    string id;
    cin.ignore();
    getline(cin,id);
    for(int i = 0; i<expensesVector.size();i++) {
        if(expensesVector[i].getID() == id) {
            balance -= toDouble(expensesVector[i].getAmount());
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
            balance += toDouble(amount);
            break;
        }
    }
    income->saveBack(expensesVector);
    expensesVector.clear();
    cout<<"Edit success";
    update_data();
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

void Wallet::deleteExpense(string Date, ifstream& fin){
    Expense *expense = new Expense();
    vector<Expense> expensesVector = expense->returnExpensesVector();
    string id;
    display_record(fin,Date);
    cout << "Enter the ID You want to delete: ";
    cin.get();
    getline(cin,id);
    for(int i = 0; i< expensesVector.size();i++) {
        if(id == expensesVector[i].getID()) {
            balance += toDouble(expensesVector[i].getAmount());
            expensesVector.erase(expensesVector.begin()+i);
            break;
        }
    }
    expense->saveBack(expensesVector);
    expensesVector.clear();
    cout << "Deleted.\n";
    update_data();
}

void Wallet::deleteIncome(string Date, ifstream& fin){
    Income *income = new Income();
    vector<Income> expensesVector = income->returnExpensesVector();
    string id;
    display_record(fin,Date);
    cout << "Enter the ID You want to delete: ";
    cin.get();
    getline(cin,id);
    for(int i = 0; i< expensesVector.size();i++) {
        if(id == expensesVector[i].getID()) {
            balance -= toDouble(expensesVector[i].getAmount());
            expensesVector.erase(expensesVector.begin()+i);
            break;
        }
    }
    income->saveBack(expensesVector);
    expensesVector.clear();
    cout << "Deleted.\n";
    update_data();
}

void Wallet::displayAll(ifstream &fin) {
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

void Wallet::sort_expense_amount(int sort_choice){
        Expense *expense = new Expense();
        vector <Expense> expensesVector = expense->returnExpensesVector();
        expense->mergeSort(expensesVector, 0, expensesVector.size() - 1, sort_choice);
        for(int i = 0; i < expensesVector.size(); i++){
            cout << expensesVector[i].getID() << endl;
            cout << expensesVector[i].getDate() << endl;
            cout << expensesVector[i].getAmount() << endl;
            cout << expensesVector[i].getCategory() << endl;
            cout << expensesVector[i].getDetail() << endl;
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
            cout << expensesVector[i].getID() << endl;
            cout << expensesVector[i].getDate() << endl;
            cout << expensesVector[i].getAmount() << endl;
            cout << expensesVector[i].getCategory() << endl;
            cout << expensesVector[i].getDetail() << endl;
        }
        expensesVector.clear();
        cout << "Sorted" << endl;
}

void Wallet::sort_income_amount(int sort_choice){
        Income *income = new Income();
        vector <Income> expensesVector = income->returnExpensesVector();
        income->mergeSort(expensesVector, 0, expensesVector.size() - 1, sort_choice);
        for(int i = 0; i < expensesVector.size(); i++){
            cout << expensesVector[i].getID() << endl;
            cout << expensesVector[i].getDate() << endl;
            cout << expensesVector[i].getAmount() << endl;
            cout << expensesVector[i].getCategory() << endl;
            cout << expensesVector[i].getDetail() << endl;
        }
}

void Wallet::sort_income_date(int sort_choice){
    Income *income = new Income();
    vector <Income> expensesVector = income->returnExpensesVector();
    Income temparr[1];
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
            cout << expensesVector[i].getID() << endl;
            cout << expensesVector[i].getDate() << endl;
            cout << expensesVector[i].getAmount() << endl;
            cout << expensesVector[i].getCategory() << endl;
            cout << expensesVector[i].getDetail() << endl;
        }
        expensesVector.clear();
        cout << "Sorted" << endl;
}

void Wallet::search_expense(){
    Expense *expense = new Expense;
    string start_pt, end_pt;
    int start = 0, ending = 0;
    cout << "Enter the date you want to search in [DDMMYY]: \nFrom: ";
    cin >> start_pt;
    start_pt = start_pt + "1";
    cout << "Until: ";
    cin >> end_pt;
    vector <Expense> vec = expense->returnExpensesVector();
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
void Wallet::search2_expense(){
    Expense *expense = new Expense();
    vector <Expense> vec = expense->returnExpensesVector();
    expense->mergeSort(vec, 0, vec.size() - 1, 1);
    cout << "Enter the amount you want to search: \n From: ";
    int start_amount, end_amount, start, ending;
    cin >> start_amount;
    cout << " Until: ";
    cin >> end_amount;
    start = expense->leftmost(vec, 0, vec.size() - 1, start_amount);
    ending = expense->rightmost(vec, 0, vec.size() - 1, end_amount);
    for(int i = start; i <= ending; i++){
        cout << vec[i].getID() << endl;
        cout << vec[i].getDate() << endl;
        cout << vec[i].getAmount() << endl;
        cout << vec[i].getCategory() << endl;
        cout << vec[i].getDetail() << endl;
    }
}
void Wallet::search_income(){
    Income *income = new Income;
    string start_pt, end_pt;
    int start = 0, ending = 0;
    cout << "Enter the date you want to search in [DDMMYY]: \nFrom: ";
    cin >> start_pt;
    start_pt = start_pt + "1";
    cout << "Until: ";
    cin >> end_pt;
    vector <Income> vec = income->returnExpensesVector();
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
void Wallet::search2_income(){
    Income *income = new Income();
    vector <Income> vec = income->returnExpensesVector();
    income->mergeSort(vec, 0, vec.size() - 1, 1);
    cout << "Enter the amount you want to search: \n From: ";
    int start_amount, end_amount, start, ending;
    cin >> start_amount;
    cout << " Until: ";
    cin >> end_amount;
    start = income->leftmost(vec, 0, vec.size() - 1, start_amount);
    ending = income->rightmost(vec, 0, vec.size() - 1, end_amount);
    for(int i = start; i <= ending; i++){
        cout << vec[i].getID() << endl;
        cout << vec[i].getDate() << endl;
        cout << vec[i].getAmount() << endl;
        cout << vec[i].getCategory() << endl;
        cout << vec[i].getDetail() << endl;
    }
}
void Wallet::ChartExpense(){
    system("cls");
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
    system("cls");
    Income *income = new Income();
    string x[5] = {"Salary", "Dividend", "Commission", "Interest", "Others"};
    vector <Income> vec = income->returnExpensesVector();
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
    vector<Income> exVector2 = income->returnExpensesVector();
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
    vector<Income> expensesVector = income->returnExpensesVector();
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
    for(lastDay= (expensesVector[i].getID().substr(startID,endID));i < expensesVector.size(); i++) {
        if((expensesVector[i].getID().substr(startID,endID)) == lastDay) {
            lastDate = expensesVector[i].getDate().substr(startDate,endDate) + " " + expensesVector[i].getDate().substr(20,4);
            if(expensesVector[i].getCategory() == "Salary")
                salary += toDouble(expensesVector[i].getAmount());
            else if(expensesVector[i].getCategory() == "Dividend")
                dividend += toDouble(expensesVector[i].getAmount());
            else if(expensesVector[i].getCategory() == "Commission")
                commission += toDouble(expensesVector[i].getAmount());
            else if(expensesVector[i].getCategory() == "Interest")
                interest += toDouble(expensesVector[i].getAmount());
            else if(expensesVector[i].getCategory() == "Others")
                others += toDouble(expensesVector[i].getAmount());
        }
        else {
            cout << "\nDate: " << lastDate <<endl;
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
            lastDay = (expensesVector[i].getID().substr(startID,endID));
            if(expensesVector[i].getCategory() == "Salary")
                salary += toDouble(expensesVector[i].getAmount());
            else if(expensesVector[i].getCategory() == "Dividend")
                dividend += toDouble(expensesVector[i].getAmount());
            else if(expensesVector[i].getCategory() == "Commission")
                commission += toDouble(expensesVector[i].getAmount());
            else if(expensesVector[i].getCategory() == "Interest")
                interest += toDouble(expensesVector[i].getAmount());
            else if(expensesVector[i].getCategory() == "Others")
                others += toDouble(expensesVector[i].getAmount());
            lastDate = expensesVector[i].getDate().substr(startDate,endDate) + " " + expensesVector[i].getDate().substr(20,4);
        }

    }
    cout << "\nDate: " << lastDate <<endl;
    cout << "\tSalary: " << salary << endl;
    cout << "\tDividend: " << dividend << endl;
    cout << "\tCommission: " << commission << endl;
    cout << "\tInterest: " << interest << endl;
    cout << "\tOthers: " << others << endl;
    expensesVector.clear();
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
