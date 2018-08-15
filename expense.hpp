#ifndef EXPENSE_H
#define EXPENSE_H
#include <string>


using namespace std;

class Expense{
private:
    string ID;
    double amount;
    string detail;
    string date;
    string category;

public:
    static int counter;
    void updateCounter();
    Expense();
    ~Expense();
    void add_record(double amount, string detail, string category);
    void remove_record(string id);
    string getID();

};

#endif // EXPENSE_H
