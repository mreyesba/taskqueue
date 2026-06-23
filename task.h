struct Task {
    int taskId;
    int userId;
    int priority;
    Task* left;
    Task* right;
    Task(int taskId, int userId, int priority) : taskId(taskId), userId(userId), priority(priority) {}
};
