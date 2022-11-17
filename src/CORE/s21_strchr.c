#include "s21_string.h"

char *s21_strchr(const char *str, int symbol) {
  const char *result = s21_NULL;
  int str_len = s21_strlen(str) + 1;
  for (int counter = 0; counter < str_len; counter++) {
    if (str[counter] == symbol) {
      result = (str + counter);
      break;
    }
  }
  return (char *)result;
}
