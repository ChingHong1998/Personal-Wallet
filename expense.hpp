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
    Expense();
    ~Expense();
    void add_record(double amount, string detail, string category);
    void remove_record(string id);
    string getID();
    void setID(string);
    void setAmount(string);
    void setDetail(string);
    void setDate(string);
    void setCategory(string);
    void display_category();
    string createID();

};

#endif // EXPENSE_H
