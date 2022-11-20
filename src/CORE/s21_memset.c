#include "../s21_string.h"

void *s21_memset(void *str, int symbol, s21_size_t size) {
  for (int x = 0; x < size; x += 1) {
    ((char *)str)[x] = symbol;
  }
  return str;
}
