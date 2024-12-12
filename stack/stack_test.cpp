#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Class for stack
class Stack {
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(int new_data) {
        Node* new_node = new Node();
        new_node->data = new_data;
        new_node->next = top;
        top = new_node;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        Node* temp = top;
        int popped_data = temp->data;
        top = top->next;
        delete temp;
        return popped_data;
    }

    int peek() {
        if (!isEmpty())
            return top->data;
        else {
            cout << "Stack is empty" << endl;
            return -1;
        }
    }
};

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
    string result;

    for (char c : s) {
        if (isalnum(c)) {
            result += c; // If operand, add to result
        } else if (c == '(') {
            stack.push(c); // Push '(' to stack
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                result += (char)stack.pop();
            }
            stack.pop(); // Pop '('
        } else { // Operator
            while (!stack.isEmpty() && precedence(c) <= precedence(stack.peek())) {
                result += (char)stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        result += (char)stack.pop();
    }

    return result;
}

// Function to evaluate postfix expression
int evaluatePostfix(string exp) {
    Stack stack;
    
    for (char c : exp) {
        if (isdigit(c)) {
            stack.push(c - '0'); // Convert char to int
        } else {
            int val2 = stack.pop();
            int val1 = stack.pop();
            switch (c) {
                case '+': stack.push(val1 + val2); break;
                case '-': stack.push(val1 - val2); break;
                case '*': stack.push(val1 * val2); break;
                case '/': stack.push(val1 / val2); break;
            }
        }
    }
    return stack.pop();
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
    Stack stack;

    for (int i = exp.length() - 1; i >= 0; i--) {
        char c = exp[i];
        if (isdigit(c)) {
            stack.push(c - '0'); // Convert char to int
        } else {
            int val1 = stack.pop();
            int val2 = stack.pop();
            switch (c) {
                case '+': stack.push(val1 + val2); break;
                case '-': stack.push(val1 - val2); break;
                case '*': stack.push(val1 * val2); break;
                case '/': stack.push(val1 / val2); break;
            }
        }
    }
    return stack.pop();
}

// Main function to demonstrate the menu-driven program
int main() {
    string infix;
    int choice;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Convert Infix to Postfix" << endl;
        cout << "2. Convert Infix to Prefix" << endl;
        cout << "3. Evaluate Postfix Expression" << endl;
        cout << "4. Evaluate Prefix Expression" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1:
                cout << "Enter an infix expression: ";
                getline(cin, infix);
                cout << "Postfix: " << infixToPostfix(infix) << endl;
                break;

            case 2:
                cout << "Enter an infix expression: ";
                getline(cin, infix);
                cout << "Prefix: " << infixToPrefix(infix) << endl;
                break;

            case 3:
                cout << "Enter a postfix expression: ";
                getline(cin, infix);
                cout << "Postfix Evaluation: " << evaluatePostfix(infix) << endl;
                break;

            case 4:
                cout << "Enter a prefix expression: ";
                getline(cin, infix);
                cout << "Prefix Evaluation: " << evaluatePrefix(infix) << endl;
                break;

            case 5:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
