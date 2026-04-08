#include <stdio.h>

#define MAX_SIZE 100

int read_array(int arr [], int max_size);
void reverse_array(int arr[], int size);
void print_array(int arr[], int size);
void swap(int *a, int *b);

int main(void) {
    int arr[MAX_SIZE] = {0};
    int size = read_array(arr, MAX_SIZE);

    if (size == -1 || size == 0) {
        printf("n/a");
    } else {
        reverse_array(arr, size);
        print_array(arr, size);
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

// Создает массив в обратном порядке
void reverse_array(int arr[], int size) {
    if (size <= 1) return;

    int *left = arr;
    int *right = &arr[size - 1];
    while (left < right) {
        swap(left, right);
        left++;
        right--;
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            printf("%d", arr[i]);
        } else {
            printf(" %d", arr[i]);
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}