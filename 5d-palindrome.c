#include <stdio.h>

int main() {
    int length = 0;
    char target[] = "level";
    int is_pal = 1;

    while (target[length] != '\0') {
        length++;
    }

    for (int i = 0; i < length / 2; i++) {
        if (target[i] != target[length - 1 - i]) {
            is_pal = 0;
            break;
        }
    }

    if (is_pal) {
        printf("Строка: \"%s\" палиндром\n", target);
    } else {
        printf("Строка: \"%s\" не палиндром\n", target);
    }

    return 0;
}