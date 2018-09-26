#include <iostream>
#include <fstream>
#include "wallet.cpp"
#include "funct.cpp"
#include "Expense.cpp"
#include "Income.cpp"
#include "Queue.cpp"
#include "Stack.cpp"
using namespace std;

void display_menu();
Wallet *w1;
int main()
{
        funct f1;
        ifstream fin;
        fin.open("Wallet.txt",ios::in);
        if(f1.is_emptyf(fin)) {
        ofstream fout;
        fout.open("Wallet.txt",ios::app);
        cout<< "Create a wallet.\nEnter your username: ";
        string username;
        getline(cin, username);
        cout << "Enter your balance in your wallet: ";
        double balance;
        cin>> balance;
        cout<< "Enter your budget(It will show warning message when your balance below budget): ";
        double budget;
        cin >> budget;
        cout << "Currency Available:\n 1.Malaysia(RM)\n 2.Singapore(SGD)\n 3.China(RMB)\n 4.Thailand(Baht)\n";
        string currency;
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
        w1 = new Wallet(username,balance,budget,currency);
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
    char con;
    do{
        display_menu();
        cout << "\nContinue (y / n)?" << endl;
        cin >> con;
    }while( con == 'y' || con == 'Y');

}

void display_menu() {
    ifstream fin;
    fin.open("expenses.txt", ios::in);
    ifstream fin2;
    fin2.open("incomes.txt", ios::in);
    system("CLS");
    cout << "\tWelcome to Personal Wallet\n"<<w1->displayUsername()<<"'s current balance is "<< w1->getCurrency()<< w1->displayBalance() <<endl;
    w1->warning();
    cout << "Menu: \n  1. Add Expense. \n  2. Add Income. \n  3. Edit Expense. \n  4. Edit Income \n  5. Delete Expense \n  6. Delete Income \n  7. Display All Expense \n";
    cout << "  8. Display All Income \n  9. Search Expense \n 10. Search Income \n 11. Sort Expense \n 12. Sort Income \n";
    cout << " 13. Search Certain Expense \n 14. Search Certain Income \n 15. Display Chart For Expense \n 16. Display Chart For Income \n";
    cout << " 17. Display Expense Summary \n 18. Display Income Summary \n 19. Change Currency \n 20. Exit" << endl;
    cout << "\nEnter Your Choice: ";
    int option;
    cin>> option;
    switch(option) {
    case 1:
        w1->addExpense();
        break;
    case 2:
        w1->addIncome();
        break;
    case 3:{
        cout << "Enter the date you want to edit: " ;
        string date;
        cin >> date;
        w1->editExpense(date,fin);
        break;
    }
    case 4:{
        cout << "Enter the date you want to edit: ";
        string date;
        cin >> date;
        w1->editIncome(date,fin2);
        break;
    }
    case 5:{
        cout << "Enter the date you want to delete: ";
        string date;
        cin >> date;
        w1->deleteExpense(date,fin);
        break;
    }
    case 6:{
        cout << "Enter the date you want to delete: ";
        string date;
        cin >> date;
        w1->deleteIncome(date,fin2);
        break;
    }
    case 7:{
        w1->displayAll(fin);
        break;
    }
    case 8:{
        w1->displayAll(fin2);
        break;
    }
    case 9:{
        w1->display_record(fin);
        break;
    }
    case 10:{
        w1->display_record(fin2);
        break;
    }
    case 11:{
        cout << "Sort \n 1) Amount (Ascending) \n 2) Amount (Descending) \n 3) Date (Ascending) \n 4) Date (Ascending)" << endl;
        int choice;
        cin>>choice;
        switch(choice){
            case 1:
                w1->sort_expense_amount(choice);
                break;
            case 2:
                w1->sort_expense_amount(choice);
                break;
            case 3:
                w1->sort_expense_date(choice);
                break;
            case 4:
                w1->sort_expense_date(choice);
                break;
        }
        break;
    }
    case 12:{
        cout << "Sort \n 1) Amount (Ascending) \n 2) Amount (Descending) \n 3) Date (Ascending) \n 4) Date (Ascending)" << endl;
        int choice;
        cin>>choice;
        switch(choice){
            case 1:
                w1->sort_income_amount(choice);
                break;
            case 2:
                w1->sort_income_amount(choice);
                break;
            case 3:
                w1->sort_income_date(choice);
                break;
            case 4:
                w1->sort_income_date(choice);
                break;
        }
        break;
    }
    case 13:{
        cout << "DATE OR AMOUNT \n 1. Amount \n 2. Date" <<endl;
        int choice;
        cin>> choice;
        switch(choice){
            case 1:
                w1->search2_expense();
                break;
        }
        break;
    }
    case 14:{
        cout << "DATE OR AMOUNT \n 1. Amount \n 2. Date" <<endl;
        int choice;
        cin>> choice;
        switch(choice){
            case 1:
                w1->search2_income();
                break;
        }
        break;
    }
    case 15:
        w1->ChartExpense();
        break;
    case 16:
        w1->ChartIncome();
        break;
    case 17:
        w1->displaySummaryExpense();
        break;
    case 18:
        w1->displaySummaryIncome();
        break;
    case 19:
        fin.close();
        fin2.close();
        w1->changeCurrency();
        w1->update_data();
        break;
    case 20:
        exit(0);
    default:
        cout << "\nInvalid option."<<endl;
    }
}
