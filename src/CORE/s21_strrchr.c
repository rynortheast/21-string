#include "s21_string.h"

char *s21_strrchr(const char *str, int symbol) {
  const char *result = s21_NULL;
  int str_len = s21_strlen(str);
  for (int counter = str_len; counter >= 0; counter--) {
    if (str[counter] == symbol) {
      result = (str + counter);
      break;
    }
  }
  return (char *)result;
}
