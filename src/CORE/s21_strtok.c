#include "../s21_string.h"

//  TODO [s21_strtok] Необходим рефакторинг кода :|
char *s21_strtok(char *str, const char *delim) {
  static int next, restok;
  static s21_size_t idx;
  static char *ptr;
  static char *addr;

  if (str) {
    restok = 1;
    idx = 0, next = 0;
    addr = str + s21_strspn(str, delim);
    ptr = str + s21_strlen(str);
  }
  char *res = s21_NULL;
  if (!(addr >= ptr || next)) {
    int exdelim = 1;
    for (int i = 0; addr[i]; i++) {
      s21_size_t step = s21_strspn(addr + i, delim);
      if (step != 0) {
        exdelim = 0;
        for (s21_size_t j = i; j < i + step; j++) addr[j] = '\0';

        idx = step + i;
        break;
      }
    }
    if (restok == 1 && exdelim) next = 1;
    res = addr;
    addr += idx;
  }
  restok += 1;
  return res;
}
