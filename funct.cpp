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
bool funct::isNotValidInt(const std::string& x)
{
    bool condition = false;
    for(int i = 0; i < x.length(); i++){
        if(!isdigit(x[i])){
            condition = true;
            break;
        }
        if(isspace(x[i])) {
            condition = true;
            break;
        }
    }
    if(condition){
        cout << "Invalid. Enter again: ";
    }
    return condition;
}


void funct::print(Node *p, int counter){
    string category[5] = {"ID","Date","Amount","Category","Detail"};
    if(p == NULL){
        return;
    }
    print(p->next,counter - 1);
    cout << "\t" << category[counter] << ": " << p->data << endl;
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
void funct::IntOnly(int x)
{
        cout << "Please enter a valid integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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





