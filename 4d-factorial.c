#include <stdio.h>

int main() {
    int num = 7;
    int fl = 1;

    for (int i = 1; i <= num; i++) {
        fl = fl * i;
    }

    printf("Факториал числа %d: %d\n", num, fl);

    return 0;
}