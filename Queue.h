#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;

typedef string QueueItemType;

class Queue {
    public:
        Queue();
        ~Queue();
        bool isEmpty();
        void enqueue(QueueItemType newItem);
        void dequeue();
        QueueItemType getFront();

    private:
        struct QueueNode {
            QueueItemType item;
            QueueNode* next;
            };

    // end QueueNode
    QueueNode* backPtr;
    QueueNode* frontPtr;
};

#endif // QUEUE_H
