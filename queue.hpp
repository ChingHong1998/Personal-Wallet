#ifndef QUEUE_L_HPP
#define QUEUE_L_HPP
#include <string>
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
}; // end Queue }; // end namespace Practice2 #endif
#endif
