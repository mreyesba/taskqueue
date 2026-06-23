#pragma once

struct Task {
    int taskId;
    int userId;
    int priority;
    Task* left;
    Task* right;
    Task(int taskId, int userId, int priority) : taskId(taskId), userId(userId), priority(priority) {}
};

int compare(Task* first, Task* second)
{
    if (first->priority == second->priority &&
        first->taskId == second->taskId &&
        first->userId == second->userId)
    {
        return 0;
    }

    if (first->priority > second->priority || 
        (first->priority == second->priority &&
         first->taskId > second->taskId) ||
        (first->priority == second->priority &&
         first->taskId == second->taskId &&
         first->userId > second->userId))
    {
        return -1;
    }

    return 1;
}
