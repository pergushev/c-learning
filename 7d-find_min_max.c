#include <stdio.h>

void find_min_max(int arr[], int size, int *min, int *max);

int main() {
    int data[] = {42, 17, 88, 23, 99, 11, 64};
    int size = sizeof(data) / sizeof(data[0]);
    int min_val, max_val;

    find_min_max(data, size, &min_val, &max_val);

    printf("Минимум: %d\n", min_val);
    printf("Максимум: %d\n", max_val);

    return 0;
}

void find_min_max(int arr[], int size, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}