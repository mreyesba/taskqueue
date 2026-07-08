#pragma once

#include "task.h"
#include <iostream>

class BST {
private:
    Task* m_root;

public:
    BST();

    ~BST();

    void add(int taskId, int userId, int priority);

    Task* find(int taskId, int userId, int priority);

    void remove(int taskId, int userId, int priority);

    void print();

    int getHeight();

    bool validate();
};