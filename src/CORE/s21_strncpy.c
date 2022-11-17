#include "s21_string.h"

char *s21_strncpy(char *str_main, const char *str_aux, s21_size_t n) {
  for (s21_size_t x = 0; x < n; x += 1) {
    str_main[x] = str_aux[x];
    if (str_aux[x] == '\0') break;
  }
  return str_main;
}
