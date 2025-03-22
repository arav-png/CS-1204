#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Node defition for BST
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// BST class
class BST {
public:
    BSTNode* root;

    BST() : root(nullptr) {}

    // Print tree in a tree structure
    void printTree(BSTNode* root, string indent, bool last) {
        if (root) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            cout << root->data << endl;
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
        }
    }

    // Search function
    BSTNode* search(int k) {
        BSTNode* x = root;
        while (x != nullptr && k != x->data) {
            if (k < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return x;
    }

    // Insert function
    void insert(BSTNode*& root, int z) {
        BSTNode* x = root;
        BSTNode* y = nullptr;
        BSTNode* n = new BSTNode(z);
        while (x != nullptr) {
            y = x;
            if (z < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        if (y == nullptr) {
            root = n;
        } else if (n->data < y->data) {
            y->left = n;
        } else {
            y->right = n;
        }
    }

    void insert(int z) {
        insert(root, z);
    }

    void print() {
        printTree(root, "", true);
    }
    BSTNode* constructBSTFromPreorder(vector<int>& preorder) {
        stack<BSTNode*> S; //creating a stack to store the node values of the preorder traversal
        
        if (preorder.size() <= 0) { //edge case if the vector is empty 
            return nullptr;
        }
        BSTNode* root = new BSTNode(preorder[0]);// the first element of a preorder treversal is the root
        S.push(root);

        for (int i = 1; i < preorder.size(); i++) {
            BSTNode* x = nullptr; //creating a node pointer to keep track of the stack
            
            while (!S.empty() && preorder[i] > S.top()->data) { //keep popping the stack until u find a greater node
                x = S.top();
                S.pop();
            }
            if (x != nullptr) {
                x->right = new BSTNode(preorder[i]);//assign the right node to the greater node
                S.push(x->right);
            } else {
                x = S.top();
                x->left = new BSTNode(preorder[i]);
                S.push(x->left);
            }
        }
        return root;
    }
    // Find LCA of two nodes
    BSTNode* findLCA(BSTNode* root, int n1, int n2) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->data == n1 || root->data == n2) {
            return root;
        }
        BSTNode* left = findLCA(root->left, n1, n2);
        BSTNode* right = findLCA(root->right, n1, n2);
        if (left && right) {
            return root;
        }
        return left ? left : right;
    }


};