#include<iostream>
#include "wallet.cpp"

int main() {
    Wallet w1;
    cout<< "Welcome!\nEnter 1 to add expense.";
    int option;
    cin >> option;
    if(option == 1) {
        w1.addExpense();
    }

}
