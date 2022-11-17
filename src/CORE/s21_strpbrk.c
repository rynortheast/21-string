#include "s21_string.h"

char *s21_strpbrk(const char *str, const char *key) {
  s21_size_t result = 0;
  int check = 0;
  for (result = 0; result < (s21_strlen(str)); result++) {
    if (s21_strchr(key, str[result])) {
      check = 1;
      break;
    }
  }
  return (char *)((check == 1) ? str + result : s21_NULL);
}
