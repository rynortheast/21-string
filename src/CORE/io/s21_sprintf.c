#include "../../s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  str[0] = '\0';
  va_list params;
  va_start(params, format);
  int counter = 0;
  for (int x = 0; format[x] != '\0'; x += 1) {
    if (format[x] == '%') {
      spec config = {"xxxxx", INT_MIN, INT_MIN, 'x'};
      x = searchModifiersForString(x, format, &config, &params);
      if (format[x] == 'n') {
        *(va_arg(params, int *)) = counter;
      } else {
        counter +=
            insertStringBySpecifier(str + counter, format[x], config, &params);
      }
    } else {
      str[counter] = format[x];
      str[counter += 1] = '\0';
    }
  }
  va_end(params);
  return counter;
}

int searchModifiersForString(int x, const char *format, spec *config,
                             va_list *params) {
  for (x += 1; s21_strchr("-+ #0", format[x]); x += 1)
    (config->flag)[5 - s21_strlen(s21_strchr("-+ #0", format[x]))] = 'o';
  for (; s21_strchr("0123456789", format[x]); x += 1)
    config->width = (config->width * 10) + (format[x] - 48);
  for (; format[x] == '*'; x += 1) config->width = va_arg(*params, int);
  if (format[x] == '.') {
    for (x += 1; format[x] == '-'; x += 1) continue;
    for (; s21_strchr("0123456789", format[x]); x += 1)
      config->accuracy = (config->accuracy * 10) + (format[x] - 48);
    for (; format[x] == '*'; x += 1) config->accuracy = va_arg(*params, int);
    config->accuracy < 0 ? config->accuracy = 0 : 0;
  }
  for (; s21_strchr("hlL", format[x]); x += 1) config->type = format[x];
  return x;
}

int setBaseAccuracyValue(int accuracy, int symbol) {
  if (accuracy < 0) {
    s21_strchr("diouxX", symbol) ? accuracy = 1 : 0;
    s21_strchr("eEfgG", symbol) ? accuracy = 6 : 0;
    s21_strchr("p", symbol) ? accuracy = 16 : 0;
  }
  return accuracy;
}

int insertStringBySpecifier(char *str, char symbol, spec config,
                            va_list *params) {
  char *flag = config.flag;
  int indent = 0, accuracy = setBaseAccuracyValue(config.accuracy, symbol);
  if (symbol == '%') {
    s21_strcat(str, "%");
  } else if (symbol == 'c') {
    return s21_ctos(str + indent, params, flag, config.width, config.type);
  } else if (s21_strchr("di", symbol)) {
    if (config.type == 'h')
      s21_itoa_short(str + indent, va_arg(*params, int), accuracy, flag);
    else if (config.type == 'l')
      s21_itoa_long(str + indent, va_arg(*params, long int), accuracy, flag);
    else
      s21_itoa(str + indent, va_arg(*params, int), accuracy, flag);
  } else if (symbol == 'p') {
    s21_ptoa(str + indent, va_arg(*params, void *));
  } else if (symbol == 's') {
    s21_stos(str + indent, params, accuracy, config.type);
  } else if (symbol == 'f') {
    if (config.type == 'L')
      s21_ftoa_long(str + indent, va_arg(*params, long double), accuracy, flag,
                    0);
    else
      s21_ftoa(str + indent, va_arg(*params, double), accuracy, flag, 0);
  } else if (s21_strchr("gG", symbol)) {
    if (config.type == 'L')
      s21_gtoa_long(str + indent, va_arg(*params, long double), accuracy, flag,
                    symbol);
    else
      s21_gtoa(str + indent, va_arg(*params, double), accuracy, flag, symbol);
  } else if (s21_strchr("eE", symbol)) {
    if (config.type == 'L')
      s21_ntoa_long(str + indent, va_arg(*params, long double), accuracy, flag,
                    symbol, 0);
    else
      s21_ntoa(str + indent, va_arg(*params, double), accuracy, flag, symbol,
               0);
  } else if (s21_strchr("xX", symbol)) {
    if (config.type == 'h')
      s21_utoa_short(str + indent, va_arg(*params, int),
                     symbol == 'x' ? 32 : 16, accuracy, flag);
    else if (config.type == 'l')
      s21_utoa_long(str + indent, va_arg(*params, long int),
                    symbol == 'x' ? 32 : 16, accuracy, flag);
    else
      s21_utoa(str + indent, va_arg(*params, int), symbol == 'x' ? 32 : 16,
               accuracy, flag);
  } else if (symbol == 'o') {
    if (config.type == 'h')
      s21_utoa_short(str + indent, va_arg(*params, unsigned int), 8, accuracy,
                     flag);
    else if (config.type == 'l')
      s21_utoa_long(str + indent, va_arg(*params, long unsigned int), 8,
                    accuracy, flag);
    else
      s21_utoa(str + indent, va_arg(*params, unsigned int), 8, accuracy, flag);
  } else if (symbol == 'u') {
    if (config.type == 'h')
      s21_utoa_short(str + indent, va_arg(*params, unsigned int), 10, accuracy,
                     flag);
    else if (config.type == 'l')
      s21_utoa_long(str + indent, va_arg(*params, long unsigned int), 10,
                    accuracy, flag);
    else
      s21_utoa(str + indent, va_arg(*params, unsigned int), 10, accuracy, flag);
  }
  s21_strchr("n%c", symbol) ? 0 : s21_conf(str + indent, config, symbol);
  return s21_strlen(str);
}

