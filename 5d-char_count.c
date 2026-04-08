#include <stdio.h>

int main() {
    char str[] = "abracadabra";
    char target = 'r';
    int count = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == target) {
            count++;
        }
        i++;
    }

    printf("Символ '%c' встречается %d раз\n", target, count);

    return 0;
}