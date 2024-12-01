#include <iostream>
using namespace std;

class CustomStack {
private:
    int* data;       // Array to hold stack elements
    int capacity;    // Maximum size of the stack
    int topIndex;    // Index of the top element in the stack

public:
    // Constructor to initialize the stack with a given size, default size is 8
    CustomStack(int size = 8) {
        capacity = size;
        data = new int[capacity];
        topIndex = -1;  // Initially, stack is empty
    }

    // Destructor to clean up memory
    ~CustomStack() {
        delete[] data;
    }

    // Push an element onto the stack
    void push(int value) {
        if (isFull()) {
            cout << "Stack is full, can't push " << value << "\n";
            return;
        }
        data[++topIndex] = value;
        cout << value << " added to the stack.\n";
    }

    // Pop the top element from the stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty, can't pop.\n";
            return -1;
        }
        cout << data[topIndex] << " removed from the stack.\n";
        return data[topIndex--];
    }

    // Check if the stack is empty
    bool isEmpty() {
        return topIndex == -1;
    }

    // Check if the stack is full
    bool isFull() {
        return topIndex == capacity - 1;
    }

    // Return the current number of elements in the stack
    int currentSize() {
        return topIndex + 1;
    }

    // Return the top element without removing it
    int peek() {
        if (!isEmpty()) {
            return data[topIndex];
        } else {
            cout << "No elements in the stack.\n";
            return -1;
        }
    }
};

int main() {
    CustomStack stack(6);

    // Push elements onto the stack
    stack.push(15);
    stack.push(25);
    stack.push(35);
    stack.push(45);
    stack.push(55);
    stack.push(65);  // Stack is full now

    // Show the current top item and total elements
    cout << "Top item: " << stack.peek() << "\n";
    cout << "Total elements: " << stack.currentSize() << "\n";

    // Pop two items from the stack
    stack.pop();
    stack.pop();

    // Show the new top item and total elements after removals
    cout << "Top item after removal: " << stack.peek() << "\n";
    cout << "Total elements after removal: " << stack.currentSize() << "\n";

    // Push another element to the stack
    stack.push(75);

    return 0;
}
