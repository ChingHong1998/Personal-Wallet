#include <iostream>
#include <fstream>
#include "wallet.cpp"
#include "funct.cpp"
#include "Expense.cpp"
#include "Income.cpp"
#include "Queue.cpp"
#include "Stack.cpp"
using namespace std;

void display_menu(), expense_menu(), income_menu();
Wallet *w1;
funct f1;

int main()
{
        ifstream fin;
        string username,balance, budget,currency;
        fin.open("Wallet.txt",ios::in);
        if(f1.is_emptyf(fin)) {
        ofstream fout;
        fout.open("Wallet.txt",ios::app);
        cout<< "Create a wallet.\nEnter your username: ";
        getline(cin, username);
        cout << "Enter your balance in your wallet: ";
        do {
            getline(cin, balance);
        }while(f1.isNotValidInt(balance));
        cout<< "Enter your budget(It will show warning message when your balance below budget): ";
        do {
            getline(cin, budget);
        }while(f1.isNotValidInt(budget));
        cout << "Currency Available:\n 1.Malaysia(RM)\n 2.Singapore(SGD)\n 3.China(RMB)\n 4.Thailand(Baht)\n";
        cout <<"Enter your currency unit: ";
        int unit;
        cin >> unit;
        switch(unit)
        {
        case 1:
            currency = "RM  ";
            break;
        case 2:
            currency = "SGD ";
            break;
        case 3:
            currency = "RMB ";
            break;
        case 4:
            currency = "BAHT";
            break;
        default:
            cout <<" Please choose from the available option: ";
        }
        w1 = new Wallet(username,f1.toDouble(balance),f1.toDouble(budget),currency);
        fout << "Username: "<< username <<endl;
        fout << "Balance: " << balance <<endl;
        fout << "Budget: " << w1->getBudget() << endl;
        fout << "Currency: " << currency <<endl;
        fout.close();
    }
    else {
        string username = "";
        string balance="";
        string budget = "";
        string currency = "";
        while(!fin.eof()&& (fin.good()))
        {
            string temp;
            getline(fin,temp);
            for(int i = 10; i< temp.length(); i++) {
                username += temp[i];
            }
            getline(fin,temp);
            for(int i = 9; i< temp.length(); i++) {
                balance += temp[i];
            }
            getline(fin,temp);
            for(int i = 8; i< temp.length(); i++) {
                budget += temp[i];
            }
            getline(fin,temp);
            for(int i = 10; i< temp.length(); i++) {
                currency += temp[i];
            }
        }
        w1 = new Wallet(username,f1.toDouble(balance),f1.toDouble(budget),currency);
    }
    fin.close();
    string option;
    do {
        display_menu();
        cout << "\nDo you want to continue?[Y/N]\nYour Option>";
        cin>>option;
    }while(option == "y" || option == "Y");
}

void display_menu() {
    system("CLS");
    cout << "\tWelcome to Personal Wallet\n"<<w1->displayUsername()<<"'s current balance is "<< w1->getCurrency()<< w1->displayBalance() <<endl;
    int choice;
    w1->warning();
    cout << "\nDo you wish to choose expense, income or change currency?" << endl;
    cout << "[1] Expense" << endl;
    cout << "[2] Income" << endl;
    cout << "[3] Change currency" << endl;
    cout << "[4] Exit" << endl;
    cout<<string(50, '.')<<endl;
    cout << "Which option would you like to choose? : ";
    while(!(cin>>choice)){
        f1.IntOnly(choice);
    }
    switch(choice){
        case 1:
            expense_menu();
            break;
        case 2:
            income_menu();
            break;
        case 3:
            w1->changeCurrency();
            w1->update_data();
            break;
        case 4:
            exit(0);
            break;
        default:
            cerr << "YOU ENTER AN INVALID CHOOSE !!" << endl;
    }
}

