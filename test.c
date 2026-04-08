#include <stdio.h>
#include <unistd.h> // for sleep

int main(void) {
     for (int i = 0; i <= 10; i++) {
        
        // \r возвращает курсор в начало — перезаписываем строку
        printf("\rПрогресс: [");

        for (int j = 0; j < i; j++) printf("#");
        for (int j = i; j < 10; j++) printf(".");
        
        
        printf("] %d%%", i * 10);
        fflush(stdout);
        sleep(1);
    }

    printf("\nГотово!\n");

    /* int j = 0;
    int is_flag = 1;
    int arr[1000] = {0};

    while (is_flag) {
        if (scanf("%d", (arr + j)) != 1) {
        printf("n/a");
        return 0;
        } else if (*(arr + j) == -1) {
            is_flag = 0;
        }
        j++;
    }

    for (int i = j - 2; i >= 0; i--) {
        if (i == 0) {
            printf("%d", arr[i]);
        } else {
            printf("%d ", arr[i]);
        }
    } */

    return 0;
}