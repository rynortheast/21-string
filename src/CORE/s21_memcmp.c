#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *tmp1 = (unsigned char *)str1;
  unsigned char *tmp2 = (unsigned char *)str2;
  int res = 0;
  for (s21_size_t i = 0; i < n; i++) {
    res = tmp1[i] - tmp2[i];
    if (tmp1[i] != tmp2[i]) break;
  }
  return res;
}
