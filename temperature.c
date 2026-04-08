#include <stdio.h>

int main() {
    float celsius = 25;

    float fahrenheit = celsius * 9 / 5 + 32;

    printf("%.1f°C = %.1f°F\n", celsius, fahrenheit);

    return 0;
}