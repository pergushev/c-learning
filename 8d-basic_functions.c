#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 1. Выделение памяти: 5 целых чисел
    int *arr = (int *)malloc(5 * sizeof(int));

    // 2. 🔒 КРИТИЧЕСКАЯ ПРОВЕРКА: удалось ли выделить память?
    if (arr == NULL) {
        fprintf(stderr, "Ошибка: не хватает памяти!\n");
        return 1;
    }

    // 3. Использование как обычного массива
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
        printf("%d ", arr[i]);
    }
    // Вывод: 0 10 20 30 40

    // 4. 🔒 ОБЯЗАТЕЛЬНО освободить память!
    free(arr);
    arr = NULL;

    return 0;
}