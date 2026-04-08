#include <stdio.h>

#define MAX_SIZE 100

int read_array(int arr [], int max_size);
void reverse_arr(int arr[], int size);

int main(void) {
    int arr[MAX_SIZE] = {0};
    int size = read_array(arr, MAX_SIZE);

    if (size != -1) {
        reverse_arr(arr, size);
    } else {
        printf("n/a");
    }

    return 0;
}

// Читает числа в массив, возвращает кол-во элементов или -1 при ошибке
int read_array(int arr[], int max_size) {
    int j = 0;
    int status = 1;
    while(j < max_size && status) {
        if (scanf("%d", &arr[j]) != 1) {
            j = -1;
            status = 0;
        } else if (arr[j] == -1) {
            status = 0;
        } else {
            j++;
        }
    }
    return j;
}

// Выводит массив в обратном порядке
void reverse_arr(int arr[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        if (i == size - 1) {
            printf("%d", arr[i]);
        } else {
            printf(" %d", arr[i]);
        }
    }
}