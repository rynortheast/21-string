#include "s21_string.h"

char *s21_strcpy(char *str_main, const char *str_aux) {
  int str_aux_len = s21_strlen(str_aux);
  for (int x = 0; x <= str_aux_len; x++) {
    str_main[x] = str_aux[x];
  }
  return str_main;
}
