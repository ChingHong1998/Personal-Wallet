#include "Queue.h"

Queue::Queue() : backPtr(NULL), frontPtr(NULL) {}
Queue::~Queue() {
    while (!isEmpty())
        dequeue();
}

bool Queue::isEmpty() {
    // TODO: Fill in your code here
    return (frontPtr == NULL);
}

void Queue::enqueue(QueueItemType newItem) {
    // HINT: // (a) Create a new node to store the new item
    // (b) If the queue is empty, the front pointer will point
    // to the new node. Otherwise, the back pointer's next pointer
    // will point to the new node
    // (c) Assign the back pointer to the new node
    // TODO: Fill in your code here
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
    // HINT: // (a) Check whether the queue is empty
    // (b) Remove the front item of the queue if it's not empty
    // TODO: Fill in your code here
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
    // TODO: Fill in your code here
    if(isEmpty()) {
        cout << "Queue is Empty!"<<endl;
        return "";
    }
    else
        return frontPtr->item;
}
