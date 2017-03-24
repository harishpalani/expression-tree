/**
 * Shunting Yard Algorithm
 * Translating mathematical expressions from infix to postfix notation, 
 * considering basic arithmetic expressions, integers, and parantheses.
 * 
 * @author Harish Palani
 * @version February 2017
 */
#include <iostream>
#include <cstring>
#include "Stack.h"
#include "Stack2.h"

using namespace std;

struct BinaryNode {
    char* c;
    BinaryNode* left = NULL, *right = NULL;
    ~BinaryNode() {
        delete[] c;
    }
};

// Function prototypes
char* toPostfix (char *infix);
bool isOperator (char t);
int precedence (char o);

BinaryNode* getTree(Stack2 &postfix);
void prefix(BinaryNode* node);
void postfix(BinaryNode* node);
void infix(BinaryNode* node);
void deleteTree(BinaryNode* node);

int main() {
    char in[128];
    char input[128];
    
    while (true) {
        // Get infix expression
        cout << "Enter an infix expression: ";
        cin.getline(in, 128);
        cout << "Infix: " << in << endl;
        
        // Convert infix to postfix
        char* post = toPostfix(in);
        
        // + Expression Tree
        Stack2 s2;
        int i = 0;
        
        while (post[i]) {
            if (post[i] == ' ') {
                i++;
                continue;
            }
            
            if (isdigit(post[i])) {
                char n[10];
                int j = 0;
                while (isdigit(post[i])) {
                    n[j++] = post[i++];
                }
                n[j++] = '\0';
                s2.push(n);
            }
            
            else {
                char o[2] = { post[i++], '\0' };
                s2.push(o);
            }
        }
        
        delete[] post;
        BinaryNode* root = getTree(s2); // Get expression tree
        
        cout << "Would you like your output in prefix, postfix, or infix?" << endl;
        cin.getline(input, 128);
        
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }
        
        if (strcmp(input, "prefix") == 0) {
            prefix(root);
            cout << endl;
        } else if(strcmp(input, "postfix") == 0) {
            postfix(root);
            cout << endl;
        } else {
            infix(root);
            cout << endl;
        } 
        
        // Delete the expression tree
        deleteTree(root);
    }
    return 0;
}

// Implementation of shunting yard algorithm
char* toPostfix(char *infix) {
    Stack s;
    char* postfix = new char[strlen(infix) + 1];
    int iInfix = 0, iPostfix = 0;
    
    while (infix[iInfix]) {
        if (infix[iInfix] == ' ') {
            iInfix++;
            continue; // Skip shunting yard operations if it's a space
        }
        
        // Check if the character is an integer
        if (isdigit(infix[iInfix])) {
            while (isdigit(infix[iInfix])) {
                postfix[iPostfix++] = infix[iInfix++];
            }
            postfix[iPostfix++] = ' ';
        }
        
        // Check if the character is an operator
        else if (isOperator(infix[iInfix])) {
            while (isOperator(s.peek()) &&
               ((infix[iInfix] != '^' && precedence(infix[iInfix]) <= precedence(s.peek()))
            || (infix[iInfix] == '^' && precedence(infix[iInfix]) < precedence(s.peek())))) {
                postfix[iPostfix++] = s.pop();
                postfix[iPostfix++] = ' ';
            }
            s.push(infix[iInfix++]);
        }
        
        // Check if the character is a left parenthesis
        else if (infix[iInfix] == '(') {
            s.push(infix[iInfix++]);
        }
        
        // Check if the character is a right parenthesis
        else if (infix[iInfix] == ')') {
            while (s.peek() != '(') {
                postfix[iPostfix++] = s.pop();
                postfix[iPostfix++] = ' ';
                if (s.peek() == 0) {
                    cout << "Error: mismatched parentheses." << endl;
                    break;
                }
            }
            s.pop();
            iInfix++;
        }
    }
    
    // Infix expression has been parsed completely!
    while (s.peek()) {
        postfix[iPostfix++] = s.pop();
        postfix[iPostfix++] = ' ';
    }
    postfix[iPostfix - 1] = 0;
    
    return postfix;
}

bool isOperator (char t) {
    return t == '+' || t == '-' || t =='*' || t =='/' || t == '^';
}

int precedence (char o) {
    if (o == '+' || o == '-') { return 0; }
    if (o == '*' || o == '/') { return 1; }
    if (o == '^') { return 2; }
    return -1;
}

BinaryNode* getTree(Stack2 &postfix) {
    if (isOperator(*postfix.peek())) {
        BinaryNode* binaryNode = new BinaryNode();
        binaryNode->c = postfix.pop();
        binaryNode->right = getTree(postfix);
        binaryNode->left = getTree(postfix);
        return binaryNode;
    } else {
        BinaryNode* binaryNode = new BinaryNode();
        binaryNode->c = postfix.pop();
        return binaryNode;
    }
}

void prefix(BinaryNode* node) {
    if (isOperator(*(node->c))) {
        cout << node->c << ' ';
        prefix(node->left);
        prefix(node->right);
    } else {
        cout << node->c << ' ';
    }
}

void postfix(BinaryNode* node) {
    if (isOperator(*(node->c))) {
        postfix(node->left);
        postfix(node->right);
        cout << node->c << ' ';
    } else {
        cout << node->c << ' ';
    }
}

void infix(BinaryNode* node) {
    if (isOperator(*(node->c))) {
        if (isOperator(*(node->left->c))) {
            cout << "( ";
            infix(node->left);
            cout << ") ";
        } else {
            infix(node->left);
        }
        
        cout << node->c << ' ';
        
        if (isOperator(*(node->right->c))) {
            cout << "( ";
            infix(node->right);
            cout << ") ";
        } else {
            infix(node->right);
        }
    } else {
        cout << node->c << ' ';
    }
}

void deleteTree(BinaryNode* node){
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}
