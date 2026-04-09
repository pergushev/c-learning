#include <stdio.h>

int main() {
    //   int scores[5];
    //   float temperatures[7];
    //   char name[10];
    //    int numbers[5] = {10, 20, 30, 40, 50};
    //    int numbers[] = {10, 20, 30, 40, 50};

    //    int numbers[5] = {10, 20};

    int scores[] = {85, 92, 78, 95, 88};
    int size = 5;

    // Вывод всех элементов
    for (int i = 0; i < size; i++) {
        printf("Оценка %d: %d\n", i + 1, scores[i]);
    }

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    printf("Средний балл: %.1f\n", (float)sum / size);

    printf("%zu\n", sizeof(scores) / sizeof(scores[0]));

    return 0;
}