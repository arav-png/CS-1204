#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;
// Custom heap
class Heap {
private:
    vector<int> heap;

    void heapifyDown(int index) { //heapify if the root is removed
        int size = heap.size();
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(int value) { //inserting a value in the heap
        heap.push_back(value);
        int index = heap.size() - 1;

        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    int extractMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        int maxElement = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return maxElement;
    }

    int peekMax() const {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }

    void print() const {
        for (int element : heap) {
            cout << element << " ";
        }
        cout << endl;
    }

    bool isEmpty() const {
        return heap.empty();
    }
};

// Assignment class definition
class Assignment {
public:
    string id;
    int weightage;
    int deadline;
    int executionTime;

    // Default constructor
    Assignment() : id(""), weightage(0), deadline(0), executionTime(0) {}

    // Parameterized constructor
    Assignment(string id, int weightage, int deadline, int executionTime)
        : id(id), weightage(weightage), deadline(deadline), executionTime(executionTime) {}

    //modifying the operator to compare weightage and deadline
    bool operator>(const Assignment& other) const {
        if (weightage == other.weightage) {
            return deadline < other.deadline;
        }
        return weightage > other.weightage;
    }
};

// AssignmentScheduler class definition
class AssignmentScheduler {
private:

    vector<Assignment> executedTasks;
    vector<string> discardedTasks;

    void heapify(vector<Assignment>& assignments, int n, int i) { 
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && assignments[left] > assignments[largest]) {
            largest = left;
        }
        if (right < n && assignments[right] > assignments[largest]) {
            largest = right;
        }
        if (largest != i) {
            swap(assignments[i], assignments[largest]);
            heapify(assignments, n, largest);
        }
    }

    void buildHeap(vector<Assignment>& assignments) {
        int n = assignments.size();
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(assignments, n, i);

        }
    }

public:
   void scheduleAssignments(vector<Assignment>& assignments) {
    
    buildHeap(assignments);

    int currentTime = 0;

    while (!assignments.empty()) {
        Assignment top = assignments[0];

        if (currentTime + top.executionTime <= top.deadline) {
            executedTasks.push_back(top);
            currentTime += top.executionTime;
        } else {
            discardedTasks.push_back(top.id); // Only store the ID
        }

        // Remove the root and rebuild the heap
        assignments[0] = assignments.back();
        assignments.pop_back();
        heapify(assignments, assignments.size(), 0);
    }
}
    void printResults() const {
    cout << "Executed Tasks: [";
    for (size_t i = 0; i < executedTasks.size(); ++i) {
        cout << "\"" << executedTasks[i].id << "\"";
        if (i < executedTasks.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    cout << "Discarded Tasks: [";
    for (size_t i = 0; i < discardedTasks.size(); ++i) {
        cout << "{\"id\": \"" << discardedTasks[i] << "\", \"reason\": \"Deadline passed\"}";
        if (i < discardedTasks.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    }
};
