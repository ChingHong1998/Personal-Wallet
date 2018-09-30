#include "Queue.h"

Queue::Queue() : backPtr(NULL), frontPtr(NULL) {}
Queue::~Queue() {
    while (!isEmpty())
        dequeue();
}

bool Queue::isEmpty() {
    return (frontPtr == NULL);
}

void Queue::enqueue(QueueItemType newItem) {
    QueueNode* newNode = new QueueNode;
    newNode->item = newItem;
    newNode->next = NULL;
    if(isEmpty()) {
        frontPtr = newNode;
    }
    else {
        backPtr->next = newNode;

    }
    backPtr = newNode;
}

void Queue::dequeue(){
    if(isEmpty()) {
        cout<< "The queue is empty."<<endl;
    }
    else {
        QueueNode* tempPtr = frontPtr;
        if(frontPtr == backPtr){
            frontPtr = NULL;
            backPtr = NULL;
        }
        else{
            frontPtr = frontPtr->next;
        }
        tempPtr->next = NULL;
        delete tempPtr;
    }
}

QueueItemType Queue::getFront() {
    if(isEmpty()) {
        cout << "Queue is Empty!"<<endl;
        return "";
    }
    else
        return frontPtr->item;
}
