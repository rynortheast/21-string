#include "s21_string.h"

int s21_strncmp(const char *str_1, const char *str_2, s21_size_t size) {
  int result = 0;

  //  TODO [s21_strncmp] Необходим рефакторинг кода :|
  for (s21_size_t x = 0; x < size; x += 1) {
    if (str_1[x] == str_2[x]) {
      if (str_1[x] != '\0') continue;
      break;
    } else {
      result = str_1[x] - str_2[x];
    }
    break;
  }

  return result;
}
