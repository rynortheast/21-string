#include "s21_string.h"

char *s21_strpbrk(const char *str, const char *keys) {
  s21_size_t strLength = s21_strlen(str);
  s21_size_t shift = 0;
  int status = 0;

  for (shift = 0; status == 0 && shift < strLength; shift += 1) {
    if (s21_strchr(keys, str[shift])) status = 1;
  }

  return (char *)(status ? (str + shift) : s21_NULL);
}
