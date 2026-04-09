/* Реализуем массив, который автоматически растёт 
при переполнении (аналог std::vector в C++). */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;      // Указатель на данные
    int size;       // Текущее количество элементов
    int capacity;   // Выделенная память (максимум без realloc)
} DynamicArray;

//
DynamicArray* create_array(int inital_capacity) {
    DynamicArray *arr = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (arr == NULL) return NULL;

    arr->data = (int *)malloc(inital_capacity * sizeof(int));
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }

    arr->size = 0;
    arr->capacity = inital_capacity;
    return arr;
}

// Добавить элемент (автоматически расширяет при необходимости)
void push(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {

        int new_capacity = arr->capacity * 2;
        int *new_data = (int *)realloc(arr->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            fprintf(stderr, "Ошибка расширения памяти!\n");
            return;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
        printf("Массив расширен до %d элементов\n", new_capacity);
    }

    arr->data[arr->size] = value;
    arr->size++;
}

// Освободить всю память
void destroy_array(DynamicArray *arr) {
    free(arr->data);
    free(arr);
}

int main(void) {
    DynamicArray *arr = create_array(2);

    for (int i = 0; i <= 10; i++) {
        push(arr, i * 10);
    }

    printf("Элементы: ");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");

    destroy_array(arr);
    return 0;
}