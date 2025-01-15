#include <iostream>
#include <limits>
using namespace std;

void findMaxSubarray(int A[], int low, int high, int& resultLow, int& resultHigh, int& resultSum);
void findMaxCrossSubarray(int A[], int low, int mid, int high, int& resultLow, int& resultHigh, int& resultSum);

void printSubarray(int A[], int low, int high) {
    cout << "Subarray: [ ";
    for (int i = low; i <= high; i++) {
        cout << A[i] << " ";
    }
    cout << "]" << endl;
}

void findMaxSubarray(int A[], int low, int high, int& resultLow, int& resultHigh, int& resultSum) {
    if (high == low) {
        resultLow = low;
        resultHigh = high;
        resultSum = A[low];
    } else {
        int mid = (low + high) / 2;

        int leftLow, leftHigh, leftSum;
        findMaxSubarray(A, low, mid, leftLow, leftHigh, leftSum);
        cout << "Left subarray max sum: " << leftSum << endl;
        printSubarray(A, leftLow, leftHigh);

        int rightLow, rightHigh, rightSum;
        findMaxSubarray(A, mid + 1, high, rightLow, rightHigh, rightSum);
        cout << "Right subarray max sum: " << rightSum << endl;
        printSubarray(A, rightLow, rightHigh);

        int crossLow, crossHigh, crossSum;
        findMaxCrossSubarray(A, low, mid, high, crossLow, crossHigh, crossSum);
        cout << "Cross subarray max sum: " << crossSum << endl;
        printSubarray(A, crossLow, crossHigh);

        cout << "Sum of left and right max: " << leftSum + rightSum << endl;

        if (leftSum >= rightSum && leftSum >= crossSum) {
            resultLow = leftLow;
            resultHigh = leftHigh;
            resultSum = leftSum;
        } else if (rightSum >= leftSum && rightSum >= crossSum) {
            resultLow = rightLow;
            resultHigh = rightHigh;
            resultSum = rightSum;
        } else {
            resultLow = crossLow;
            resultHigh = crossHigh;
            resultSum = crossSum;
        }
    }
}

void findMaxCrossSubarray(int A[], int low, int mid, int high, int& resultLow, int& resultHigh, int& resultSum) {
    int leftSum = numeric_limits<int>::min();
    int sum = 0;
    int maxLeft;

    for (int i = mid; i >= low; i--) {
        sum += A[i];
        if (sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }

    int rightSum = numeric_limits<int>::min();
    sum = 0;
    int maxRight;

    for (int j = mid + 1; j <= high; j++) {
        sum += A[j];
        if (sum > rightSum) {
            rightSum = sum;
            maxRight = j;
        }
    }

    resultLow = maxLeft;
    resultHigh = maxRight;
    resultSum = leftSum + rightSum;
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    int* arr = new int[size]; 

    for (int i = 0; i < size; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> arr[i];
    }

    int resultLow, resultHigh, resultSum;
    findMaxSubarray(arr, 0, size - 1, resultLow, resultHigh, resultSum);

    cout << "The maximum sum is: " << resultSum << endl;
    cout << "Subarray indices: [" << resultLow << ", " << resultHigh << "]" << endl;
    printSubarray(arr, resultLow, resultHigh);

    delete[] arr; 
    return 0;
}
