#include "s21_string.h"

s21_size_t s21_strspn(const char *str, const char *key) {
  s21_size_t str_len = s21_strlen(str), result = 0;
  for (s21_size_t x = 0; x < str_len; x++) {
    if (s21_strchr(key, str[x]) != s21_NULL) {
      result = x + 1;
      continue;
    }
    break;
  }
  return result;
}
