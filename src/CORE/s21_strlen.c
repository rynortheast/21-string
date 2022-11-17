#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t lenStr = 0;
  for (; str[lenStr];) {
    lenStr += 1;
  }
  return lenStr;
}
