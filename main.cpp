#include<iostream>
#include<cstdlib>
#include <fstream>
#include "wallet.cpp"

void display_menu();
void check_account(Wallet *wallet);

Wallet *w1;


int main() {
    ifstream fin;
    fin.open("Wallet.txt",ios::in);
    if(is_emptyf(fin)) {
        ofstream fout;
        fout.open("Wallet.txt",ios::app);
        cout<< "Create a wallet.\nEnter your username: ";
        string username;
        cin >> username;
        cout << "Enter your balance in your wallet: ";
        double balance;
        cin>> balance;
        w1 = new Wallet(username,balance);
        fout << "Username: "<< username <<endl;
        fout << "Balance: " << balance <<endl;
        fout.close();
    }
    else {
        string username = "";
        double balance;
        while(!fin.eof()&& (fin.good()))
        {
            string temp;
            getline(fin,temp);
            for(int i = 10; i< temp.length(); i++) {
                username += temp[i];
            }
            fin >> temp;
            stringstream ss(temp);
            ss >> balance;
        }
        w1 = new Wallet(username,balance);
    }
    fin.close();
    display_menu();
}

void display_menu() {
    ifstream fin;
    fin.open("expenses.txt", ios::in);
    ifstream fin2;
    fin2.open("incomes.txt", ios::in);
    system("CLS");
    cout << "Welcome to Personal Wallet.\n"<<w1->displayUsername()<<" current balance is "<< w1->displayBalance() <<endl;
    cout << "Menu: \n 1. Add Expense. \n 2. Add Income \n 3. Display Expense \n 4. Display Income \nEnter Your choice: ";
    int option;
    cin>> option;
    switch(option) {
    case 1:
        w1->addExpense();
        break;
    case 2:
        w1->addIncome();
        break;
    case 3:
        w1->display_record(fin);
        break;
    case 4:
        w1->display_record(fin2);
        break;
    default:
        cout << "\nInvalid option."<<endl;
    }
}

void check_account(Wallet *wallet) {

}



