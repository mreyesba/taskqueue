#include <iostream>
#include "task.h"
#include "bst.h"

bool validateBST(Task* root) {
    if (root == nullptr)
    {
        return true;
    }

    if (root->left != nullptr && !validateBST(root->left))
    {
        return false;
    }

    if (root->right != nullptr && !validateBST(root->right))
    {
        return false;
    }

    return true;
}

int main() {
    std::cout << "Create and initialize tree" << '\n';

    BST* tree = new BST();

    tree->BST::add(3, 3, 3);
    tree->add(2, 2, 2);
    tree->add(5, 5, 5);
    tree->add(1, 1, 1);
    tree->add(4, 4, 4);

    std::cout << "V1" << '\n';

    tree->print();

    std::cout << "Height: " << tree->getHeight() << '\n';

    tree->remove(5, 5, 5);

    tree->remove(1, 1, 1);

    std::cout << "V2" << '\n';

    tree->print();

    std::cout << "Height: " << tree->getHeight() << '\n';

    return 0;
}