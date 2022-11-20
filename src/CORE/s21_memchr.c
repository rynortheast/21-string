#include "../s21_string.h"

void *s21_memchr(const void *str, int symbol, s21_size_t size) {
  const char *result = str;
  int status = 0;

  for (int x = 0; status == 0 && result && x < size; x += 1) {
    if (result[x] == symbol) {
      if (symbol != '\0') result += x;
      status = 1;
    }
  }

  return status ? ((void *)result) : s21_NULL;
}
