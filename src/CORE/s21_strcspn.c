#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str, const char *keys) {
  s21_size_t strLength = s21_strlen(str) + 1;
  s21_size_t result = 0;

  for (result = 0; result <= strLength; result += 1)
    if (s21_strchr(keys, str[result])) break;

  return result;
}