void expense_menu(){
    system("cls");
    ifstream fin;
    fin.open("expenses.txt", ios::in);
    cout << "Expense Category....." << endl;
    cout << "Main Menu" << endl;
    int choice2, choose3;
    cout << " [1] Add Expense\n [2] Edit Expense\n [3] Delete Expense\n [4] Display All Expense\n [5] Search Expense\n [6] Sort Expense\n [7] Expense Chart\n [8] Summarize Expense\n [9] Back" << endl;
    cout<<string(50, '.')<<endl;
    cout << "Which option would you like to choose? : ";
    while(!(cin>>choice2)){
        f1.IntOnly(choice2);
    }
    switch(choice2){
        case 1:
            w1->addExpense();
            break;
        case 2:
            w1->editExpense(fin);
            break;
        case 3:
            w1->deleteExpense(fin);
            break;
        case 4:
            w1->displayAll(fin);
            break;
        case 5:{
            cout<<string(50, '.')<<endl;
            cout << "You Are Currently Searching The Expense Record...." << endl;
            cout<<string(50, '.')<<endl;
            cout << "May you please choose a searching method?" << endl << endl;
            cout << " [1] Specified Date\n [2] Specified Day\n [3] Specified Month\n [4] Specified Year\n [5] Range of Date\n [6] Range of Amount "<< endl;
            cout<<string(50, '.')<<endl;
            cout << "Which option would you like to choose? : ";
            while(!(cin >> choose3)){
                f1.IntOnly(choose3);
            }
            switch(choose3){
                case 1:
                    cout << "Enter the day you want to display[DDMMYY]: ";
                    w1->display_day_record(fin);
                    break;
                case 2:
                    w1->display_record(fin,choose3);
                    break;
                case 3:
                    w1->display_record(fin,choose3);
                    break;
                case 4:
                    w1->display_record(fin,choose3);
                    break;
                case 5:
                    w1->search_expense();
                    break;
                case 6:
                    w1->search2_expense();
                    break;
                default:
                    cerr << "YOU ENTER AN INVALID CHOOSE !!" << endl;
            }
            break;
        }
        case 6:{
            cout<<string(50, '.')<<endl;
            cout << "You Are Currently Sorting The Expense Record...." << endl;
            cout<<string(50, '.')<<endl;
            cout << "May you please choose a sorting method?" << endl;
            cout << " [1] Amount (Descending)\n [2] Amount (Ascending)\n [3] Date (Descending)\n [4] Date (Ascending)" << endl;
            cout<<string(50, '.')<<endl;
            cout << "Which option would you like to choose? : ";
            cin >> choose3;
            switch(choose3){
                case 1:
                    w1->sort_expense_amount(choose3);
                    break;
                case 2:
                    w1->sort_expense_amount(choose3);
                    break;
                case 3:
                    w1->sort_expense_date(choose3);
                    break;
                case 4:
                    w1->sort_expense_date(choose3);
                    break;
                default:
                    cerr << "PLEASE ENTER AN VALID CHOOSE !!" << endl;
            }
            cin.ignore();
            break;
        }
        case 7:
            cout<<string(50, '.')<<endl;
            cout << "You Are Currently Displaying The Expense Chart...." << endl;
            w1->ChartExpense();
            break;
        case 8:
            cout<<string(50, '.')<<endl;
            cout << "You Are Currently Displaying The Expense Summary...." << endl;
            w1->displaySummaryExpense();
            break;
        case 9:
            system("CLS");
            display_menu();
            break;
        default:
            cerr << "YOU ENTER AN INVALID CHOOSE !!" << endl;
    }
    fin.close();
}

void income_menu(){
    system("cls");
    ifstream fin;
    fin.open("incomes.txt", ios::in);
    cout << "Income Category....." << endl;
    cout << "Main Menu" << endl;
    int choice2, choose3;
    cout << " [1] Add Income\n [2] Edit Income\n [3] Delete Income\n [4] Display All Income\n [5] Search Income\n [6] Sort Income\n [7] Income Chart\n [8] Summarize Income\n [9] Back" << endl;
    cout<<string(50, '.')<<endl;
    cout << "Which option would you like to choose? : ";
    while(!(cin>>choice2)){
        f1.IntOnly(choice2);
    }
    switch(choice2){
        case 1:
            w1->addIncome();
            break;
        case 2:
            w1->editIncome(fin);
            break;
        case 3:
            w1->deleteIncome(fin);
            break;
        case 4:
            w1->displayAll(fin);
            break;
        case 5:{
            cout<<string(50, '.')<<endl;
            cout << "You Are Currently Searching The Income Record...." << endl;
            cout<<string(50, '.')<<endl;
            cout << "May you please choose a searching method?" << endl << endl;
            cout << " [1] Specified Date\n [2] Specified Day\n [3] Specified Month\n [4] Specified Year\n [5] Range of Day\n [6] Range of Amount" << endl;
            cout<<string(50, '.')<<endl;
            cout << "Which option would you like to choose? : ";
            while(!(cin >> choose3)){
                f1.IntOnly(choose3);
            }
            switch(choose3){
                case 1:
                    cout << "Enter the day you want to display[DDMMYY]: ";
                    w1->display_day_record(fin);
                    break;
                case 2:
                    w1->display_record(fin,choose3);
                    break;
                case 3:
                    w1->display_record(fin,choose3);
                    break;
                case 4:
                    w1->display_record(fin,choose3);
                    break;
                case 5:
                    w1->search_income();
                    break;
                case 6:
                    w1->search2_income();
                    break;
                default:
                    cerr << "YOU ENTER AN INVALID CHOOSE !!" << endl;
            }
            break;
        }
        case 6:{
            cout<<string(50, '.')<<endl;
            cout << "You Are Currently Sorting The Income Record...." << endl;
            cout<<string(50, '.')<<endl;
            cout << "May you please choose a sorting method?" << endl;
            cout << " [1] Amount (Descending)\n [2] Amount (Ascending)\n [3] Date (Descending)\n [4] Date (Ascending)" << endl;
            cout<<string(50, '.')<<endl;
            cout << "Which option would you like to choose? : ";
            cin >> choose3;
            switch(choose3){
                case 1:
                    w1->sort_income_amount(choose3);
                    break;
                case 2:
                    w1->sort_income_amount(choose3);
                    break;
                case 3:
                    w1->sort_income_date(choose3);
                    break;
                case 4:
                    w1->sort_income_date(choose3);
                    break;
                default:
                    cerr << "PLEASE ENTER AN VALID CHOOSE !!" << endl;
            }
            cin.ignore();
            break;
        }
        case 7:
            cout<<string(50, '.')<<endl;
            cout << "You Are Currently Displaying The Income Chart...." << endl;
            w1->ChartIncome();
            break;
        case 8:
            cout<<string(50, '.')<<endl;
            cout << "You Are Currently Displaying The Income Summary...." << endl;
            w1->displaySummaryIncome();
            break;
        case 9:
            system("CLS");
            display_menu();
            break;
        default:
            cerr << "YOU ENTER AN INVALID CHOOSE !!" << endl;
    }
    fin.close();

}
