#include "s21_string.h"

char *s21_strstr(const char *str_main, const char *str_aux) {
  char *result = s21_NULL;
  size_t strAuxLen = s21_strlen(str_aux);
  if (strAuxLen != 0) {
    for (int x = 0; str_main[x] != '\0'; x += 1) {
      if (str_main[x] != str_aux[0]) {
        continue;
      }
      if (strncmp(str_main + x, str_aux, strAuxLen) == 0) {
        result = ((char *)str_main + x);
        break;
      }
    }
  } else {
    result = (char *)str_main;
  }
  return result;
}
