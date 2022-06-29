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

char * s21_reverse(char * str);
char * s21_ptoa(char * str, int * variable);
char * s21_itoa(char * str, int number, int accuracy);
int s21_sprintf(char * str, const char * format, ...);
char * s21_conf(char * str, spec config, char symbol);
char * s21_ntoa(char * str, double number, int format);
char * s21_ftoa(char * str, double number, int afterpoint);
char * s21_utoa(char * str, unsigned int number, int format);
char * insertStringBySpecifier(char * str, char symbol, spec config, va_list * params);
int searchModifiersForString(int x, const char * format, spec * config, va_list * params);

int s21_sprintf(char * str, const char * format, ...) {
    str[0] = '\0';
    va_list params;
    va_start(params, format);

    // TODO:    1. Если возникла ошибка, то изначальная строка должна остатсья в том же виде.
    //          2. Необходимо считывать кол-во просканированных переменных.

    for (int x = 0; format[x] != '\0'; x += 1) {
        if (format[x] == '%') {
            //      1. Поменять равно на ИКС!
            spec config = {'x', INT_MIN, INT_MIN, 'x'};
            x = searchModifiersForString(x, format, &config, &params);
            insertStringBySpecifier(str + strlen(str), format[x], config, &params);
        } else {
            int lenStr = strlen(str);
            str[lenStr] = format[x];
            str[lenStr + 1] = '\0';
        }
    }
    return strlen(str);
}

int searchModifiersForString(int x, const char * format, spec * config, va_list * params) {
    for (x += 1; strchr("-+ #0", format[x]); x += 1)
        config -> flag = format[x];
    for (; strchr("0123456789", format[x]); x += 1)
        config -> width = (config -> width * 10) + (format[x] - 48);
    for (; format[x] == '*'; x += 1)
        config -> width = va_arg(*params, int);
    if (format[x] == '.') {
        for (x += 1; strchr("0123456789", format[x]); x += 1)
            config -> accuracy = (config -> accuracy * 10) + (format[x] - 48);
        for (; format[x] == '*'; x += 1)
            config -> accuracy = va_arg(*params, int);
    }
    for (; strchr("hlL", format[x]); x += 1)
        config -> type = format[x];
    return x;
}

char * insertStringBySpecifier(char * str, char symbol, spec config, va_list * params) {
    // TODO:    1. Здесь необходимо выделять память динамически.
    //          2. Необходимо обновить структуру, убрать switch.
    //          3. Нужно использовать long вместо int.
    char storage[1000] = "\0";

    switch (symbol) {
        case 'c':
            for (memmove(str + 1, str, 1), str[0] = va_arg(*params, int); 1 == 0;);
            s21_conf(str, config, symbol);
            break;
        case 'd':
        case 'i':
            s21_conf(s21_itoa(str, va_arg(*params, int), config.accuracy), config, symbol);
            break;
        case 'e':
        case 'E':
            strcat(str, s21_conf(s21_ntoa(storage, va_arg(*params, double), symbol), config, symbol));
            break;
        case 'f':
            int len = config.accuracy > 0 ? config.accuracy : 6;
            strcat(str, s21_conf(s21_ftoa(storage, va_arg(*params, double), len), config, symbol));
            break;
        case 'g':
        case 'G':
            strcat(str, s21_conf(s21_ftoa(storage, va_arg(*params, double), 5), config, symbol));
            break;
        case 's':
            strcat(str, s21_conf(va_arg(*params, char *), config, symbol));
            break;
        case 'o':
            strcat(str, s21_conf(s21_utoa(storage, va_arg(*params, unsigned int), 8), config, symbol));
            break;
        case 'u':
            strcat(str, s21_conf(s21_utoa(storage, va_arg(*params, unsigned int), 10), config, symbol));
            break;
        case 'x':
        case 'X':
            strcat(str, s21_conf(s21_utoa(storage, va_arg(*params, int), symbol == 'x' ? 32 : 16), config, symbol));
            break;
        case 'p':
            // TODO:    1. Здесь надо убрать реверс!
            strcat(str, s21_conf(s21_reverse(s21_ptoa(storage, va_arg(*params, void *))), config, symbol));
            break;
        case 'n':
            *(va_arg(*params, int *)) = strlen(str);
            break;
        case '%':
            strcat(str, "%");
            break;
    }
    return str;
}



