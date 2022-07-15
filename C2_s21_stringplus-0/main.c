#include "s21_string.h"
#include <string.h>
#include <locale.h>
#include <stdio.h>

int main() {

    setlocale(LC_ALL, "");
    char MESSAGE_1[512] = "TEST";
    char MESSAGE_2[512] = "TEST";

    double aux = 0.0004;

    int M1 = sprintf(MESSAGE_1, "%.g", aux);
    int M2 = s21_sprintf(MESSAGE_2, "%.g", aux);

    printf("TEST_ORIGINAL - %d - |%s|\n", M1, MESSAGE_1);
    printf("TEST_REPLICAN - %d - |%s|\n", M2, MESSAGE_2);
    printf("TEST_ITOG = %d\n", strcmp(MESSAGE_1, MESSAGE_2));

    return 1;
}
