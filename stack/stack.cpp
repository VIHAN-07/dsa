#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <algorithm>

using namespace std;

// Node structure for the linked list
struct Node {
    char data;
    Node* next;
};

// Stack structure
struct Stack {
    Node* top;
};

// Function to initialize the stack
void initializeStack(Stack* stack) {
    stack->top = nullptr;
}

// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == nullptr;
}

// Function to push an element onto the stack
void push(Stack* stack, char new_data) {
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = stack->top;
    stack->top = new_node;
}

// Function to pop an element from the stack
char pop(Stack* stack) {
    if (isEmpty(stack)) {
        cout << "Stack Underflow" << endl;
        return '\0'; // Return null character if stack is empty
    }
    Node* temp = stack->top;
    char popped_data = temp->data;
    stack->top = stack->top->next;
    delete temp;
    return popped_data;
}

// Function to return the top element of the stack
char peek(Stack* stack) {
    if (!isEmpty(stack))
        return stack->top->data;
    else {
        cout << "Stack is empty" << endl;
        return '\0'; // Return null character if stack is empty
    }
}

// Function to return precedence of operators
int precedence(char c) {
    if (c == '^') return 3;
    else if (c == '/' || c == '*') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

// Function to convert infix to postfix
string infixToPostfix(string s) {
    Stack stack;
    initializeStack(&stack);
    string result;

    for (char c : s) {
        if (isalnum(c)) {
            result += c; // If operand, add to result
        } else if (c == '(') {
            push(&stack, c); // Push '(' to stack
        } else if (c == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                result += pop(&stack);
            }
            pop(&stack); // Pop '('
        } else { // Operator
            while (!isEmpty(&stack) && precedence(c) <= precedence(peek(&stack))) {
                result += pop(&stack);
            }
            push(&stack, c);
        }
    }

    while (!isEmpty(&stack)) {
        result += pop(&stack);
    }

    return result;
}

// Function to evaluate postfix expression
int evaluatePostfix(string exp) {
    stack<int> st;

    for (char c : exp) {
        if (isdigit(c)) {
            st.push(c - '0'); // Convert char to int
        } else {
            int val2 = st.top(); st.pop();
            int val1 = st.top(); st.pop();
            switch (c) {
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2); break;
                case '/': st.push(val1 / val2); break;
            }
        }
    }
    return st.top();
}

// Function to convert infix to prefix
string infixToPrefix(string s) {
    reverse(s.begin(), s.end());
    for (char &c : s) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }
    string postfix = infixToPostfix(s);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

// Function to evaluate prefix expression
int evaluatePrefix(string exp) {
    stack<int> st;

    for (int i = exp.length() - 1; i >= 0; i--) {
        char c = exp[i];
        if (isdigit(c)) {
            st.push(c - '0'); // Convert char to int
        } else {
            int val1 = st.top(); st.pop();
            int val2 = st.top(); st.pop();
            switch (c) {
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2 ); break;
                case '/': st.push(val1 / val2); break;
            }
        }
    }
    return st.top();
}

// Main function to demonstrate the usage
int main() {
    string infix;
    cout << "Enter an infix expression: ";
    getline(cin, infix); // Take user input for infix expression

    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    string prefix = infixToPrefix(infix);
    cout << "Prefix: " << prefix << endl;

    // Example postfix evaluation
    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << endl;

    // Example prefix evaluation
    cout << "Prefix Evaluation: " << evaluatePrefix(prefix) << endl;

    return 0;
}