char * s21_conf(char * str, spec config, char symbol) {

    if (config.flag != 'x' || config.width < 0 || config.accuracy < 0 || config.type != 'x') {
        if (symbol == 'p')
            strcpy(str, str + strspn(str, "0"));
        else if (strchr("gG", symbol))
            for (int x = (strlen(str) - 1); str[x] == '0'; str[x] = '\0', x -= 1);
    }

    char * aux = str;
    char filler = ' ';
    int countFill = config.width > 0 ? config.width - strlen(str) : 0;

    // if (config.flag == '+' && strchr("dieEfgG", symbol) && str[0] != '-')
    //     for (memmove(str + 1, str, strlen(str)), str[0] = '+'; 1 == 0;);
    // else if (config.flag == ' ' && strchr("dieEfgGu", symbol) && str[0] != '-')
    //     for (memmove(str + 1, str, strlen(str)), str[0] = ' '; 1 == 0;);

    // if (config.flag == '0') {
    //     aux[0] == '-' ? aux += 1 : 0;
    //     strchr("cs", symbol) ? 0 : (filler = '0');
    // } else if (config.flag == '-') {
    //     aux += strlen(aux);
    // }

    if (countFill > 0)
        for (memmove(aux + countFill, aux, strlen(aux) + 1); countFill != 0; aux[countFill - 1] = filler, countFill -= 1);

    return str;
}

char * s21_reverse(char * str) {
    int lenStr = strlen(str);
    for (int x = 0; x < (lenStr / 2); x += 1) {
        char aux = str[lenStr - 1 - x];
        str[lenStr - 1 - x] = str[x];
        str[x] = aux;
    }
    return str;
}

char * s21_ptoa(char * str, int * variable) {
    for (int * aux = variable, x = 0; x < 16; aux = ((void *) (((size_t) aux) >> 4)), x += 1) {
        unsigned int last_symbol = ((size_t) aux) % 0x10;
        last_symbol < 10 ? 
            (str[x] = ('0' + last_symbol)) : (str[x] = ('a' + (last_symbol - 10))); 
    }
    return str;
}

char * s21_ntoa(char * str, double number, int format) {
    int e = 0;
    // TODO:    1. Здесь необходимо выделять память динамически.
    //          2. Необходимо как-то обновить здесь структуру.
    char storage[100] = "Hello, world!";
    for (; pow(10, e) < fabs(number); e += 1);
    strcat(str, s21_ftoa(storage, number * pow(10, -(e - 1)), 6));
    format == 'e' ? strcat(str, "e+0") : strcat(str, "E+0");
    str[strlen(str) + (e > 10 ? (-1) : 0)] = '\0';
    strcat(str, s21_itoa(storage, e - 1, 1));
    return str;
}

//      ДАНЯ! Необязательно создавать доп.переменную. Можно отправлять ту же STR, но с плюсом (str + x)!!!

char * s21_ftoa(char * str, double number, int afterpoint) {
    strcat(s21_itoa(str, number, 1), ".");
    for (number -= (int) number; number < 0; number *= (-1));
    for (int lenStr = strlen(str), x = 1; x < afterpoint; x += 1, lenStr += 1)
        s21_itoa(str + lenStr, ((round(number * pow(10, x + 1))) - (floor(number * pow(10, x)) * 10)), 1);
    return str;
}

//  s21_utoa(str, (number < 0 ? INT_MAX + number + 1 : number), format);

char * s21_utoa(char * str, unsigned int number, int format) {
    int lenStr = 0, type = 97;
    format == 32 ? format /= 2 : (type = 65);
    for (; (number / format) != 0; number /= format, lenStr += 1)
        str[lenStr] = (number % format) < 10 ? (number % format) + 48 : ((number % format) - 10) + type;
    str[lenStr] = number < 10 ? number + 48 : (number - 10) + type;
    str[lenStr + 1] = '\0';
    s21_reverse(str);
    return str;
}

