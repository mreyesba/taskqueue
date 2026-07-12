#pragma once

#include <tuple>
#include <iostream>

struct Task {
    int priority;
    int taskId;
    int userId;
    Task* left;
    Task* right;

    Task() = default; 
    
    Task(int taskId, int userId, int priority) : taskId(taskId), userId(userId), priority(priority) {}
    Task(int taskId) : taskId(taskId) {}
    
    Task(Task* task) {
        if (task != nullptr)
        {
            priority = task->priority;
            taskId = task->taskId;
            userId = task->userId;
        }
        else
        {
            priority = 0;
            taskId = 0;
            userId = 0;
        }
    }

    bool operator<(const Task& other) const {
        return std::tie(priority, taskId, userId) < 
               std::tie(other.priority, other.taskId, other.userId);
    }

    bool operator>(const Task& other) const {
        return other < *this; // Reuses the < operator logic cleanly
    }

    bool operator==(const Task& other) const {
        return std::tie(priority, taskId, userId) == 
               std::tie(other.priority, other.taskId, other.userId);
    }

    void print() const {
        std::cout << "taskId: " << this->taskId << ", usedId: " << this->userId << ", priority: " << this->priority << "\n";
    }
};

int compare(Task* first, Task* second);
