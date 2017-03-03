#include "Stack.h"

char Stack::peek() {
    if (head == NULL) { return '\0'; } 
    return head->c;
}

char Stack::pop() {
    if (head != NULL){
        char temp = head->c;
        Node* topOfStack = head;
        head = head->next;
        delete topOfStack;
        return temp;
    }
    
    return 0;
}

void Stack::push(char c) {
    Node* n = new Node();
    n->next = head;
    n->c = c;
    head = n;
}