char *s21_conf(char *str, spec config, char symbol) {
  if (s21_strcmp(config.flag, "xxxxx") || config.width >= 0 ||
      config.type != 'x') {
    if (s21_strchr("gG", symbol) && config.flag[3] != 'o') {
      if (!(s21_strlen(str) == 1 && str[0] == '0')) {
        for (int x = (s21_strlen(str) - 1); str[x] == '0';
             str[x] = '\0', x -= 1)
          continue;
      }
    }
  }
  char *aux = str;
  char filler = ' ';
  int countFill = config.width > 0 ? config.width - s21_strlen(str) : 0;
  if (config.flag[4] == 'o') {
    aux[0] == '-' ? aux += 1 : 0;
    s21_strchr("cs", symbol) ? 0 : (filler = '0');
  } else if (config.flag[0] == 'o') {
    aux += s21_strlen(aux);
  }
  if (countFill > 0) {
    for (s21_memmove(aux + countFill, aux, s21_strlen(aux) + 1);
         countFill != 0;) {
      aux[countFill - 1] = filler;
      countFill -= 1;
    }
  }
  return str;
}

int s21_ctos(char *str, va_list *params, char *flag, int accuracy, char type) {
  int counter = 0;
  accuracy = accuracy < 1 ? 1 : accuracy;
  if (type == 'l') {
    wchar_t w_c = va_arg(*params, wchar_t);
    counter = wcstombs(str + counter, &w_c, 512);
  } else {
    str[counter++] = va_arg(*params, int);
    str[counter] = '\0';
  }
  if (flag[0] != 'o' && accuracy - counter > 0) {
    s21_memmove(str + (accuracy - counter), str, counter + 1);
    for (int x = 0; x < accuracy - counter; x += 1) str[x] = ' ';
    counter = accuracy;
  }
  for (int x = counter; flag[0] == 'o' && x < (accuracy); x += 1)
    str[counter++] = ' ';
  return counter;
}

char *s21_stos(char *str, va_list *params, int accuracy, char type) {
  if (type == 'l') {
    wcstombs(str, va_arg(*params, wchar_t *), 512);
  } else {
    s21_strcat(str, va_arg(*params, char *));
  }
  accuracy < 0 ? accuracy = s21_strlen(str) : 0;
  str[accuracy] = '\0';
  return str;
}

char *s21_ptoa(char *str, int *variable) {
  int *aux = variable;
  if (aux == NULL) {
    // OSS == 1 ? s21_strcat(str, "(nil)") : s21_strcat(str, "0x0");
    s21_strcat(str, "0x0");
  } else {
    for (int x = s21_strlen(str); aux != 0;
         aux = ((void *)(((size_t)aux) >> 4)), x += 1) {
      unsigned int last_symbol = ((size_t)aux) % 0x10;
      last_symbol < 10 ? (str[x] = ('0' + last_symbol))
                       : (str[x] = ('a' + (last_symbol - 10)));
      str[x + 1] = '\0';
    }
    s21_strcat(str, "x0");
    s21_reverse(str);
  }
  return str;
}

