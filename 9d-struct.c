#include <stdio.h>
#include <stdlib.h>

// 1. Объявление структуры
struct Point {
    int x;
    int y;
};

int main(void) {
    // 2. Создание экземпляра
    struct Point p1;          // Статически
    struct Point *p2 = NULL;  // Указатель (для динамической памяти)

    // 3. Доступ к полям через точку (.)
    p1.x = 10;
    p1.y = 20;
    printf("Точка: (%d, %d)\n", p1.x, p1.y); // (10, 20)

    // 4. Доступ через стрелку (->) для указателей
    p2 = (struct Point *)malloc(sizeof(struct Point));
    if (p2 != NULL) {
        p2->x = 30;     // Эквивалентно (*p2.x = 30)
        p2->y = 40;
        printf("Точка 2: (%d, %d)\n", p2->x, p2->y); // (30, 40)
        free(p2);
    }

    return 0;
}

