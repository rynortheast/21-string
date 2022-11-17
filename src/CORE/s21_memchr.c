#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  int check = 0;
  const char *newArr = str;
  for (s21_size_t i = 0; newArr && i < n; i++) {
    if (check == 0 && newArr[i] == c) {
      check = 1;
      if (c == '\0') break;
      newArr += i;
    }
  }
  if (check == 0)
    return s21_NULL;
  else
    return (void *)newArr;
}
