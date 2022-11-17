#include "s21_string.h"

int s21_strncmp(const char *str_1, const char *str_2, s21_size_t n) {
  int result = 0;
  for (s21_size_t counter = 0; counter < n; counter += 1) {
    if (str_1[counter] == str_2[counter]) {
      if (str_1[counter] != '\0') continue;
      break;
    } else {
      result = str_1[counter] - str_2[counter];
    }
    break;
  }
  return result;
}
