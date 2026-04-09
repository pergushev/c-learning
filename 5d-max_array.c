#include <stdio.h>

int main() {
    int numbers[] = {42, 17, 88, 23, 99, 11, 64};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    int max = numbers[0];
    int max_index = 0;

    for (int i = 1; i < size; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
            max_index = i;
        }
    }

    printf("Максимум: %d на позиции: %d\n", max, max_index + 1);

    return 0;
}