#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *tocpy = (char *)dest;
  char *fromcpy = (char *)src;
  char *tmp = (char *)malloc(sizeof(char) * n);
  if (tmp) {
    s21_memcpy(tmp, fromcpy, n);
    s21_memcpy(tocpy, tmp, n);
    free(tmp);
  }
  return dest;
}
