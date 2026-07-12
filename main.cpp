#include <iostream>
#include "task.h"
#include "bst.h"
#include "avl.hpp"
#include "testqueue.hpp"

int main() {
    std::cout << "Create and initialize tree" << '\n';

    //BST* tree = new BST();

    AVLTree<Task>* tree = new AVLTree<Task>();

    tree->add(Task(1, 1, 1));
    tree->add(Task(2, 2, 2));
    tree->add(Task(3, 3, 3));
    tree->add(Task(6, 6, 6));
    tree->add(Task(7, 7, 7));
    tree->add(Task(11, 11, 11));
    tree->add(Task(12, 12, 12));
    tree->add(Task(13, 13, 13));
    tree->add(Task(16, 16, 16));
    tree->add(Task(17, 17, 17));

    std::cout << "V1" << '\n';

    tree->print();

    std::cout << "Validate: " << tree->validate() << '\n';

    std::cout << "Height: " << tree->getHeight() << '\n';

    tree->remove(Task(5, 5, 5));

    tree->remove(Task(7, 7, 7));

    std::cout << "V2" << '\n';

    tree->print();

    std::cout << "Validate: " << tree->validate() << '\n';

    std::cout << "Height: " << tree->getHeight() << '\n';

    TaskQueue queue;

    std::cout << "--- Phase 1: Sequential Insertion ---\n";
    // This ascending pattern causes regular BSTs to completely degrade (Height = 5)
    queue.addTask(Task(10, 1, 1));
    queue.addTask(Task(20, 2, 2));
    queue.addTask(Task(30, 3, 3));
    queue.addTask(Task(40, 4, 4));
    queue.addTask(Task(50, 5, 5));

    std::cout << "--- Phase 2: Interleaved Priority Updates ---\n";
    // Change Task 20's priority to be the highest absolute element (Priority 10)
    queue.updatePriority(20, 10);

    std::cout << "\nExecuting Dispatch Pipeline Loop:\n";
    while (queue.hasNext()) {
        Task t = queue.execute();
        std::cout << "[EXECUTED] ";
        t.print();
    }

    return 0;
}