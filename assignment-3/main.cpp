#include <iostream>
#include "bst.cpp"
#include "rbt.cpp"

using namespace std;

int main() {
    // Testing BST functions
    BST bst;
    vector<int> preorder = {8, 5, 1, 7, 10, 12};
    bst.root = bst.constructBSTFromPreorder(preorder);
    bst.printTree(bst.root, "", true);

    cout << "Searching 7: " << (bst.search(7) ? "Found" : "Not Found") << endl;

    BSTNode* lca = bst.findLCA(bst.root, 1, 7);
    cout << "LCA of 1 and 7: " << (lca ? lca->data : -1) << endl;

        // Testing RBT functions
    RBTree tree1;
    tree1.insert(10);
    tree1.insert(20);
    tree1.insert(30);

    RBTree tree2;
    tree2.insert(40);
    tree2.insert(35);
    tree2.insert(60);

    tree1.printInOrder();
    cout << endl;
    tree2.printInOrder();

    RBTree* mergedTree = tree1.merge(tree2);
    cout << "Merged tree: ";
    mergedTree->printTree();

    RBTree tree;
    // Insert some values
    tree.insert(10);
    tree.insert(20);
    tree.insert(25);
    tree.insert(30);
    tree.insert(35);
    tree.insert(40);
    tree.insert(50);

    // Split around 8
    auto [leftTree, rightTree] = tree.split(15);
    // Print results
    cout << "Left tree: " << endl;
    leftTree.printTree();
    cout << "Right tree: " << endl;
    rightTree.printTree();

    return 0;
}
