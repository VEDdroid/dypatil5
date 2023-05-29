#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main()
{
    int size = 10;
    vector<int> arr(size);
    omp_set_num_threads(10);
    // Initialize the array
    for (int i = 0; i < size; i++)
    {
        arr[i] = i + 1;
    }

    int min_val = arr[0];
    int max_val = arr[0];
    int sum_val = 0;

    double startTime = omp_get_wtime();
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum_val)
    for (int i = 0; i < size; i++)
    {
        printf("Thread ID = %d, i = %d\n", omp_get_thread_num(), i);

        min_val = min(min_val, arr[i]);
        max_val = max(max_val, arr[i]);
        sum_val += arr[i];
    }

    double avg_val = static_cast<double>(sum_val) / size;
    double endTime = omp_get_wtime();

    cout << "Minimum: " << min_val << endl;
    cout << "Maximum: " << max_val << endl;
    cout << "Sum: " << sum_val << endl;
    cout << "Average: " << avg_val << endl;
    cout << "Total Time Taken: " << endTime - startTime << " seconds" << endl;

    return 0;
}
