#include <stdio.h>

int square(int x) { return x * x; }

// Функция принимает массив и его размер
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Функция изменяет массив (+1 к элементу)
void increment_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] += 1;
    }
}

int main() {
    int result = square(5);
    printf("%d\n", result);

    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("До: ");
    print_array(numbers, size);

    increment_array(numbers, size);

    printf("После: ");
    print_array(numbers, size);

    return 0;
}