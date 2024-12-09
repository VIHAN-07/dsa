#include<iostream>
#include<queue>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    node() {
        data = 0;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    node* root = NULL;
    node* insert(node* root, int key);
    node* search(node* root, int key);
    void inorder(node* temp);
    void preorder(node* temp);
    void postorder(node* temp);
    void mirror(node*root);
    node*copy_tree(node*root);
    void displayLeafNodes(node*root);
    int depth(node*root);
    node*inorderSucc(node*root);
    node* remove(node*root, int key);
    void levelWiseOrder(node*root);
    void displayWithChildren(node* root);
};

node* BST::insert(node* root, int key) {
    if (root == NULL) {
        root = new node();
        root->data = key;
        return root;
    }

    if (key < root->data) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return root;
}

node* BST::search(node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

void BST::inorder(node* temp) {
    if (temp != NULL) {
        inorder(temp->left);
        cout << temp->data << " ";
        inorder(temp->right);
    }
}

void BST::preorder(node* temp) {
    if (temp != NULL) {
        cout << temp->data << " ";
        preorder(temp->left);
        preorder(temp->right);
    }
}

void BST::postorder(node* temp) {
    if (temp != NULL) {
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->data << " ";
    }
}

void BST::mirror(node*root){
	if(root!=NULL){
		node*temp=root->left;
		root->left=root->right;
		root->right=temp;
		
		mirror(root->left);
		mirror(root->right);
	}
}

node*BST::copy_tree(node*root){
	if(root==NULL){
		return root;
	}
	node* fakeroot=root;
	fakeroot->left=copy_tree(root->left);
	fakeroot->right=copy_tree(root->right);
	
	return fakeroot;
}

void BST:: displayLeafNodes(node* root) {
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        cout << root->data << " ";
    }

    displayLeafNodes(root->left);
    displayLeafNodes(root->right);
}

int BST::depth(node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftDepth = depth(root->left);
        int rightDepth = depth(root->right);
        return max(leftDepth, rightDepth) + 1;
    }
}

node*BST::inorderSucc(node*root){
	node*current=root;
	while(current->left!=NULL){
		current=current->left;
	}
	return current;
}

node* BST::remove(node*root,int key){
	if(root==NULL){
		return root;
	}
	if(key<root->data){
		root->left=remove(root->left,key);
	}
	else if(key>root->data){
		root->right=remove(root->right,key);
	}
	else {
		if(root->left==NULL){
			node*temp=root->right;
			delete root;
			return temp;
		}
		else if(root->right==NULL){
			node*temp=root->left;
			delete root;
			return temp;
		}
		node*temp=inorderSucc(root->right);
		root->data=temp->data;
		root->right=remove(root->right,temp->data);
	}
	return root;	
}

void BST::levelWiseOrder(node*root){
	if(root==NULL){
		return;
	}
	
	queue<node*> q;
	q.push(root);
	q.push(NULL);
	
	while(!q.empty()){
		node* nod=q.front();
		q.pop();
		if(nod!=NULL){
			cout<<nod->data<<" ";
			if(nod->left){
				q.push(nod->left);
			}
			if(nod->right){
				q.push(nod->right);
			}
		}
		else if(!q.empty()) {
			q.push(NULL);
		}
	}
} 

void BST::displayWithChildren(node* root) {
    if (root == NULL) {
        return;
    }

    cout << "Parent: " << root->data<<endl;

    if (root->left != NULL) {
        cout << " Left Child: " << root->left->data<<endl;
         // Recursively display left child and its children
    }
    else{
		cout<<"Left child : NULL"<<endl;
	}

    if (root->right != NULL) {
        cout << " Right Child: " << root->right->data<<endl;
          // Recursively display right child and its children
    }
    else{
		cout<<"Right child : NULL"<<endl;
	}
     displayWithChildren(root->left);
     displayWithChildren(root->right);

    cout << endl;
}


int main() {
    BST b;
    int ch;
    do {
        cout << endl;
        cout << "Main Menu: " << endl;
        cout << "Enter 1 for insertion" << endl;
        cout << "Enter 2 for searching the element" << endl;
        cout << "Enter 3 for inorder traversal " << endl;
        cout << "Enter 4 for preorder traversal " << endl;
        cout << "Enter 5 for postorder traversal " << endl;
        cout << "Enter 6 for mirror image of BST "<<endl;
        cout << "Enter 7 for copying tree "<<endl;
        cout << "Enter 8 for displaying leaf nodes "<<endl;
        cout << "Enter 9 for depth of tree "<<endl;
        cout << "Enter 10 for deleting the element "<<endl;
        cout << "Enter 11 for displaying level wise order "<<endl;
        cout << "Enter 12 for displaying parent with child nodes "<<endl;
        cout << "Enter 13 to exit" << endl;

        cout << "Enter the choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                int n;
                cout << "Enter the number of nodes: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    int k;
                    cout << "Enter the key: ";
                    cin >> k;
                    b.root = b.insert(b.root, k);
                }
                break;

            case 2:
                int m;
                cout << "Enter the element to search: ";
                cin >> m;

                if (b.search(b.root, m) != NULL) {
                    cout << "Key is found" << endl;
                } else {
                    cout << "Key is not found" << endl;
                }
                break;

            case 3:
                b.inorder(b.root);
                cout << endl;
                break;

            case 4:
                b.preorder(b.root);
                cout << endl;
                break;

            case 5:
                b.postorder(b.root);
                cout << endl;
                break;
                
            case 6:
            	b.mirror(b.root);
            	cout << endl;
            	cout<<"Inorder traversal after taking mirror image "<<endl;
            	b.inorder(b.root);
            	break;
            
            case 7:
            	cout<<"Inorder traversal before copying "<<endl;
            	b.inorder(b.root);
            	cout<<endl;
            	cout<<"Inorder traversal after copying "<<endl;
                b.copy_tree(b.root);
            	b.inorder(b.root);
            	break;
            	
            case 8:
            	b.displayLeafNodes(b.root);
            	break;
            	
            case 9:
            	cout << "Depth of the tree: " << b.depth(b.root) << endl;
                break;
                
            case 10:
            	int a;
            	cout<<"Enter the element to delete "<<endl;
            	cin>>a;
            	cout<<"Inorder traversal before deleting the elemnt"<<endl;
            	b.inorder(b.root);
            	b.remove(b.root,a);
            	cout<<"Inorder traversal after deleting the element "<<endl;
            	b.inorder(b.root);
            	break;
            	
            case 11:
            	b.levelWiseOrder(b.root);
            	break;
            	
            case 12:
            	b.displayWithChildren(b.root);
            	break;
            	
            case 13:
                cout << "Program Terminated" << endl;
                exit(0);
        }
    } while (ch != 13);

    return 0;
}
