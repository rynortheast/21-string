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
int s21_sprintf(char * str, const char * format, ...);
char * s21_conf(char * str, spec config, char symbol);
char * s21_ptoa(char * str, int * variable, int accuracy);
char * s21_itoa(char * str, long int number, int accuracy);
char * s21_gtoa(char * str, long double number, int accuracy);
char * s21_ftoa(char * str, long double number, int afterpoint);
char * s21_ntoa(char * str, long double number, int accuracy, int symbol);
char * s21_utoa(char * str, unsigned long int number, int format, int accuracy);
char * insertStringBySpecifier(char * str, char symbol, spec config, va_list * params);
int searchModifiersForString(int x, const char * format, spec * config, va_list * params);

int s21_sprintf(char * str, const char * format, ...) {
    str[0] = '\0';
    va_list params;
    va_start(params, format);
    for (int x = 0; format[x] != '\0'; x += 1) {
        if (format[x] == '%') {
            spec config = {'x', INT_MIN, INT_MIN, 'x'};
            x = searchModifiersForString(x, format, &config, &params);
            insertStringBySpecifier(str, format[x], config, &params);
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
        for (x += 1; format[x] == '-'; x += 1);
        for (; strchr("0123456789", format[x]); x += 1)
            config -> accuracy = (config -> accuracy * 10) + (format[x] - 48);
        for (; format[x] == '*'; x += 1)
            config -> accuracy = va_arg(*params, int);
    }
    for (; strchr("hlL", format[x]); x += 1)
        config -> type = format[x];
    return x;
}

char * insertStringBySpecifier(char * str, char symbol, spec config, va_list * params) {

    str += strlen(str);

    switch (symbol) {
        case 'c':
            memmove(str + 1, str, 1);
            str[0] = va_arg(*params, int);
            s21_conf(str, config, symbol);
            break;
        case 'd':
        case 'i': 
            s21_conf(s21_itoa(str, va_arg(*params, int), config.accuracy), config, symbol);
            break;
        case 'e':
        case 'E':
            int len = config.accuracy > 0 ? config.accuracy : 6;
            s21_conf(s21_ntoa(str, va_arg(*params, double), len, symbol), config, symbol);
            break;
        case 'f':
            int lens = config.accuracy > 0 ? config.accuracy : 6;
            s21_conf(s21_ftoa(str, va_arg(*params, double), lens), config, symbol);
            break;
        case 'g':
        case 'G':
            int len_10 = config.accuracy > 0 ? config.accuracy : 6;
            s21_conf(s21_gtoa(str, va_arg(*params, double), len_10), config, symbol);
            break;
        case 's':
            int lensss = config.accuracy > 0 ? config.accuracy : strlen(str);
            s21_conf(strncat(str, va_arg(*params, char *), lensss), config, symbol);
            break;
        case 'o':
            int len_2 = config.accuracy > 0 ? config.accuracy : 1;
            s21_conf(s21_utoa(str, va_arg(*params, unsigned int), 8, len_2), config, symbol);
            break;
        case 'u':
            //  s21_utoa(str, (number < 0 ? INT_MAX + number + 1 : number), format);
            int lenssss = config.accuracy > 0 ? config.accuracy : 1;
            s21_conf(s21_utoa(str, va_arg(*params, unsigned int), 10, lenssss), config, symbol);
            break;
        case 'x':
        case 'X':
            int len_1 = config.accuracy > 0 ? config.accuracy : 1;
            s21_conf(s21_utoa(str, va_arg(*params, int), symbol == 'x' ? 32 : 16, len_1), config, symbol);
            break;
        case 'p':
            // TODO:    1. Здесь надо убрать реверс!
            int len_3 = config.accuracy > 0 ? config.accuracy : 16;
            s21_conf(s21_ptoa(str, va_arg(*params, void *), len_3), config, symbol);
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

    // printf("TEST - %s\n", str);

    // if (config.flag != 'x' || config.width < 0 || config.accuracy < 0 || config.type != 'x') {
    //     if (symbol == 'p')
    //         strcpy(str, str + strspn(str, "0"));
    //     else if (strchr("gG", symbol))
    //         for (int x = (strlen(str) - 1); str[x] == '0'; str[x] = '\0', x -= 1);
    // }

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

char * s21_ptoa(char * str, int * variable, int accuracy) {
    for (int * aux = variable, x = 0; x < accuracy; aux = ((void *) (((size_t) aux) >> 4)), x += 1) {
        unsigned int last_symbol = ((size_t) aux) % 0x10;
        last_symbol < 10 ? 
            (str[x] = ('0' + last_symbol)) : (str[x] = ('a' + (last_symbol - 10))); 
    }
    str[accuracy] = '\0';
    return s21_reverse(str);
}

char * s21_utoa(char * str, unsigned long int number, int format, int accuracy) {
    int lenStr = 0, type = 97;
    format == 32 ? format /= 2 : (type = 65);
    for (; (lenStr < accuracy - 1) || (number / format) != 0; number /= format, lenStr += 1)
        str[lenStr] = (number % format) < 10 ? (number % format) + 48 : ((number % format) - 10) + type;
    str[lenStr] = number < 10 ? number + 48 : (number - 10) + type;
    str[lenStr + 1] = '\0';
    s21_reverse(str);
    return str;
}

char * s21_ntoa(char * str, long double number, int accuracy, int symbol) {
    int lenStr = 0, lenNum = 0, result = 0;
    for (int aux = lenNum = fabsl(number) < 1 ? 1 : fabsl(number) < 10 ? 0 : (-1); aux != 0; lenNum += aux)
        aux = ((fabsl(number) * powl(10, lenNum)) < 1 || 10 < fabsl(number) * powl(10, lenNum)) ? aux : 0;
    strcat(s21_itoa(str, number * powl(10, lenNum), 1), ".");
    for (lenStr = strlen(str); number < 0; number *= (-1));
    for (result = lenNum; (accuracy != 0 && (lenNum + 1) <= 0); accuracy -= 1)
        s21_itoa(str + (lenStr++), fmodl((number * powl(10, lenNum += 1)), 10), 1);
    for (int aux = lenNum + 1; accuracy != 0; accuracy -= 1)
        s21_itoa(str + (lenStr++), fmodl((number * powl(10, (aux++))), 10), 1);
    str[lenStr++] = symbol;
    result <= 0 ? str[lenStr++] = '+' : '-';
    s21_itoa(str + (lenStr), -result, 2);
    return str;
}

char * s21_ftoa(char * str, long double number, int afterpoint) {
    int lenStr = 0, minus = 0;
    for (; number < 0; number *= (-1), minus = 1);
    double aux = ceill((number - truncl(number)) * powl(10, afterpoint) - 0.5); //  FIXME: возможно тут косяк с округлением. . .
    for (; ((afterpoint > 0) || ((aux / 10) > 1) || (fmodl(aux, 10) > 1)); afterpoint -= 1, aux /= 10, str[lenStr] = '\0')
        str[lenStr++] = ((int) fmodl(aux, 10)) + 48;
    for (str[lenStr++] = '.', aux = number; ((aux / 10) > 1); aux /= 10, str[lenStr] = '\0')
        str[lenStr++] = ((int) fmodl(aux, 10)) + 48;
    s21_itoa(str + lenStr, fmodl(aux, 10), 1);
    minus == 1 ? strcat(str, "-") : 0;
    s21_reverse(str);
    return str;
}

char * s21_gtoa(char * str, long double number, int accuracy) {
    int lenStr = 0, lenNum = 0;
    for (int aux = lenNum = fabsl(number) < 1 ? 1 : fabsl(number) < 10 ? 0 : (-1); aux != 0; lenNum += aux)
        aux = ((fabsl(number) * powl(10, lenNum)) < 1 || 10 < fabsl(number) * powl(10, lenNum)) ? aux : 0;
    lenNum = lenNum <= 0 ? -(lenNum - 1) : lenNum - 1;
    accuracy < lenNum ? s21_ntoa(str, number, accuracy - 1, 'E') : s21_ftoa(str, number, accuracy - lenNum);
    return str;
}

char * s21_itoa(char * str, long int number, int accuracy) {
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
    unsigned int TEST_d = -21475;
    unsigned int TEST_i = -214749;
    double TEST_e = -5123.75342;               //  Надо допилить с другими примерами:
    double TEST_E = -0.000032323323;      //  0.02342343243200  -  0.23543243243247536875368
    double TEST_f = -5123.75342;
    double TEST_g = 1.32323323;
    double TEST_G = -5.75342;
    int TEST_o = 775;
    char TEST_s[100] = "CHAMOMIL";
    int TEST_u = -3857;
    int TEST_x = -999000000;
    int TEST_X = -998;
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

    int one = sprintf(TEST_MESSAGE, "|%5.15c|%d|%.15i|%.3e|%.3E|%.15f|%.3g|%.3G|%.15o|%.3s|%.15u|%.15x|%.15X|%p|%.15n|%.15%|", 
        TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G, TEST_o, 
        TEST_s, TEST_u, TEST_x, TEST_X, &TEST_p, &TEST_n);
    printf("\nORIGINAL - %s - %d - |%d|\n", TEST_MESSAGE, TEST_n, one);

    int two = s21_sprintf(TEST_MESSAGE, "|%5.15c|%d|%.15i|%.3e|%.3E|%.15f|%.3g|%.3G|%.15o|%.3s|%.15u|%.15x|%.15X|%p|%.15n|%.15%|", 
        TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G, TEST_o, 
        TEST_s, TEST_u, TEST_x, TEST_X, &TEST_p, &TEST_n);
    printf("\n__FAKE__ - %s - %d - |%d|\n\n", TEST_MESSAGE, TEST_n, two);

    return 0;
}
