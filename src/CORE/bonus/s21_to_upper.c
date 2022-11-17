#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *newstr = calloc(s21_strlen(str) + 1, 1);
  for (unsigned long long i = 0; i < s21_strlen(str); i++) {
    if (str[i] < 'a' || str[i] > 'z') {
      newstr[i] = str[i];
    } else {
      newstr[i] = str[i] - 32;
    }
  }
  return newstr;
}
