#include <stdio.h>

void increment(int a);
void increment_ptr(int *a);
void swap (int *a, int *b);

int main() {
/*     int x = 10;
    int *ptr;   // Указатель на int

    ptr = &x;    // Взять адрес переменной x

    printf("Значение х: %d\n", x);
    printf("Адрес х: %p\n", (void*)&x);
    printf("Значение ptr: %p\n", (void*)ptr);
    printf("Значение по адресу ptr: %d\n", *ptr);

    *ptr = 99;
    printf("Теперь х = %d\n", x);

    increment(x);
    printf("По значению: %d\n", x);

    increment_ptr(&x);
    printf("По ссылке: %d\n", x); */

    int x = 10, y = 20;

    printf("До: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("После: x=%d, y=%d\n", x, y);

    //  Указатели и массивы (магия C!)

    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr; // ptr указывает на arr[0]

    // Имя массива = указатель на первый элемент!
    printf("%d\n", *arr);       // 10 (то же, что arr[0])
    printf("%d\n", *(arr + 1)); // 20 (то же, что arr[1])
    printf("%d\n", arr[2]);     // 30

    // Эквивалентность:
    // arr[i] == *(arr + i) == i[arr] (да, так тоже можно!)

    printf("%d\n", *ptr);             // 10
    printf("%d\n", *(ptr + 1));       // 20
    printf("%d\n", *(ptr + 2));       // 30

    ptr++;  // Сдвигаем указатель на 1 элемент (не на 1 байт!)
    printf("%d\n", *ptr);              //20

    return 0;
}

void increment(int a) {
    a = a + 1;
}

void increment_ptr(int *a) {
    *a = *a + 1;
}

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}