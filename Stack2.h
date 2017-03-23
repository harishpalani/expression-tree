#ifndef STACK2_H
#define STACK2_H

#include <iostream>

struct Node2 {
    char c;
    Node2* next = NULL;
};

class Stack2 {
    public:
        char peek();
        char pop();
        void push(char c);
    
    private:
        Node2* head = NULL;
    
};
#endif