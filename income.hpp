#ifndef INCOME_H
#define INCOME_H
#include <string>

using namespace std;

class Income {
private:
    string ID;
    double amount;
    string detail;
    string date;
    string category;

public:
    static int counter;
    Income();
    ~Income();
    void add_record(double amount, string detail, string category);
    void remove_record(string id);
    string getID();

};

#endif // INCOME_H
