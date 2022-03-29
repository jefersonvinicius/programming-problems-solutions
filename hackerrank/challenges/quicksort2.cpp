#include <bits/stdc++.h>
using namespace std;

void print_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        if (i == size-1) printf("%d\n", array[i]);
        else printf("%d ", array[i]);
    }
}

void partition(int array[], int left, int right) {
    int size = right - left + 1;
    int lesser[size], bigger[size];
    int lesser_index = 0, bigger_index = 0;
    int pivot = array[left];

    for (int i = left + 1; i <= right; i++) {
        if (array[i] >= pivot) {
            bigger[bigger_index] = array[i];
            bigger_index++;
        } else {
            lesser[lesser_index] = array[i];
            lesser_index++;
        }
    }

    print_array(lesser, lesser_index);
    print_array(bigger, bigger_index);

    for (int i = 0; i < lesser_index; i++) {
        array[left+i] = lesser[i];
    }

    array[lesser_index] = pivot;

    for (int i = 0; i < bigger_index; i++) {
        array[lesser_index+i+1] = bigger[i];
    }
}

void quickSort(int array[], int left, int right) {
    printf("QuickSort\n");
    if (left < right) {
        partition(array, left + 1, right);
        // partition(array, left, right);
    }
}


int main()
{
    int n;
    cin >> n;

    int arr[n];
    for(int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr, 0, n - 1);

    return 0;
}
