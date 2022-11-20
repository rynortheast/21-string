#include "../s21_string.h"

//  TODO [s21_strncat] Необходим рефакторинг кода :|
char *s21_strncat(char *result, const char *str, s21_size_t size) {
  int strLength = s21_strlen(str);

  for (s21_size_t x = 0; x < size && str[x] != '\0'; x += 1) {
    result[strLength + x] = str[x];
    result[strLength + x + 1] = '\0';
  }

  for (int x = 0, strLength = s21_strlen(str); x < size && str[x] != '\0';
       x += 1) {
    result[strLength + x] = str[x];
    result[strLength + x + 1] = '\0';
  }

  return result;
}
