
struct Node{
    string data;
    Node* next;
};
Node *Insert(Node *head, string x){
    Node *temp = new Node();
    temp->data = x;
    temp->next = head;
    head = temp;
    return head;
}

void print(Node *p){
    if(p == NULL){
        return;
    }
    print(p->next);
    cout << p->data << endl;
}
string GetNth(Node *head, int index){
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
void deleteAll(Node** head)
{
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
