#ifndef WALLET_H
#define WALLET_H
#include<string>
using namespace std;
class Wallet {
public:
    Wallet();
    ~Wallet();
    void addExpense();
    void addIncome(float Amount,  string Date, string Detail, int Category);
    void deleteExpense(string Date);
    void deleteIncome(string Date);
    void editExpense(string Date);
    void editIncome(string Date);
    void search(string Date);
    void sort();
    void displayBalance();
    void displaySummary();
    void warning();
    void displayChart();
    void setBudget();
    void changeCurrency();

private:
    double balance;
};

#endif // WALLET_H


