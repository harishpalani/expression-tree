#ifndef STACK_H
#define STACK_H

#include <iostream>

struct Node {
    char c;
    Node* next = NULL;
};

class Stack {
    public:
        char peek();
        char pop();
        void push(char c);
    
    private:
        Node* head = NULL;
    
};
#endif