#pragma once

#include "task.h"
#include <iostream>

template <typename T>
struct Node {
    T data;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    int height = 1;

    Node(const T& val) : data(val) {}
};

template <typename T>
class AVLTree {
private:
    Node<T>* m_root;

    void deleteTree(Node<T>* root) {
        if (root == nullptr)
        {
            return;
        }

        if (root->left != nullptr)
        {
            deleteTree(root->left);
            root->left = nullptr;
        }

        if (root->right != nullptr)
        {
            deleteTree(root->right);
            root->right = nullptr;
        }

        delete root;
    }

    Node<T>* leftmost(Node<T>* root) {
        Node<T>* cur = root;

        if (cur == nullptr)
        {
            return nullptr;
        }

        while (cur->left != nullptr)
        {
            cur = cur->left;
        }

        return cur;
    }

    int getHeightHelperHeavy(Node<T>* node) {
        if (node == nullptr)
        {
            return 0;
        }

        return std::max(getHeightHelperHeavy(node->left), getHeightHelperHeavy(node->right)) + 1;
    }

    int getHeightHelper(Node<T>* node) {
        if (node == nullptr)
        {
            return 0;
        }

        return node->height;
    }

    void updateHeight(Node<T>* node) {
        if (node == nullptr)
        {
            return;
        }

        node->height =  std::max(getHeightHelper(node->left), getHeightHelper(node->right)) + 1;

        // std::cout << "New height " << node->height << '\n'; 
    }

    Node<T>* rotateLeft(Node<T>* node) {
        Node<T>* cur = node;
        Node<T>* right = nullptr;

        if (cur == nullptr)
        {
            return nullptr;
        }

        // std::cout << "rotate left " << '\n'; 

        right = cur->right;

        if (right != nullptr)
        {
            cur->right = right->left;
            right->left = cur;
            cur = right;
            updateHeight(cur->left);
            updateHeight(cur);
        }
        
        return cur;
    }

    Node<T>* rotateRight(Node<T>* node) {
        Node<T>* cur = node;
        Node<T>* left = nullptr;

        if (cur == nullptr)
        {
            return nullptr;
        }

        // std::cout << "rotate left " << '\n'; 

        left = cur->left;

        if (left != nullptr)
        {
            cur->left = left->right;
            left->right = cur;
            cur = left;
            updateHeight(cur->right);
            updateHeight(cur);
        }
        
        return cur;
    }

    int getBalanceHeavy(Node<T>* node) {
        if (node == nullptr)
        {
            return 0;
        }

        return getHeightHelperHeavy(node->left) - getHeightHelperHeavy(node->right);
    }

    int getBalance(Node<T>* node) {
        if (node == nullptr)
        {
            return 0;
        }

        return getHeightHelper(node->left) - getHeightHelper(node->right);
    }

    Node<T>* balanceSubtree(Node<T>* node) {
        int balance = 0;
        Node<T>* res = node;

        balance = getBalance(node);

        // std::cout << "balance " << balance << '\n'; 

        if (balance >= 2)
        {
            if (getBalance(node->left) < 0)
            {
                node->left = rotateLeft(node->left);
            }

            res = rotateRight(node);
        }
        else if (balance <= -2)
        {
            if (getBalance(node->right) > 0)
            {
                node->right = rotateRight(node->right);
            }

            res = rotateLeft(node);
        }

        return res;
    }

    Node<T>* addHelper(Node<T>* root, Node<T>* node) {
        int balance = 0;

        // std::cout << "Add in " << root << '\n';
        // std::cout << "node "  << '\n';
        // node->data.print();

        if (root == nullptr)
        {
            return node;
        }

        if (root->data == node->data)
        {
            delete node;
            return root;
        }

        if (root->data > node->data)
        {
            root->left = addHelper(root->left, node);
        }
        else
        {
            root->right = addHelper(root->right, node);
        }

        updateHeight(root);

        return balanceSubtree(root);
    }

    Node<T>* removeHelper(const T& val, Node<T>* node) {
        Node<T>* cur = node;
        Node<T>* successor = nullptr;
        int balance = 0;

        if (node == nullptr)
        {
            return nullptr;
        }

        if (node->data == val)
        {   
            if (node->left == nullptr)
            {
                cur = node->right;
                delete node;
            } 
            else if (cur->right == nullptr)
            {
                cur = node->left;
                delete node;
            }
            else
            {
                successor = leftmost(cur->right);

                if (successor == nullptr)
                {
                    std::cout << "This should never happen!" << '\n';
                    return nullptr;
                }

                cur->data = successor->data;

                cur->right = removeHelper(successor->data, cur->right);
            }
        }
        else if (cur->data > val)
        {
            node->left = removeHelper(val, node->left);
        }
        else
        {
            node->right = removeHelper(val, node->right);
        }

        updateHeight(cur);

        return balanceSubtree(cur);
    }

    //
    //  This will only work for Task or other structs that implement print()
    //

    void printNode(Node<T>* node) {
        if (node != nullptr)
        {
            //std::cout << node->data << "\n";
            node->data.print();
        }
    }

    void printHelper(Node<T>* node) {
        if (node == nullptr)
        {
            return;
        }

        if (node->left != nullptr)
        {
            printHelper(node->left);
        }

        printNode(node);

        if (node->right != nullptr)
        {
            printHelper(node->right);
        }
    }

    bool validateHelper(Node<T>* node, Node<T>* leftBound, Node<T>* rightBound) {
        if (node == nullptr)
        {
            return true;
        }

        if (leftBound != nullptr && node->data < leftBound->data)
        {
            return false;
        } 
        
        if (rightBound != nullptr && node->data > rightBound->data)
        {
            return false;
        }

        if (!validateHelper(node->left, leftBound, node))
        {
            return false;
        }

        if (!validateHelper(node->right, node, rightBound))
        {
            return false;
        }

        if (std::abs(getBalanceHeavy(node)) >= 2)
        {
            return false;
        }

        return true;
    }

public:
    AVLTree() : m_root(nullptr) {}

    ~AVLTree() {
        deleteTree(m_root);
    }

    AVLTree(const AVLTree&) = delete;
    
    AVLTree& operator=(const AVLTree&) = delete;

    void add(const T& val) {
        Node<T>* node = new Node<T>(val);
        
        m_root = addHelper(m_root, node);
    }

    Node<T>* find(const T& val) {
        Node<T>* cur = m_root;

        while (cur != nullptr)
        {
            if (cur->data == val)
            {
                break;
            }
            else if (cur->data > val)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }

        return cur;
    }

    void remove(const T& val) {
        m_root = removeHelper(val, m_root);
    }

    Node<T>* getMin()
    {
        return leftmost(m_root);
    }

    int getHeight() {
        return getHeightHelper(m_root);
    }

    void print() {
        printHelper(m_root);
    }

    bool validate() {
        return validateHelper(m_root, nullptr, nullptr);
    }
};