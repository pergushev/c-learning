#include <stdio.h>

int main() {
    char text[] = "Privet";
    int length = 0;

    // 1. Найдём длину строки вручную (до \0)
    while (text[length] != '\0') {
        length++;
    }

    // 2. Перевернём строку
    for (int i = 0; i < length / 2; i++) {
        char temp = text[i];
        text[i] = text[length - 1 - i];
        text[length - 1 - i] = temp;
    }

    printf("Перевёрнутая строка: %s\n", text);
    return 0;
}