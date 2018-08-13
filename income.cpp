#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include "income.hpp"

using namespace std;

int Income::counter = 0;



Income::Income() {
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
Income::~Income() {}

string Income::getID() {
    return this->ID;
}



void Income::add_record(double amount, string detail, string category) {
    ofstream fout;
    fout.open("income.txt",ios::app);
    if(fout.good()) {
        fout << setTime();
        fout << getID()<<"\n";
        fout << amount <<"\n";
        fout << detail<<"\n";
        fout << category << "\n";
    }
    cout << "\nSuccess! ";
}

void Income::remove_record(string id) {}


