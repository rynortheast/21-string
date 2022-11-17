#include "s21_string.h"

char *s21_strncat(char *str_main, const char *str_aux, s21_size_t accuracy) {
  int len = s21_strlen(str_main);
  for (s21_size_t counter = 0; counter < accuracy && str_aux[counter] != '\0';
       counter += 1) {
    str_main[len + counter] = str_aux[counter];
    str_main[len + counter + 1] = '\0';
  }
  return str_main;
}
