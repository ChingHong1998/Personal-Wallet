#ifndef WALLET_H
#define WALLET_H
#include<string>
using namespace std;
class Wallet {
public:
    Wallet(string name, double bal);
    ~Wallet();
    void addExpense();
    void addIncome();
    void deleteExpense(string Date);
    void deleteIncome(string Date);
    void editExpense(string Date);
    void editIncome(string Date);
    void search(string Date);
    void sort();
    double displayBalance();
    string displayUsername();
    void displaySummary();
    void warning();
    void displayChart();
    void setBudget();
    void changeCurrency();
    bool isEnough(double amount);
    void update_data();
    void display_record(ifstream &filen1);
private:
    string username;
    double balance;
};

#endif // WALLET_H


