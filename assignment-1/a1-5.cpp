#include <iostream>

using namespace std;

// We have defined a Stack class with the required functions to be used in the problem
class Stack {
    int* arr;
    int top;
    int capacity;

    public:
    
        Stack(int size) { // The constructor has been defined for you
             if (size <= 0) {
                cout << "Invalid Input" << endl;
                exit(0);
             }
            arr = new int[size];
            capacity = size;
            top = -1;
        }

        ~Stack() {
            delete[] arr;
        }

        // Function to add an element to the stack
        void push(int x) {
           if (!isFull()) {
                arr[++top] = x;
            } 
            else{
                cout << "Stack Overflow";
            }
        }

        // Function to pop the top element
        int pop() {
            if(!isEmpty()){
                return arr[top--];
            }
            else {
                cout << "Stack Underflow";
                return -1;
            }
        }
        

        // Function to display the elements of the stack
        void display() const {
            if (isEmpty()) {
                cout << "Empty";
            } else {
                for (int i = 0; i <= top; i++) {
                    cout << arr[i] << " ";
                }
            }
            cout << endl;
        }

    private:
    
        // Function to check if the stack is full
        bool isFull() const {
            return (top==capacity-1);
        }

        // Function to check if the stack is empty
        bool isEmpty() const {
            return (top== -1);
        }

};

// Stacks have been defined globally for the towers A, B, and C for printing the towers at each step
Stack* A;
Stack* B;
Stack* C;

// Function to display the contents of the towers
void displayTowers() {
    cout << "Tower A: ";
    A->display();
    cout << "Tower B: ";
    B->display();
    cout << "Tower C: ";
    C->display();
    cout << "\n";
}

void rearrangeDisks(int n, Stack& A, Stack& B, Stack& C, char from, char to, char aux) {
    //base case when there is only one disk
    if (n == 1) {
        int disk = A.pop();
        C.push(disk);//remove and put the disk to C 
        cout << "Move disk " + to_string(disk) + " from " + from + " to " + to + "\n";
        displayTowers();
        return;
    }
    rearrangeDisks(n - 1, A, C, B, from, aux, to);  // Move n-1 disks to B
    rearrangeDisks(1, A, B, C, from, to, aux);      // Move the nth disk to C
    rearrangeDisks(n - 1, B, A, C, aux, to, from);  // Move n-1 disks from B to C 
}

int main() { // The main function has been defined for you, do not edit anything here.
    int n;
    //cout << "Enter the number of disks: ";
    cin >> n;
    if (cin.fail()) {
        cout << "Invalid input" << endl; 
        return 1; 
    }

    A = new Stack(n);
    B = new Stack(n);
    C = new Stack(n);

    for (int i = n; i >= 1; i--) {
        A->push(i);
    }

    displayTowers();

    rearrangeDisks(n, *A, *B, *C, 'A', 'C', 'B');

    delete A;
    delete B;
    delete C;

    return 0;
}
