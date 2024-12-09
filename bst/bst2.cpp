#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        // If value is equal, do not insert (handle duplicates)
        return node;
    }

    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) return node;

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(node->right);
            node->data = temp->data; // Copy the inorder successor's content to this node
            node->right = deleteNode(node->right, temp->data); // Delete the inorder successor
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    int depth(Node* node) {
        if (node == nullptr) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return max(leftDepth, rightDepth) + 1;
    }

    void mirror(Node* node) {
        if (node == nullptr) return;
        swap(node->left, node->right);
        mirror(node->left);
        mirror(node->right);
    }

    void levelOrder(Node* node) {
        if (node == nullptr) return;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

    void displayLeafNodes(Node* node) {
        if (node == nullptr) return;
        if (node->left == nullptr && node->right == nullptr) {
            cout << node->data << " ";
        }
        displayLeafNodes(node->left);
        displayLeafNodes(node->right);
    }

    void displayParentChild(Node* node) {
        if (node == nullptr) return;
        if (node->left != nullptr || node->right != nullptr) {
            cout << "Parent: " << node->data << " -> ";
            if (node->left) cout << "Left Child: " << node->left->data << " ";
            if (node->right) cout << "Right Child: " << node->right->data << " ";
            cout << endl;
        }
        displayParentChild(node->left);
        displayParentChild(node->right);
    }

    Node* copy(Node* node) {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->left = copy(node->left );
        newNode->right = copy(node->right);
        return newNode;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void deleteNode(int value) {
        root = deleteNode(root, value);
    }

    bool search(int value) {
        Node* current = root;
        while (current != nullptr) {
            if (current->data == value) return true;
            current = (value < current->data) ? current->left : current->right;
        }
        return false;
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }

    void preorderTraversal() {
        preorder(root);
        cout << endl;
    }

    void postorderTraversal() {
        postorder(root);
        cout << endl;
    }

    int getDepth() {
        return depth(root);
    }

    void displayMirror() {
        mirror(root);
        inorderTraversal(); // Display the mirrored tree using inorder traversal
        mirror(root); // Restore original tree
    }

    BinarySearchTree* createCopy() {
        BinarySearchTree* newTree = new BinarySearchTree();
        newTree->root = copy(root);
        return newTree;
    }

    void displayLeafNodes() {
        displayLeafNodes(root);
        cout << endl;
    }

    void displayParentChildNodes() {
        displayParentChild(root);
    }

    void displayLevelWise() {
        levelOrder(root);
        cout << endl;
    }

    void menu() {
        int choice, value;
        do {
            cout << "\nMenu:\n";
            cout << "1. Insert\n";
            cout << "2. Delete\n";
            cout << "3. Search\n";
            cout << "4. Inorder Traversal\n";
            cout << "5. Preorder Traversal\n";
            cout << "6. Postorder Traversal\n";
            cout << "7. Depth of Tree\n";
            cout << "8. Display Leaf Nodes\n";
            cout << "9. Display Level Wise\n";
            cout << "10. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter value to insert: ";
                    cin >> value;
                    insert(value);
                    break;
                case 2:
                    cout << "Enter value to delete: ";
                    cin >> value;
                    deleteNode(value);
                    break;
                case 3:
                    cout << "Enter value to search: ";
                    cin >> value;
                    cout << (search(value) ? "Found" : "Not Found") << endl;
                    break;
                case 4:
                    cout << "Inorder Traversal: ";
                    inorderTraversal();
                    break;
                case 5:
                    cout << "Preorder Traversal: ";
                    preorderTraversal();
                    break;
                case 6:
                    cout << "Postorder Traversal: ";
                    postorderTraversal();
                    break;
                case 7:
                    cout << "Depth of Tree: " << getDepth() << endl;
                    break;
                case 8:
                    cout << "Leaf Nodes: ";
                    displayLeafNodes();
                    break;
                case 9:
                    cout << "Level Wise Display: ";
                    displayLevelWise();
                    break;
                case 10:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 10);
    }
};

int main() {
    BinarySearchTree bst;
    bst.menu();
    return 0;
}