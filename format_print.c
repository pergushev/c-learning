#include <stdio.h>

/* Комментарии */

int main() {
    /*    double pi = 3.1415926;
        double minus_e = -2.71828182;
        int n = 1948;*/
    char chr1 = '"', chr2 = '\'', chr3 = '\\', chr4 = '?';

    /*    printf("|%+8d|\n", n);           //|   +1948|

        printf("|%-+8.3f|\n", pi);       //|+3.142  |

        printf("|%+8.3f|\n", minus_e);   //|  -2.718|
    */
    printf("%c\t %c\t %c\t %c\t\n", chr1, chr2, chr3, chr4);

    return 0;
}