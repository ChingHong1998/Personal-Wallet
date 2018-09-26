#include "Stack.h"

Stack::Stack() : topPtr(NULL) { }

// Copy constructor, Deep copy
Stack::Stack(const Stack& aStack) {
    if (aStack.topPtr == NULL)
        topPtr = NULL; // original list is empty
    else { // copy first node
        topPtr = new StackNode;
        topPtr->item = aStack.topPtr->item;
        // copy rest of list
        StackNode *newPtr = topPtr; // new node pointer
        for (StackNode *origPtr = aStack.topPtr->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new StackNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = NULL; //tail
    }
}

Stack::~Stack() {
    // pop until stack is empty
    while (!isEmpty())
        pop();
    // Assertion:topPtr == NULL;
}

bool Stack::isEmpty() const {
    return topPtr == NULL;
}
void Stack::push(const StackItemType& newItem) {
    // create a new node
    try {
        StackNode *newPtr = new StackNode;
        newPtr->item = newItem; // insert the new node
        newPtr->next = topPtr; //newPtr->next pointer points to topPtr
        topPtr = newPtr;
    }
    catch (bad_alloc e) {
        cout<<"StackException: push cannot allocate memory."<<endl;
    }
}

void Stack::pop(){
    if (isEmpty())
        cout << "StackException: stack empty on pop"<<endl;
    else {
        // stack is not empty;delete top
        StackNode *temp = topPtr;
        topPtr = topPtr->next;
        // return deleted node to system
        // safeguard, don't point anything, points to nothing
        temp->next = NULL;
        delete temp;
    }
}

void Stack::pop(StackItemType& stackTop){
    if (isEmpty())
        cout << "StackException: stack empty on pop"<<endl;
    else {
        // stack is not empty; retrieve and delete top
        stackTop = topPtr->item;
        StackNode *temp = topPtr;
        topPtr = topPtr->next;
        // return deleted node to system
        temp->next = NULL; // safeguard, points to nothing
        delete temp;
    }
}

StackItemType Stack::getTop() {
    if (isEmpty())
        cout << "StackException: stack empty on getTop"<<endl;
    else // stack is not empty; retrieve top
        return topPtr->item;
}
