#include "s21_string.h"
#include <string.h>
#include <stdarg.h>
#include <math.h>

typedef struct {
    char flag;
    int width;
    int accuracy;
    char type;
} spec;

int s21_sprintf(char * str, const char * format, ...);
int searchModifiersForString(int x, const char * format, spec * config, va_list * params);
char * insertStringBySpecifier(char * str, char symbol, spec config, va_list * params);
char * s21_itoa(char * str, int number);
char * s21_reverse(char * str);
char * s21_i16toa(char * str, int number);

void s21_itoi(char * str, int * len, int number) {
    // s21_itoa(str, len, number < 0 ? (- number) : number);
    number < 0 ? str[*len += 1] = '-' : 0;
    str[*len + 1] = '\0';
}
void s21_ftoi(char * str, int * len, double remainder) {
    remainder < 0 ? remainder *= (-1) : 0;
    // s21_itoa(str, len, ((int) (remainder * pow(10, 6))));
    str[*len += 1] = '.';
    str[*len += 1] = '\0';
}
int insertSpecifier(char * str, char symbol, va_list * param) {
    int status = 1, len = 0;
    if (symbol == '%') {
        str[len] = '%';
        str[len + 1] = '\0';
    } else if (symbol == 'c') {
        str[len] = va_arg(*param, int);
        str[len + 1] = '\0';
    } else if (symbol == 'd' || symbol == 'i') {
        // s21_itoi(str, &len, va_arg(*param, int));
        s21_reverse(str);
    } else if (symbol == 'f') {
        double number = va_arg(*param, double);
        // s21_ftoi(str, &len, (number - ((int) number)));
        // s21_itoi(str, &len, (int) number);
        s21_reverse(str);
    } else if (symbol == 's') {
        strcpy(str, va_arg(*param, char *));
    } else if (symbol == 'u') {
        // s21_utoi(str, &len, va_arg(*param, int));
        s21_reverse(str);
    } else {
        status = 0;
    }
    return status;
}
int extractFormat(const char * str, int pos, char * format) {
    int lenFormat = 0;
    for (; strchr("1234567890-+", str[pos]); lenFormat += 1, pos += 1)
        format[lenFormat] = str[pos];
    format[lenFormat] = *strchr("cdifsu%%", str[pos]);
    format[lenFormat += 1] = '\0';
    return lenFormat;
}
void insertModifications(char * str, char * forma) {
    int lenForma = strlen(forma);
    for (int x = 0; x < lenForma - 1; x += 1) {
        if (forma[x] == '+' && strchr("dif", forma[lenForma])) {
            if (str[0] != '-') {
                char aux[100] = "+";
                strcat(aux, str);
                strcpy(str, aux);
            }
        } else if (forma[x] == ' ' && strchr("dif", forma[lenForma])) {
            char aux[100] = " ";
            strcat(aux, str);
            strcpy(str, aux);
        } else if (forma[x] == '-'  && strchr("ciu", forma[lenForma])) {
            char aux[100] = " ";
            int result = 0;
            for (int y = 0; strchr("123456789", forma[x + 1]); y += 1)
                result = forma[x += 1] - '0';
            for (int y = 0; y < result; y += 1)
                aux[y] = ' ';
            strcat(str, aux);
        } else if (strchr("1234567890", forma[x])) {
            char aux[100] = " ";
            int result = 0;
            for (int y = 0; strchr("123456789", forma[x]); y += 1, x += 1) {
                // printf("QTE - %c\n", forma[x]);
                // здесь нужно написать код так, чтоб он преобразовал многозначные числа (5 5 5)
                result = forma[x + 1];
            }
            for (int y = 0; y < result; y += 1) {
                aux[y] = ' ';
                aux[y + 1] = '\0';
            }
            // printf("TEST - %d\n", result);
            strcat(aux, str);
            strcpy(str, aux);
        } else if (forma[x] == '.') {

        }
    }
}

int s21_sprintf(char * str, const char * format, ...) {

    str[0] = '\0';
    va_list params;
    va_start(params, format);

    // TODO:
    // необходим код, который будет создавать копию str,
    // типа если в конце программы будет ошибка, то изначальная
    // переменная должна остаться в том же виде.
    // а нужно ли? вроде как говорили, что проверка на правильность не делается.

    for (int x = 0; format[x] != '\0'; x += 1) {

        if (format[x] == '%') {

            spec config = {'0', 0, 0, '0'};
            x = searchModifiersForString(x, format, &config, &params);            
            // printf("%% | %c | %d | .%d | %c | %c\n", config.flag, config.width, config.accuracy, config.type, format[x]);
            insertStringBySpecifier(str, format[x], config, &params);

        } else {
            int lenStr = strlen(str);
            str[lenStr] = format[x];
            str[lenStr + 1] = '\0';
        }

    }

    return 1;
}

