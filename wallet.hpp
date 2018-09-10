#ifndef WALLET_H
#define WALLET_H
#include<string>
using namespace std;
class Wallet {
public:
    Wallet(string name, double bal,double bud);
    ~Wallet();
    void addExpense();
    void addIncome();
    void deleteExpense(string Date,ifstream &fin);
    void deleteIncome(string Date);
    void editExpense(string Date);
    void editIncome(string Date);
    void search();
    void search2();
    void sort(int sort_choice);
    double displayBalance();
    string displayUsername();
    void displaySummary();
    void warning();
    void displayChart();
    void setBudget();
    void changeCurrency();
    bool isEnough(double amount);
    void update_data();
    void display_all_expenses();
    void display_record(ifstream &filen1);
    void display_record(ifstream &filen1,string choose2);
    string getBudget();
private:
    string username;
    double balance;
    double budget;
};

#endif // WALLET_H


