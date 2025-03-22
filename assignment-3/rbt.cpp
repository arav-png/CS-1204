#include <iostream>
#include <iomanip>
using namespace std;
 
enum COLOR { RED, BLACK };
 
class RBTNode {
public:
    int val;
    COLOR color;
    RBTNode *left, *right, *parent;
    
    RBTNode(int val) : val(val) {
        parent = left = right = NULL;
        color = RED;
    }
};
    
class RBTree {
public:
    RBTNode *root;

    void printTreeHelper(RBTNode* node, int indent = 0, bool isLeft = false) {
        if (node == nullptr)
            return;

        indent += 4;
        printTreeHelper(node->right, indent, false);

        cout << std::setw(indent);
        if (node->parent == nullptr)
            cout << "Root ";
        else if (isLeft)
            cout << "L----";
        else
            cout << "R----";

        string sColor = (node->color == BLACK) ? "BLACK" : "RED";
        cout << node->val << "(" << sColor << ")" << endl;

        printTreeHelper(node->left, indent, true);
    };

    void destroyTree(RBTNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    void inorderTraversal(RBTNode* node, vector<int>& inorder) {
        if (node == nullptr)
            return;
        inorderTraversal(node->left, inorder);
        inorder.push_back(node->val);
        inorderTraversal(node->right, inorder);
    }
    RBTNode* clone(RBTNode* node) { // Helper function for deep copy
        if (node == nullptr)
            return nullptr;

        RBTNode* newNode = new RBTNode(node->val);
        newNode->color = node->color;
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);

        if (newNode->left) newNode->left->parent = newNode;
        if (newNode->right) newNode->right->parent = newNode;

        return newNode;
    }
    // search for a node in the tree
    RBTNode* search(int val) {
        RBTNode* curr = root;
        while (curr != nullptr) {
            if (val == curr->val) {
                return curr;
            } else if (val < curr->val) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return nullptr;
    }
    

    void leftRotate(RBTNode* x) {
        RBTNode* y = x->right;
        x->right = y->left; //y's left subtree is now x's right subtree
        
        if (y->left != nullptr) { //if leftsubtree not empty 
            y->left->parent = x; // then x is the parent of the left subtree
        }
        
        y->parent = x->parent;// x's parent is y's parent 
        if (x->parent == nullptr) // if x is the root
        {
            root = y;
        } 

        else if (x == x->parent->left) // if x's a left subchild then y becomes the left subchild
         {
            x->parent->left = y;
        } 

        else { // similarly if x is a right child
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    //symmetric code for rightRotate

    void rightRotate(RBTNode* x) {
        RBTNode* y = x->left;
        x->left = y->right; //y's right subtree is now x's left subtree
        
        if (y->right != nullptr) { //if right subtree not empty
            y->right->parent = x; // then x is the parent of the right subtree
        }
        
        y->parent = x->parent; // x's parent is y's parent
        if (x->parent == nullptr) // if x is the root
        {
            root = y;
        } 

        else if (x == x->parent->right) // if x's a right subchild then y becomes the right subchild
        {
            x->parent->right = y;
        }

        else { // similarly if x is a left child
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
    void insertFixup(RBTNode* z) {
        while (z->parent != nullptr && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBTNode* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) { // Case 1
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) { // Case 2
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK; // Case 3
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                RBTNode* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) { // Case 1
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) { // Case 2
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK; // Case 3
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    RBTree() : root(nullptr) {}

    ~RBTree() {
        destroyTree(root);
    }

    RBTree(const RBTree& other) : root(nullptr) { // Copy constructor
        if (other.root != nullptr) {
            root = clone(other.root);
        }
    }

    void printTree() {
        printTreeHelper(root);
    }
    void insert(int val) {
        RBTNode* newNode = new RBTNode(val);
        RBTNode* y = nullptr;
        RBTNode* x = root;

        while (x != nullptr) {
            y = x;
            if (newNode->val == x->val) { // Avoid duplicate insertion
                delete newNode;
                return;
            }
            x = (newNode->val < x->val) ? x->left : x->right;
        }

        newNode->parent = y;
        if (y == nullptr) {
            root = newNode;
        } else if (newNode->val < y->val) {
            y->left = newNode;
        } else {
            y->right = newNode;
        }

        newNode->color = RED;
        insertFixup(newNode);
    }

    RBTree* merge(RBTree& otherTree) {
        vector<int> inorder1, inorder2;
        inorderTraversal(root, inorder1);
        inorderTraversal(otherTree.root, inorder2);

        RBTree* mergedTree = new RBTree();
        int i = 0, j = 0;

        while (i < inorder1.size() && j < inorder2.size()) {
            if (inorder1[i] < inorder2[j])
                mergedTree->insert(inorder1[i++]);
            else
                mergedTree->insert(inorder2[j++]);
        }
        while (i < inorder1.size())
            mergedTree->insert(inorder1[i++]);
        while (j < inorder2.size())
            mergedTree->insert(inorder2[j++]);

        return mergedTree;
    }
    //split a tree
    pair<RBTree, RBTree> split(int k) {
    if (root == nullptr) // If the tree is empty
        return {RBTree(), RBTree()};

    RBTree leftTree, rightTree;
    vector<int> inorder;
    inorderTraversal(root, inorder);
    for(int i = 0; i < inorder.size(); i++) {
        if (inorder[i] < k)
            leftTree.insert(inorder[i]);
        else 
            rightTree.insert(inorder[i]);
    }
    return {leftTree, rightTree};
}

    void printInOrder() {
        vector<int> inorder;
        inorderTraversal(root, inorder);
        cout << "Inorder:";
        cout << endl;
        for (int val : inorder)
            cout << val << " ";
        cout << endl;
    }



};
