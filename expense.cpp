#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include "expense.hpp"

using namespace std;

int Expense::counter = 0;

template <typename T> string tostr(const T& t) {
   ostringstream os;
   os<<t;
   return os.str();
}

string to2digit(string s) {
    if(s.length() < 2) {
        return ("0" + s);
    }
    else
        return s;
}

string setTime()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    return dt;
}

Expense::Expense() {
    counter++;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    float year = 1900 + ltm->tm_year - 2000;
    float month = 1 + ltm->tm_mon;
    float day = ltm->tm_mday;
    string y = tostr(year);
    string m = to2digit(tostr(month));
    string d = to2digit(tostr(day));
    string c = tostr(counter);
    this->ID = d+m+y+c;
}
Expense::~Expense() {}

string Expense::getID() {
    return this->ID;
}



void Expense::add_record(double amount, string detail, string category) {
    ofstream fout;
    fout.open("expenses.txt",ios::app);
    if(fout.good()) {
        fout << setTime();
        fout << getID()<<"\n";
        fout << amount <<"\n";
        fout << detail<<"\n";
        fout << category << "\n";
    }
    cout << "\nSuccess! ";
}

void Expense::remove_record(string id) {

}



