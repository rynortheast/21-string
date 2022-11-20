#include "../s21_string.h"

int s21_memcmp(const void *mem_1, const void *mem_2, s21_size_t size) {
  unsigned char *str_1 = (unsigned char *)mem_1;
  unsigned char *str_2 = (unsigned char *)mem_2;
  int result = 0;

  for (int x = 0; result == 0 && str_1[x] != '\0' && x < size; x += 1)
    result = str_1[x] - str_2[x];

  return result;
}
