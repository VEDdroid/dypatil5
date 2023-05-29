#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

// Sequential merge function
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftArr, if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArr, if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Sequential merge sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Parallel merge sort function
void parallelMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, left, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, right);
        }

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Print the elements of the vector
void printVector(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = { 12, 11, 13, 5, 6, 7 };

    cout << "Original array: ";
    printVector(arr);

    // Sequential Merge Sort
    vector<int> sequentialArr = arr;
    mergeSort(sequentialArr, 0, sequentialArr.size() - 1);
    cout << "Sequential Merge Sort: ";
    printVector(sequentialArr);

    // Parallel Merge Sort
    vector<int> parallelArr = arr;
    parallelMergeSort(parallelArr, 0, parallelArr.size() - 1);
    cout << "Parallel Merge Sort: ";
    printVector(parallelArr);

    return 0;
}
