#include "../s21_string.h"

char *s21_strchr(const char *str, int symbol) {
  int strLength = s21_strlen(str) + 1;
  const char *result = s21_NULL;

  for (int x = 0; x < strLength && result == s21_NULL; x += 1)
    if (str[x] == symbol) result = (str + x);

  return (char *)result;
}
