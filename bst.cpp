#include "task.h"
#include <iostream>
#include "bst.h"
#include <algorithm>

void deleteTree(Task* root)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->left != nullptr)
    {
        deleteTree(root->left);
    }

    if (root->right != nullptr)
    {
        deleteTree(root->right);
    }

    delete root;
}

Task* leftmost(Task* root)
{
    Task* cur = root;

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

Task* rearrangeSubTree(Task* root)
{
    Task* cur = root;
    Task* res = nullptr;
    Task* leftmostRight = nullptr;

    if (cur == nullptr)
    {
        return res;
    }

    if (cur->left == nullptr)
    {
        return cur->right;
    }

    if (cur->right == nullptr)
    {
        return cur->left;
    }

    leftmostRight = leftmost(cur->right);

    if (leftmostRight == nullptr)
    {
        std::cout << "This should never happen!" << '\n';
        return nullptr;
    }

    leftmostRight->left = cur->left;
    res = cur->right;
    cur->left = nullptr;
    cur->right = nullptr;

    return res;
}

BST::BST() {
    m_root = nullptr;
}

BST::~BST() {
    deleteTree(m_root);
}

void BST::add(int taskId, int userId, int priority) {
    Task* cur = m_root;
    Task* newNode = nullptr;

    if (taskId == 0)
    {
        return;
    }

    newNode = new Task(taskId, userId, priority);

    if (cur == nullptr)
    {
        m_root = newNode;
        return;
    }

    while (cur != nullptr)
    {
        if (cur->priority == newNode->priority &&
            cur->taskId == newNode->taskId &&
            cur->userId == newNode->userId)
        {
            delete newNode;
            return;
        }

        if (cur->priority > newNode->priority || 
            (cur->priority == newNode->priority &&
             cur->taskId > newNode->taskId) ||
            (cur->priority == newNode->priority &&
             cur->taskId == newNode->taskId &&
             cur->userId > newNode->userId))
        {
            if (cur->left == nullptr)
            {
                cur->left = newNode;
                return;
            }

            cur = cur->left;
            continue;
        }

        if (cur->priority < newNode->priority || 
            (cur->priority == newNode->priority &&
             cur->taskId < newNode->taskId) ||
            (cur->priority == newNode->priority &&
             cur->taskId == newNode->taskId &&
             cur->userId < newNode->userId))
        {
            if (cur->right == nullptr)
            {
                cur->right = newNode;
                return;
            }

            cur = cur->right;
            continue;
        }
    }
}

Task* BST::find(int taskId, int userId, int priority)
{
    Task* cur = m_root;

    if (cur == nullptr)
    {
        return nullptr;
    }

    while (cur != nullptr)
    {
        if (cur->priority == priority &&
            cur->taskId == taskId &&
            cur->userId == userId)
        {
            return cur;
        }

        if (cur->priority > priority || 
            (cur->priority == priority &&
             cur->taskId > taskId) ||
            (cur->priority == priority &&
             cur->taskId == taskId &&
             cur->userId > userId))
        {
            cur = cur->left;
            continue;
        }

        if (cur->priority < priority || 
            (cur->priority == priority &&
             cur->taskId < taskId) ||
            (cur->priority == priority &&
             cur->taskId == taskId &&
             cur->userId < userId))
        {
            cur = cur->right;
            continue;
        }
    }

    return nullptr;
}

void BST::remove(int taskId, int userId, int priority) {
    Task* cur = m_root;
    Task* parent = nullptr;

    if (cur == nullptr)
    {
        return;
    }

    while (cur != nullptr)
    {
        if (cur->priority == priority &&
            cur->taskId == taskId &&
            cur->userId == userId)
        {
            if (parent != nullptr)
            {

                // Check delegation logic
                if (cur == parent->right)
                {
                    parent->right = rearrangeSubTree(cur);
                }
                else
                {
                    parent->left = rearrangeSubTree(cur);
                }
            }
            else
            {
                m_root = parent->left = rearrangeSubTree(cur);;
            }

            delete cur;

            return;
        }

        if (cur->priority > priority || 
            (cur->priority == priority &&
             cur->taskId > taskId) ||
            (cur->priority == priority &&
             cur->taskId == taskId &&
             cur->userId > userId))
        {
            parent = cur;
            cur = cur->left;
            continue;
        }

        if (cur->priority < priority || 
            (cur->priority == priority &&
             cur->taskId < taskId) ||
            (cur->priority == priority &&
             cur->taskId == taskId &&
             cur->userId < userId))
        {
            parent = cur;
            cur = cur->right;
            continue;
        }
    }
}

void printHelper(Task* node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->left)
    {
        printHelper(node->left);
    }

    std::cout << "taskId: " << node->taskId << ", usedId: " << node->userId << ", priority: " << node->priority << "\n";

    if (node->right)
    {
        printHelper(node->right);
    }
}

void BST::print() {
    printHelper(m_root);
}

int getHeightHelper(Task* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return std::max(getHeightHelper(root->left), getHeightHelper(root->right)) + 1;
}

int BST::getHeight() {
    return getHeightHelper(m_root);
}