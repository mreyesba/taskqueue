#include "task.h"
#include <iostream>

class BST {
private:
    Task* m_root;

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

        return res;
    }

public:
    BST() {
        m_root = nullptr;
    }

    ~BST() {
        deleteTree(m_root);
    }

    void add(int taskId, int userId, int priority) {
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

    Task* find(int taskId, int userId, int priority)
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

    void remove(int taskId, int userId, int priority) {
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
                    m_root = nullptr;
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
    }

    int get_height() {
        return 0;
    }
};