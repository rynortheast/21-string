#include "s21_string.h"

int s21_strcmp(const char *str_1, const char *str_2) {
  int counter = 0;
  while (str_1[counter] && str_2[counter] && (str_1[counter] == str_2[counter]))
    counter += 1;
  return str_1[counter] > str_2[counter]   ? 1
         : str_1[counter] < str_2[counter] ? (-1)
                                           : 0;
}
