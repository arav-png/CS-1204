#include <iostream>
#include <algorithm> // For std::swap
using namespace std;

// Define maximum size for the combined array
const int MAX_SIZE = 160;
int five_median(int arr[], int left, int right) {
    int size = right - left + 1;
    for (int i = left; i <= right; ++i) {
        for (int j = i + 1; j <= right; ++j) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
    return arr[left + size / 2]; // Return the median
}

int part(int arr[], int left, int right, int pivot) {
    for (int i = left; i <= right; i++) {
        if (arr[i] == pivot) {
            swap(arr[i], arr[right]); // Move the pivot to the end 
            break;
        }
    }

    int pivot_index = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[pivot_index]); // Move smaller elements to the left
            pivot_index++;
        }
    }
    swap(arr[pivot_index], arr[right]); // Move the pivot to its final place
    return pivot_index; 
}

int kthSmallest(int arr[], int left, int right, int k) {
    if (right - left + 1 <= 5) {
        return five_median(arr, left, right);
    }

    // Divide the array into groups of 5 and find medians
    int num_medians = (right - left + 1 + 4) / 5; // Number of medians
    int medians[32]; // Assuming the maximum number of groups of 5 is 32

    for (int i = 0; i < num_medians; i++) {
        int left_group = left + i * 5;
        int right_group = min(left_group + 4, right);
        medians[i] = five_median(arr, left_group, right_group);
    }

    int medianOfMedians = kthSmallest(medians, 0, num_medians - 1, num_medians / 2);
    int pivotIndex = part(arr, left, right, medianOfMedians);

    int pivotDist = pivotIndex - left;

    if (pivotDist == k) {
        return arr[pivotIndex];
    } else if (pivotDist > k) {
        return kthSmallest(arr, left, pivotIndex - 1, k);
    } else {
        return kthSmallest(arr, pivotIndex + 1, right, k - pivotDist - 1);
    }
}

double findMedian(int arr1[], int size1, int arr2[], int size2) {
    if (size1 == 0 && size2 == 0) {
        cout << "Empty Array"; // Print an empty array
        return -1; 
    }
    int arr[size1+size2]; // Combined array with a maximum size

    // Add elements from the first array to the combined array
    for (int i = 0; i < size1; i++) {
        arr[i] = arr1[i];
    }
    // Add elements from the second array
    for (int i = 0; i < size2; i++) {
        arr[size1 + i] = arr2[i];
    }

    int size = size1 + size2; // Total size of the combined array

    if (size % 2 == 1) {
        return kthSmallest(arr, 0, size - 1, size / 2);
    } else {
        int leftMedian = kthSmallest(arr, 0, size - 1, size / 2 - 1);
        int rightMedian = kthSmallest(arr, 0, size - 1, size / 2);
        return (leftMedian + rightMedian) / 2.0;
    }
}

int main() {
    // You can use cout statements, but ensure that you submit after commenting them out, as the autograder will otherwise mistake it for your actual output
    // Everything else in the main function remains unchanged
    
    int size1;
    //cout << "Enter the size of the array1: ";
    cin >> size1;

    int arr[size1];
    //cout << "Enter " << size1 << " elements:" << endl;
    for (int i = 0; i < size1; ++i) {
        cin >> arr[i];
    }

    // cout << "The array elements are: ";
    // for (int i = 0; i < size1; ++i) {
    //     cout << arr[i] << " ";
    // }
    // cout << endl;

    int size2;
    //cout << "Enter the size of the array2: ";
    cin >> size2;

    int arr1[size2];
    // cout << "Enter " << size2 << " elements:" << endl;
    for (int i = 0; i < size2; ++i) {
        cin >> arr1[i];
    }

    // cout << "The array elements are: ";
    // for (int i = 0; i < size2; ++i) {
    //     cout << arr1[i] << " ";
    // }
    // cout << endl;
    //if (median!=0){
        //cout << "Median = " << findMedian(arr, size1, arr1, size2) << endl; // do not comment this out
    double median = findMedian(arr, size1, arr1, size2);
    if (median != -1) {
        cout << "Median = " << median << endl;
    }
    return 0;
    }
    
    