int searchModifiersForString(int x, const char * format, spec * config, va_list * params) {
    for (x += 1; strchr("-+ #0", format[x]); x += 1)
        config -> flag = format[x];
    for (; strchr("0123456789", format[x]); x += 1)
        config -> width = (config -> width * 10) + (format[x] - 48);
    for (; format[x] == '*'; x += 1)
        config -> width = va_arg(*params, int);
    if (format[x] == '.') {
        for (; strchr("0123456789", format[x += 1]); x += 1)
            config -> accuracy = (config -> accuracy * 10) + (format[x] - 48);
        for (; format[x] == '*'; x += 1)
            config -> accuracy = va_arg(*params, int);
    }
    for (; strchr("hlL", format[x]); x += 1)
        config -> type = format[x];
    return x;
}

char * insertStringBySpecifier(char * str, char symbol, spec config, va_list * params) {
    // TODO: нужно здесь создать маллок строку
    char storage[1000] = "\0";
    switch (symbol) {
        case 'c':
            int lenStr = strlen(str);
            str[lenStr] = va_arg(*params, int);
            str[lenStr + 1] = '\0';
            break;
        case 'd':
        case 'i':
            strcat(str, s21_reverse(s21_itoa(storage, va_arg(*params, int))));
            break;
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':
            va_arg(*params, double);
            break;
        case 's':
            strcat(str, va_arg(*params, char *));
            break;
        case 'o':
        case 'u':
        case 'x':
        case 'X':
            va_arg(*params, int);
            break;
        case 'p':
            break;
        case 'n':
            va_arg(*params, int);
            break;
        case '%':
            strcat(str, "%");
            break;
    }
    return str;
}

char * s21_reverse(char * str) {
    int lenStr = strlen(str) - 1;
    for (int x = 0; x < (lenStr / 2); x += 1) {
        char aux = str[x];
        str[x] = str[lenStr - x];
        str[lenStr - x] = aux;
    }
    return str;
}

char * s21_itoa(char * str, int number) {
    int lenStr = strlen(str);
    for (; (number / 10) != 0; number /= 10, lenStr += 1)
        str[lenStr] = number > 0 ? (number % 10) + '0' : ((-number) % 10) + '0';
    str[lenStr] = number > 0 ? number + '0' : (-number) + '0';
    str[lenStr + 1] = '\0';
    return str;
}

char * s21_i16toa(char * str, int number) {
    int lenStr = strlen(str);
    number = number < 0 ? (INT_MAX + number + 1) : number;
    printf("T - %d\n", number);
    for (; (number / 0x10) != 0; number /= 0x10, lenStr += 1) {
        printf("TEST - %d\n", number % 0x10);
        str[lenStr] = (number % 0x10) < 10 ? (number % 0x10) + '0' : ((number %0x10) - 10) + 97;

    }
    printf("TEST_LAST - %d\n", number);
    str[lenStr] = number < 10 ? number + '0' : number + 97;
    str[lenStr + 1] = '\0';
}

int main() {
    
    char TEST_MESSAGE[500] = "Hello, World!!";

    char TEST_c = '5';
    int TEST_d = 123;
    int TEST_i = 321;
    double TEST_e = 101.753;
    double TEST_E = 101.753;
    double TEST_f = 101.753;
    double TEST_g = 5.753;
    double TEST_G = 5.753;
    int TEST_o = 777;
    char TEST_s[100] = "CHAMOMIL VAMIRYN";
    int TEST_u = 999;
    int TEST_x = 999;
    int TEST_X = INT_MIN + 1;
    int TEST_p = 999;
    int TEST_n = 999;

    int width = 5;

    sprintf(TEST_MESSAGE, "%c|%d|%i|%e|%E|%f|%.*g|%G|%o|%s|%u|%x|%X|%p|%n|%%", 
        TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, width, TEST_g, TEST_G, TEST_o, 
        TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n);
    printf("ORIGINAL - |%s| - %d\n", TEST_MESSAGE, TEST_n);   
    s21_sprintf(TEST_MESSAGE, "%c|%d|%i|%e|%E|%f|%.*g|%G|%o|%s|%u|%x|%X|%p|%n|%%", 
        TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, width, TEST_g, TEST_G, TEST_o, 
        TEST_s, TEST_u, TEST_x, TEST_X, TEST_X, &TEST_n);
    printf("__FAKE__ - |%s| - %d\n", TEST_MESSAGE, TEST_n);

    s21_i16toa(TEST_MESSAGE, TEST_X);
    printf("TEST FUNC - %s|\n", TEST_MESSAGE);

    int TEST = 555;
    int * TEST_piz = &TEST;
    printf("Z - %p - %p - %p\n", TEST, TEST_piz, *TEST_piz);
    for (int * x = &TEST, z = 0; z < 13 ; *x = (((size_t)*x) >> 4), z += 1) {
        unsigned int aux = ((size_t) *x) % 0x10;
        aux < 10 ? printf("%c", ('0' + aux)) : printf("%c", ('a' + (aux - 10))); 
    }
    printf("TEST = %d", TEST);

    return 0;
}
