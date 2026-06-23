#include "task.h"
#include <iostream>

class BST {
private:
    Task* m_root;

    void deleteTree(Task* root);

    Task* leftmost(Task* root);

    Task* rearrangeSubTree(Task* root);

public:
    BST();

    ~BST();

    void add(int taskId, int userId, int priority);

    Task* find(int taskId, int userId, int priority);

    void remove(int taskId, int userId, int priority);

    int get_height();
};