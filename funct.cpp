#include "funct.h"

funct::funct()
{
    //ctor
}

bool funct::is_emptyf(ifstream& pFile){
    return pFile.peek() == ifstream::traits_type::eof();
}


double funct::toDouble(const string &s) {
    stringstream ss(s);
    double result;
    ss >> result;
    return result;
}

string funct::setTime(){
    time_t now = time(0);
    char* dt = ctime(&now);
    return dt;
}

string funct::to2digit(string s) {
    if(s.length() < 2) {
        return ("0" + s);
    }
    else
        return s;
}



void funct::print(Node *p){
    if(p == NULL){
        return;
    }
    print(p->next);
    cout << p->data << endl;
}
string funct::GetNth(Node *head, int index){
    struct Node* current = head;
    int counter = 0;
    while(current != NULL){
        if(counter == index){
            return current->data;
        }
        counter++;
        current = current->next;
    }
}
void funct::deleteAll(Node** head){
     Node* current = *head;
     Node* next;
     while (current != NULL)
     {
         next = current->next;
         delete current;
         current = next;
     }
     *head = NULL;
}





