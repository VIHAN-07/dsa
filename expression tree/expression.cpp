#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

struct Node {
    char value;
    Node* left;
    Node* right;

    Node(char val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to construct an expression tree from postfix expression
Node* constructPostfix(const string& postfix) {
    stack<Node*> st;
    for (char ch : postfix) {
        if (isalnum(ch)) { // If the character is an operand
            st.push(new Node(ch));
        } else { // The character is an operator
            Node* right = st.top(); st.pop();
            Node* left = st.top(); st.pop();
            Node* node = new Node(ch);
            node->left = left;
            node->right = right;
            st.push(node);
        }
    }
    return st.top();
}

// Function to construct an expression tree from prefix expression
Node* constructPrefix(const string& prefix) {
    stack<Node*> st;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];
        if (isalnum(ch)) { // If the character is an operand
            st.push(new Node(ch));
        } else { // The character is an operator
            Node* left = st.top(); st.pop();
            Node* right = st.top(); st.pop();
            Node* node = new Node(ch);
            node->left = left;
            node->right = right;
            st.push(node);
        }
    }
    return st.top();
}

// Recursive In-order Traversal
void inorderRecursive(Node* node) {
    if (node) {
        inorderRecursive(node->left);
        cout << node->value << " ";
        inorderRecursive(node->right);
    }
}

// Non-Recursive In-order Traversal
void inorderNonRecursive(Node* root) {
    stack<Node*> st;
    Node* current = root;
    while (!st.empty() || current) {
        while (current) {
            st.push(current);
            current = current->left;
        }
        current = st.top(); st.pop();
        cout << current->value << " ";
        current = current->right;
    }
}

// Recursive Pre-order Traversal
void preorderRecursive(Node* node) {
    if (node) {
        cout << node->value << " ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }
}

// Non-Recursive Pre-order Traversal
void preorderNonRecursive(Node* root) {
    if (!root) return;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* current = st.top(); st.pop();
        cout << current->value << " ";
        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }
}

// Recursive Post-order Traversal
void postorderRecursive(Node* node) {
    if (node) {
        postorderRecursive(node->left);
        postorderRecursive(node->right);
        cout << node->value << " ";
    }
}

// Non-Recursive Post-order Traversal
void postorderNonRecursive(Node* root) {
    if (!root) return;
    stack<Node*> st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        Node* current = st1.top(); st1.pop();
        st2.push(current);
        if (current->left) st1.push(current->left);
        if (current->right) st1.push(current->right);
    }
    while (!st2.empty()) {
        cout << st2.top()->value << " ";
        st2.pop();
    }
}

int main() {
    int choice;
    string expression;
    Node* root = nullptr;

    do {
        cout << "\nMenu:\n";
        cout << "1. Construct Expression Tree from Postfix\n";
        cout << "2. Construct Expression Tree from Prefix\n";
        cout << "3. In-order Traversal (Recursive)\n";
        cout << "4. In-order Traversal (Non-Recursive)\n";
        cout << "5. Pre-order Traversal (Recursive)\n";
        cout << "6. Pre-order Traversal (Non-Recursive)\n";
        cout << "7. Post-order Traversal (Recursive)\n";
        cout << "8. Post-order Traversal (Non-Recursive)\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Postfix Expression: ";
                cin >> expression;
                root = constructPostfix(expression);
                break;
            case 2:
                cout << "Enter Prefix Expression: ";
                cin >> expression;
                root = constructPrefix(expression);
                break;
            case 3:
                cout << "In-order Traversal (Recursive): ";
                inorderRecursive(root);
                cout << endl;
                break;
            case 4:
                cout << "In-order Traversal (Non-Recursive): ";
                inorderNonRecursive(root);
                cout << endl;
                break;
            case 5:
                cout << "Pre-order Traversal (Recursive): ";
                preorderRecursive(root);
                cout << endl;
                break;
            case 6:
                cout << "Pre-order Traversal (Non-Recursive): ";
                preorderNonRecursive(root);
                cout << endl;
                break;
            case 7:
                cout << "Post-order Traversal (Recursive): ";
                postorderRecursive(root);
                cout << endl;
                break;
            case 8:
                cout << "Post-order Traversal (Non-Recursive): ";
                postorderNonRecursive(root);
                cout << endl;
                break;
            case 9:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}