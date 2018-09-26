#ifndef FUNCT_H
#define FUNCT_H
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
struct Node{
    string data;
    Node* next;
};
class funct
{
    public:
        funct();
        bool is_emptyf(ifstream& pFile);
        double toDouble(const string &s);
        string setTime();
        string to2digit(string s);
        template<typename T> string tostr(const T &t){
            ostringstream os;
            os<<t;
            return os.str();
        };
        Node *Insert(Node *head, string x){
            Node *temp = new Node();
            temp->data = x;
            temp->next = head;
            head = temp;
            return head;
        }
        void print(Node *p);
        string GetNth(Node *head, int index);
        void deleteAll(Node** head);
    private:
};

#endif // FUNCT_H
