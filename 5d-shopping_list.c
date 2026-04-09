#include <stdio.h>

int main() {
    char items[5][20] = {"milk", "bread", "eggs", "cheese", "apples"};
    int size = 5;

    printf("Список покупок:\n");
    printf("---------------\n");

    for (int i = 0; i < size; i++) {
        printf("%d. %s\n", i + 1, items[i]);
    }

    return 0;
}