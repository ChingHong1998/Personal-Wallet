#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include "income.hpp"

using namespace std;

int Income::counter = 0;



Income::Income() {
    updateCounter();
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
    fout.open("incomes.txt",ios::app);
    if(fout.good()) {
        fout << getID()<<"\n";
        fout << setTime();
        fout << amount <<"\n";
        fout << detail<<"\n";
        fout << category << "\n";
    }
    cout << "\nSuccess! ";
}

void Income::remove_record(string id) {}

void Income::updateCounter() {
    ifstream fin;
    fin.open("incomes.txt",ios::in);
    int i=1;
    string temp;
    if(is_emptyf(fin)) {
        Income::counter = 1;
        return;
    }
    while(!fin.eof()&& (fin.good())) {
        getline(fin, temp);
        i++;
    }
    Income::counter = (i / 5) + 1;
    fin.close();
}

