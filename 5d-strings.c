#include <stdio.h>
#include <string.h>

int main() {
    // Способ 1: как массив символов
    // char name[6] = {'A', 'l', 'e', 'x', '\0'};

    // Саособ 2: строковый литерал (компилятор добавит \0 автоматически)
    // char name2[5] = "Alex";

    // printf("%s\n", name);
    // printf("%s\n", name2);

    char name[50];

    printf("Введите имя: ");
    // Способ 1: fgets - безоавсный (рекомендуется)
    fgets(name, sizeof(name), stdin);
    // Удаляем символ новой строки \n, если есть
    name[strcspn(name, "\n")] = '\0';

    printf("Привет, %s!\n", name);
    return 0;
}