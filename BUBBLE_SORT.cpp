#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

void sequentialBubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void parallelBubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        #pragma omp parallel for
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int size;
    cout << "Enter the total number of elements: ";
    cin >> size;
    if (size <= 0) {
        cout << "Invalid number of elements. Exiting program." << endl;
        return 0;
    }

    int arr[size];

    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1 ;
    }

    // Make a copy of the original array for parallel algorithm
    int arrCopy[size];
    for (int i = 0; i < size; ++i) {
        arrCopy[i] = arr[i];
    }

    // Measure sequential algorithm performance
    double startTime = omp_get_wtime();
    sequentialBubbleSort(arr, size);
    double endTime = omp_get_wtime();

    cout << "Sequential algorithm performance: " << endTime - startTime << " seconds" << endl;

    // Measure parallel algorithm performance
    startTime = omp_get_wtime();
    parallelBubbleSort(arrCopy, size);
    endTime = omp_get_wtime();

    cout << "Parallel algorithm performance: " << endTime - startTime << " seconds" << endl;

    //cout << "Sorted Array: ";
    //printArray(arr, size);

    return 0;
}