char * s21_itoa(char * str, int number, int accuracy) {
    int lenStr = 0, minus = number < 0 ? (number *= (-1)) : 0;
    for (; ((lenStr < accuracy) || ((number / 10) != 0) || ((number % 10) != 0)); number /= 10)
        str[lenStr++] = (number % 10) + 48;
    minus != 0 ? str[lenStr++] = '-' : 0;
    str[lenStr] = '\0';
    s21_reverse(str);
    return str;
}

int main() {
    
    char TEST_MESSAGE[500] = "Hello, World!!";

    char TEST_c = '5';
    unsigned int TEST_d = 214748;
    unsigned int TEST_i = -214749;
    double TEST_e = 32354324324324.7536875368;
    double TEST_E = -32354324324324.7536875368;
    double TEST_f = 5.323543000024324;
    double TEST_g = 5.32354324324324;
    double TEST_G = -5.753;
    int TEST_o = 775;
    char TEST_s[100] = "CHAMOMIL";
    int TEST_u = -7473857;
    int TEST_x = 999;
    int TEST_X = 998;
    int TEST_p = 999;
    int TEST_n = 999;

    // int width = 5;

    //          |%c|%d|%i|%e|%E|%f|%g|%G|%o|%s|%u|%x|%X|%p|%n|%%|
    //          |%-15c|%-15d|%-15i|%-15e|%-15E|%-15f|%-15g|%-15G|%-15o|%-15s|%-15u|%-15x|%-15X|%-30p|%-15n|%-15%|
    //          |%15c|%15d|%15i|%15e|%15E|%15f|%15g|%15G|%15o|%15s|%15u|%15x|%15X|%30p|%15n|%15%|
    //          |%.2c|%.2d|%.2i|%.2e|%.2E|%.2f|%.2g|%.2G|%.2o|%.2s|%.2u|%.2x|%.2X|%.2p|%.2n|%.2%|
    //          |%+c|%+d|%+i|%+e|%+E|%+f|%+g|%+G|%+o|%+s|%+u|%+x|%+X|%+p|%+n|%+%|   -   dieEfgG
    //          |% c|% d|% i|% e|% E|% f|% g|% G|% o|% s|% u|% x|% X|% p|% n|% %|   -   dieEfgGu
    //          |%#c|%#d|%#i|%#e|%#E|%#f|%#g|%#G|%#o|%#s|%#u|%#x|%#X|%#p|%#n|%#%|
    //          |%015c|%015d|%015i|%015e|%015E|%015f|%015g|%015G|%015o|%015s|%015u|%015x|%015X|%015p|%015n|%015%|   -   dieEfgGuxXp
    //          |%.15c|%.15d|%.15i|%.15e|%.15E|%.15f|%.15g|%.15G|%.15o|%.15s|%.15u|%.15x|%.15X|%.15p|%.15n|%.15%|

    //          1. Проверяем знаки и доп.символы.
    //          2. Проверяем точность числа.
    //          3. Настраиваем ширину.

    int one = sprintf(TEST_MESSAGE, "|%5.15c|%.15d|%.15i|%.15e|%.15E|%.15f|%.15g|%.15G|%.15o|%.15s|%.15u|%.15x|%.15X|%.15p|%.15n|%.15%|", 
        TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G, TEST_o, 
        TEST_s, TEST_u, TEST_x, TEST_X, &TEST_p, &TEST_n);
    printf("\nORIGINAL - %s - %d - |%d|\n", TEST_MESSAGE, TEST_n, one);

    int two = s21_sprintf(TEST_MESSAGE, "|%5.15c|%.15d|%.15i|%.15e|%.15E|%.15f|%.15g|%.15G|%.15o|%.15s|%.15u|%.15x|%.15X|%.15p|%.15n|%.15%|", 
        TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G, TEST_o, 
        TEST_s, TEST_u, TEST_x, TEST_X, &TEST_p, &TEST_n);
    printf("\n__FAKE__ - %s - %d - |%d|\n\n", TEST_MESSAGE, TEST_n, two);

    return 0;
}
