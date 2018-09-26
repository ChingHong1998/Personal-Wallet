#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string>
using namespace std;
typedef string StackItemType;
class Stack {
    public: /** Default constructor. */
        Stack();
        /** Copy constructor. * @param aStack The stack to copy. */
        Stack(const Stack& aStack);
        /** Destructor. */
        ~Stack(); // Stack operations:
        bool isEmpty() const;
        void push(const StackItemType& newItem);
        void pop() ;
        void pop(StackItemType& stackTop);
        StackItemType getTop();

    private: /** A node on the stack. */
        struct StackNode { /** A data item on the stack. */
            StackItemType item; /** Pointer to next node. */
            StackNode *next;
        };
        StackNode *topPtr;
};


#endif // STACK_H
