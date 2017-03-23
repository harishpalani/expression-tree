#include "Stack2.h"

char Stack2::peek() {
    if (head == NULL) { return '\0'; } 
    return head->c;
}

char Stack2::pop() {
    if (head != NULL){
        char temp = head->c;
        Node2* topOfStack = head;
        head = head->next;
        delete topOfStack;
        return temp;
    }
    
    return 0;
}

void Stack2::push(char c) {
    Node2* n = new Node2();
    n->next = head;
    n->c = c;
    head = n;
}