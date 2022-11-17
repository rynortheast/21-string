#include "s21_string.h"

char *s21_strcat(char *str_main, const char *str_aux) {
  int str_aux_len = s21_strlen(str_aux);
  int str_main_len = s21_strlen(str_main);
  for (int counter = 0; counter <= str_aux_len; counter++)
    str_main[str_main_len + counter] = str_aux[counter];
  return str_main;
}
