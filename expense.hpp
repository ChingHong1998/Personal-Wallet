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
    void setID(string);
    void setAmount(string);
    void setDetail(string);
    void setDate(string);
    void setCategory(string);
    string getID() ;
    string getAmount() ;
    string getDate() ;
    string getDetail() ;
    string getCategory();
    void display_category();
    string createID();
    void display();
    void remake(string,string,string,string);

};

#endif // EXPENSE_H
