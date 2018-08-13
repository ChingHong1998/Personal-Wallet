#include<iostream>
#include<cstdlib>
#include <fstream>
#include "wallet.cpp"

void display_menu();

Wallet *w1;

bool is_emptyf(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

int main() {
    ifstream fin;
    fin.open("Wallet.txt",ios::in);
    if(is_emptyf(fin)) {
        ofstream fout;
        fout.open("Wallet.txt",ios::app);
        cout<< "Create a wallet.\nEnter your username: ";
        string username;
        cin >> username;
        cout << "Enter your balance in your wallet.";
        double balance;
        cin>> balance;
        w1 = new Wallet(username,balance);
        fout << "Username: "<< username <<endl;
        fout << "Balance: " << balance <<endl;
    }
    else {
        while(!fin.eof()&& (fin.good()))
        {
            string username;
            double balance;
            fin >> username;
            string temp;
            fin >> temp;
            stringstream ss(temp);
            ss >> balance;
            w1 = new Wallet(username,balance);
        }
    }
    display_menu();
}

void display_menu() {
    system("CLS");
    cout << "Welcome to Personal Wallet.\n"<<w1->displayUsername()<<" current balance is "<< w1->displayBalance() <<endl;
    cout << "Menu: \n 1. Add Expense. \n 2. Add Income \n ";
    int option;
    cin>> option;
    switch(option) {
    case 1:
        w1->addExpense();
        break;
    default:
        cout << "\nInvalid option."<<endl;
    }
}