char *s21_utoa(char *str, unsigned int number, int format, int accuracy,
               char *flag) {
  int lenStr = 0, type = 97, numb = number;
  format == 32 ? format /= 2 : (type = 65);
  for (; (lenStr < accuracy - 1) || (number / format) != 0;
       number /= format, lenStr += 1)
    str[lenStr] = (number % format) < 10 ? (number % format) + 48
                                         : ((number % format) - 10) + type;
  str[lenStr++] = number < 10 ? number + 48 : (number - 10) + type;
  (flag[3] == 'o' && format == 8 && number != 0) ? str[lenStr++] = '0' : 0;
  str[lenStr] = '\0';
  (flag[3] == 'o' && format == 16 && type == 65 && numb != 0)
      ? s21_strcat(str, "X0")
      : 0;
  (flag[3] == 'o' && format == 16 && type == 97 && numb != 0)
      ? s21_strcat(str, "x0")
      : 0;
  s21_reverse(str);
  return str;
}

char *s21_ntoa_long(char *str, long double number, int accuracy, char *flag,
                    int symbol, int kostyl_2) {
  int lenStr = 0, lenNum = 0, result = 0, kostyl = accuracy;
  char flagX[10] = "xxxxx";
  char flag1[10] = "xoxxx";
  if (number != 0) {
    for (int aux = lenNum = fabsl(number) < 1    ? 1
                            : fabsl(number) < 10 ? 0
                                                 : (-1);
         aux != 0; lenNum += aux)
      aux = ((fabsl(number) * powl(10, lenNum)) < 1 ||
             10 < fabsl(number) * powl(10, lenNum))
                ? aux
                : 0;
  }
  s21_itoa(str,
           (kostyl == 0 ? (roundl(number * powl(10, lenNum)))
                        : (number * powl(10, lenNum))),
           1, flag);
  (kostyl != 0 || flag[3] == 'o')
      ? s21_strcat(str, (localeconv()->decimal_point))
      : 0;
  for (lenStr = s21_strlen(str); number < 0; number *= (-1)) continue;
  for (result = lenNum; (accuracy != 0 && (lenNum + 1) <= 0); accuracy -= 1) {
    if (accuracy == 1)
      s21_itoa(str + (lenStr++),
               roundl(fmodl((roundl(number) * powl(10, lenNum += 1)), 10)), 1,
               flagX);
    else
      s21_itoa(str + (lenStr++), fmodl((number * powl(10, lenNum += 1)), 10), 1,
               flagX);
  }
  for (int aux = lenNum + 1; accuracy != 0; accuracy -= 1) {
    if (accuracy == 1)
      s21_itoa(str + (lenStr++),
               roundl(fmodl((number * powl(10, (aux++))), 10)), 1, flagX);
    else
      s21_itoa(str + (lenStr++), fmodl((number * powl(10, (aux++))), 10), 1,
               flagX);
  }
  if (kostyl_2 == 1 && flag[3] != 'o') {
    for (int x = s21_strlen(str) - 1; s21_strchr("0.", str[x]); str[x--] = '\0')
      continue;
    for (int x = s21_strlen(str) - 1;
         s21_strchr((localeconv()->decimal_point), str[x]);)
      str[x--] = '\0';
  }
  lenStr = s21_strlen(str);
  str[lenStr++] = symbol;
  str[lenStr] = '\0';
  s21_itoa(str + (lenStr), -result, 2, flag1);
  return str;
}

