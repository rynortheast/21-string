#include "../s21_string.h"

int s21_strcmp(const char *str_1, const char *str_2) {
  int result = 0;

  for (int x = 0; result == 0 && str_1[x] != '\0' && str_2[x] != '\0'; x += 1)
    if (str_1[x] != str_2[x]) result = str_1[x] - str_2[x];

  return result == 0 ? 0 : (result > 0 ? 1 : (-1));
}
