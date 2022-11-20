#include "s21_string.h"

s21_size_t s21_strspn(const char *str, const char *keys) {
  s21_size_t strLength = s21_strlen(str);
  s21_size_t result = 0;

  for (s21_size_t x = 0; result == 0 && x < strLength; x += 1) {
    if (s21_strchr(keys, str[x]) != s21_NULL) result = x + 1;
  }

  return result;
}