char *s21_ftoa_long(char *str, long double number, int afterpoint, char *flag,
                    int kostyl_2) {
  char flagX[10] = "xxxxx";
  int lenStr = 0, minus = 0, kostyl = afterpoint, k3 = 0;
  for (; number < 0; number *= (-1), minus = 1) continue;
  long double aux =
      ceill((number - truncl(number)) * powl(10, afterpoint) - 0.5);
  for (; ((afterpoint != 0) || ((aux / 10) > 1) || (fmodl(aux, 10) > 1));
       afterpoint -= 1, aux /= 10) {
    str[lenStr++] = ((int)fmodl(aux, 10)) + 48;
    str[lenStr] = '\0';
  }
  aux == 1 ? k3 = 1 : 0;
  (kostyl != 0 || flag[3] == 'o')
      ? str[lenStr++] = (localeconv()->decimal_point)[0]
      : 0;
  kostyl == 0 ? number = roundl(number) : 0;
  for (aux = k3 == 1 ? round(number) : number; ((aux / 10) >= 1);
       aux /= 10, str[lenStr] = '\0')
    str[lenStr++] = ((int)fmodl(aux, 10)) + 48;
  s21_itoa(str + lenStr, fmodl(aux, 10), 1, flagX);
  minus == 1 ? s21_strcat(str, "-") : 0;
  lenStr = s21_strlen(str);
  if (str[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o')) {
    str[lenStr++] = flag[1] == 'o' ? '+' : ' ';
    str[lenStr] = '\0';
  }
  s21_reverse(str);
  if (kostyl_2 == 1 && flag[3] != 'o') {
    int x = s21_strlen(str) - 1;
    for (; s21_strchr("0", str[x]); str[x--] = '\0') continue;
    str[x] == (localeconv()->decimal_point)[0] ? str[x] = '\0' : 0;
  }
  return str;
}

char *s21_gtoa_long(char *str, long double number, int accuracy, char *flag,
                    int symbol) {
  int lenNum = 0;
  accuracy == 0 ? accuracy = 1 : 0;
  if (number == 0) {
    s21_ftoa_long(str, number, accuracy - 1, flag, 1);
  } else {
    for (int aux = lenNum = fabsl(number) < 1    ? 1
                            : fabsl(number) < 10 ? 0
                                                 : (-1);
         aux != 0; lenNum += aux)
      aux = ((fabsl(number) * powl(10, lenNum)) < 1 ||
             10 < fabsl(number) * powl(10, lenNum))
                ? aux
                : 0;
    if (lenNum <= 0)
      (accuracy + lenNum <= 0)
          ? s21_ntoa_long(str, number, accuracy - 1, flag, symbol - 2, 1)
          : s21_ftoa_long(str, number, (accuracy - 1) + lenNum, flag, 1);
    else
      (accuracy - 1) <= lenNum
          ? s21_ntoa_long(str, number, accuracy - 1, flag, symbol - 2, 1)
          : s21_ftoa_long(str, number, lenNum + (accuracy - 1), flag, 1);
  }
  return str;
}

char *s21_itoa(char *str, int number, int accuracy, char *flag) {
  int lenStr = 0, minus = number < 0 ? (number *= (-1)) : 0;
  if (number < 0) {
    for (; ((lenStr < accuracy) || (-(number / 10) != 0) ||
            (-(number % 10) != 0));
         number /= 10)
      str[lenStr++] = (-(number % 10)) + 48;
  } else {
    for (;
         ((lenStr < accuracy) || ((number / 10) != 0) || ((number % 10) != 0));
         number /= 10)
      str[lenStr++] = (number % 10) + 48;
  }
  minus != 0 ? str[lenStr++] = '-' : 0;
  if (str[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o'))
    str[lenStr++] = flag[1] == 'o' ? '+' : ' ';
  str[lenStr] = '\0';
  s21_reverse(str);
  return str;
}

char *s21_utoa_long(char *str, long unsigned int number, int format,
                    int accuracy, char *flag) {
  int lenStr = 0, type = 97, numb = number;
  format == 32 ? format /= 2 : (type = 65);
  for (; (lenStr < accuracy - 1) || (number / format) != 0;
       number /= format, lenStr += 1)
    str[lenStr] = (number % format) < 10 ? (number % format) + 48
                                         : ((number % format) - 10) + type;
  str[lenStr++] = number < 10 ? number + 48 : (number - 10) + type;
  (flag[3] == 'o' && format == 8 && number != 0) ? str[lenStr++] = '0' : 0;
  str[lenStr] = '\0';
  (flag[3] == 'o' && format == 16 && type == 65 && numb != 0)
      ? s21_strcat(str, "X0")
      : 0;
  (flag[3] == 'o' && format == 16 && type == 97 && numb != 0)
      ? s21_strcat(str, "x0")
      : 0;
  s21_reverse(str);
  return str;
}

char *s21_itoa_long(char *str, long int number, int accuracy, char *flag) {
  int lenStr = 0;
  long int minus = number < 0 ? (number *= (-1)) : 0;
  if (number < 0) {
    for (; ((lenStr < accuracy) || (-(number / 10) != 0) ||
            (-(number % 10) != 0));
         number /= 10)
      str[lenStr++] = (-(number % 10)) + 48;
  } else {
    for (;
         ((lenStr < accuracy) || ((number / 10) != 0) || ((number % 10) != 0));
         number /= 10)
      str[lenStr++] = (number % 10) + 48;
  }
  minus != 0 ? str[lenStr++] = '-' : 0;
  if (str[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o'))
    str[lenStr++] = flag[1] == 'o' ? '+' : ' ';
  str[lenStr] = '\0';
  s21_reverse(str);
  return str;
}

char *s21_utoa_short(char *str, short unsigned int number, int format,
                     int accuracy, char *flag) {
  int lenStr = 0, type = 97, numb = number;
  format == 32 ? format /= 2 : (type = 65);
  for (; (lenStr < accuracy - 1) || (number / format) != 0;
       number /= format, lenStr += 1)
    str[lenStr] = (number % format) < 10 ? (number % format) + 48
                                         : ((number % format) - 10) + type;
  str[lenStr++] = number < 10 ? number + 48 : (number - 10) + type;
  (flag[3] == 'o' && format == 8 && number != 0) ? str[lenStr++] = '0' : 0;
  str[lenStr] = '\0';
  (flag[3] == 'o' && format == 16 && type == 65 && numb != 0)
      ? s21_strcat(str, "X0")
      : 0;
  (flag[3] == 'o' && format == 16 && type == 97 && numb != 0)
      ? s21_strcat(str, "x0")
      : 0;
  s21_reverse(str);
  return str;
}

char *s21_itoa_short(char *str, short int number, int accuracy, char *flag) {
  int lenStr = 0, minus = number < 0 ? (number *= (-1)) : 0;
  if (number < 0) {
    for (; ((lenStr < accuracy) || (-(number / 10) != 0) ||
            (-(number % 10) != 0));
         number /= 10)
      str[lenStr++] = (-(number % 10)) + 48;
  } else {
    for (;
         ((lenStr < accuracy) || ((number / 10) != 0) || ((number % 10) != 0));
         number /= 10)
      str[lenStr++] = (number % 10) + 48;
  }
  minus != 0 ? str[lenStr++] = '-' : 0;
  if (str[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o'))
    str[lenStr++] = flag[1] == 'o' ? '+' : ' ';
  str[lenStr] = '\0';
  s21_reverse(str);
  return str;
}

char *s21_ntoa(char *str, double number, int accuracy, char *flag, int symbol,
               int kostyl_2) {
  char flagX[10] = "xxxxx";
  char flag1[10] = "xoxxx";
  int lenStr = 0, lenNum = 0, result = 0, kostyl = accuracy;
  if (number != 0) {
    for (int aux = lenNum = fabs(number) < 1    ? 1
                            : fabs(number) < 10 ? 0
                                                : (-1);
         aux != 0; lenNum += aux)
      aux = ((fabs(number) * pow(10, lenNum)) < 1 ||
             10 < fabs(number) * pow(10, lenNum))
                ? aux
                : 0;
  }
  s21_itoa(str,
           (kostyl == 0 ? (round(number * pow(10, lenNum)))
                        : (number * pow(10, lenNum))),
           1, flag);
  (kostyl != 0 || flag[3] == 'o')
      ? s21_strcat(str, (localeconv()->decimal_point))
      : 0;
  for (lenStr = s21_strlen(str); number < 0; number *= (-1)) continue;
  for (result = lenNum; (accuracy != 0 && (lenNum + 1) <= 0); accuracy -= 1) {
    if (accuracy == 1)
      s21_itoa(str + (lenStr++),
               fmod((round(number) * pow(10, lenNum += 1)), 10), 1, flagX);
    else
      s21_itoa(str + (lenStr++), fmod((number * pow(10, lenNum += 1)), 10), 1,
               flagX);
  }
  for (int aux = lenNum + 1; accuracy != 0; accuracy -= 1)
    accuracy == 1
        ? s21_itoa(str + (lenStr++),
                   round(fmod((number * pow(10, (aux++))), 10)), 1, flagX)
        : s21_itoa(str + (lenStr++), fmod((number * pow(10, (aux++))), 10), 1,
                   flagX);
  if (kostyl_2 == 1 && flag[3] != 'o') {
    for (int x = s21_strlen(str) - 1; s21_strchr("0", str[x]); str[x--] = '\0')
      continue;
    for (int x = s21_strlen(str) - 1;
         s21_strchr((localeconv()->decimal_point), str[x]);)
      str[x--] = '\0';
  }
  lenStr = s21_strlen(str);
  str[lenStr++] = symbol;
  str[lenStr] = '\0';
  s21_itoa(str + (lenStr), -result, 2, flag1);
  return str;
}

char *s21_ftoa(char *str, double number, int afterpoint, char *flag,
               int kostyl_2) {
  char flagX[10] = "xxxxx";
  int lenStr = 0, minus = 0, kostyl = afterpoint, k3 = 0;
  for (; number < 0; number *= (-1), minus = 1) continue;
  double aux = ceil((number - trunc(number)) * pow(10, afterpoint) - 0.5);
  for (; ((afterpoint != 0) || ((aux / 10) > 1) || (fmod(aux, 10) > 1));
       afterpoint -= 1, aux /= 10) {
    str[lenStr++] = ((int)fmod(aux, 10)) + 48;
    str[lenStr] = '\0';
  }
  aux == 1 ? k3 = 1 : 0;
  (kostyl != 0 || flag[3] == 'o')
      ? str[lenStr++] = (localeconv()->decimal_point)[0]
      : 0;
  kostyl == 0 ? number = round(number) : 0;
  for (aux = k3 == 1 ? round(number) : number; (aux / 10 >= 1);
       aux /= 10, str[lenStr] = '\0')
    str[lenStr++] = ((int)fmod(aux, 10)) + 48;
  s21_itoa(str + lenStr, fmod(aux, 10), 1, flagX);
  minus == 1 ? s21_strcat(str, "-") : 0;
  lenStr = s21_strlen(str);
  if (str[lenStr - 1] != '-' && (flag[1] == 'o' || flag[2] == 'o')) {
    str[lenStr++] = flag[1] == 'o' ? '+' : ' ';
    str[lenStr] = '\0';
  }
  s21_reverse(str);
  if (kostyl_2 == 1 && flag[3] != 'o') {
    int x = s21_strlen(str) - 1;
    for (; s21_strchr("0", str[x]); str[x--] = '\0') continue;
    str[x] == (localeconv()->decimal_point)[0] ? str[x] = '\0' : 0;
  }
  return str;
}

char *s21_gtoa(char *str, double number, int accuracy, char *flag, int symbol) {
  int lenNum = 0;
  accuracy == 0 ? accuracy = 1 : 0;
  if (number == 0) {
    s21_ftoa(str, number, accuracy - 1, flag, 1);
  } else {
    for (int aux = lenNum = fabs(number) < 1    ? 1
                            : fabs(number) < 10 ? 0
                                                : (-1);
         aux != 0; lenNum += aux)
      aux = ((fabs(number) * pow(10, lenNum)) < 1 ||
             10 < fabs(number) * pow(10, lenNum))
                ? aux
                : 0;
    // printf("TEST - %d - %d\n", accuracy, lenNum);
    if (lenNum <= 0)
      (accuracy + lenNum <= 0)
          ? s21_ntoa(str, number, accuracy - 1, flag, symbol - 2, 1)
          : s21_ftoa(str, number, (accuracy - 1) + lenNum, flag, 1);
    else
      lenNum > 4 ? s21_ntoa(str, number, accuracy - 1, flag, symbol - 2, 1)
                 : s21_ftoa(str, number, lenNum + (accuracy - 1), flag, 1);
  }
  return str;
}
