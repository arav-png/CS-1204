#include <iostream>
#include "scheduler.cpp"
// this is only for you to test your code. this need not be submitted.
int main() {
    Heap heap;
    heap.insert(3);
    heap.insert(10);
    heap.insert(7);
    heap.insert(5);
    heap.print();
    int a = heap.extractMax();
    std::cout << "Extrtacted max value: " << a << std::endl;
    int b = heap.peekMax();
    std::cout << "Peek max value: " << b << std::endl;
    heap.print();
    heap.insert(18);
    heap.print();
    // Format - {id”: ”Assignment1”, ”weightage”: 5, ”deadline”: 10, ”execution time”: 3}
    std::vector<Assignment> assignments = {
        Assignment("Assignment1", 5, 10, 3),
        Assignment("Assignment2", 10, 2, 1),
        Assignment("Assignment3", 7, 5, 2),
        Assignment("Assignment4", 8, 8, 4)
    };
    AssignmentScheduler scheduler;
    scheduler.scheduleAssignments(assignments);
    scheduler.printResults();
    return 0;
}