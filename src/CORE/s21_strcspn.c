#include "s21_string.h"

s21_size_t s21_strcspn(const char *str, const char *key) {
  s21_size_t result = 0;
  for (result = 0; result <= (s21_strlen(str) + 1); result++) {
    if (s21_strchr(key, str[result])) break;
  }
  return result;
}
