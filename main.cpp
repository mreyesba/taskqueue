#include <iostream>
#include "task.h"


bool validate_bst(Task* root) {
    if (root == nullptr)
    {
        return true;
    }

    if (root->left != nullptr && !validate_bst(root->left))
    {
        return false;
    }

    if (root->right != nullptr && !validate_bst(root->right))
    {
        return false;
    }

    return true;
}

int main() {
    std::cout << "Create and initialize tree" << '\n';



    return 0;
}