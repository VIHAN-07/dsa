#include <iostream>
using namespace std;

// Node structure for Threaded Binary Tree
struct ThreadedNode {
    int data;
    ThreadedNode* left;
    ThreadedNode* right;
    bool leftThread;  // true if left pointer is a thread
    bool rightThread; // true if right pointer is a thread

    ThreadedNode(int val) : data(val), left(nullptr), right(nullptr), leftThread(true), rightThread(true) {}
};

// Class for Threaded Binary Tree
class ThreadedBinaryTree {
private:
    ThreadedNode* root;

public:
    ThreadedBinaryTree() : root(nullptr) {}

    // Function to insert a new node in the threaded binary tree
    void insert(int val) {
        ThreadedNode* newNode = new ThreadedNode(val);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        ThreadedNode* current = root;
        ThreadedNode* parent = nullptr;

        // Find the correct position to insert the new node
        while (current) {
            parent = current;
            if (val < current->data) {
                if (!current->leftThread) {
                    current = current->left;
                } else {
                    break;
                }
            } else {
                if (!current->rightThread) {
                    current = current->right;
                } else {
                    break;
                }
            }
        }

        // Insert the new node
        if (val < parent->data) {
            newNode->left = parent->left;
            newNode->right = parent;
            newNode->leftThread = parent->leftThread;
            newNode->rightThread = true;

            parent->left = newNode;
            parent->leftThread = false;
        } else {
            newNode->right = parent->right;
            newNode->left = parent;
            newNode->rightThread = parent->rightThread;
            newNode->leftThread = true;

            parent->right = newNode;
            parent->rightThread = false;
        }
    }

    // In-order traversal of the threaded binary tree
    void inorderTraversal() {
        ThreadedNode* current = root;
        if (current == nullptr) return;

        // Go to the leftmost node
        while (current->left != nullptr && !current->leftThread) {
            current = current->left;
        }

        // Traverse the tree
        while (current != nullptr) {
            cout << current->data << " ";

            // If the right pointer is a thread, go to the in-order successor
            if (current->rightThread) {
                current = current->right;
            } else {
                current = current->right;
                // Go to the leftmost node of the right subtree
                while (current != nullptr && !current->leftThread) {
                    current = current->left;
                }
            }
        }
        cout << endl;
    }

    // Pre-order traversal of the threaded binary tree
    void preorderTraversal() {
        ThreadedNode* current = root;
        if (current == nullptr) return;

        // Pre-order traversal
        while (current != nullptr) {
            cout << current->data << " ";

            // If left child exists, go to it
            if (!current->leftThread) {
                current = current->left;
            } else {
                // If left child is a thread, go to the right child
                while (current != nullptr && current->rightThread) {
                    current = current->right;
                }
                // Move to the right child
                if (current != nullptr) {
                    current = current->right;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    ThreadedBinaryTree tbt;
    int value;
    char choice;

    // Take user input for inserting nodes
    do {
        cout << "Enter a value to insert: ";
        cin >> value;
        tbt.insert(value);

        cout << "Do you want to insert another value? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "In-order Traversal: ";
    tbt.inorderTraversal();

    cout << "Pre-order Traversal: ";
    tbt.preorderTraversal();

    return 0;
}