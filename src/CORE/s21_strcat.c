#include "../s21_string.h"

char *s21_strcat(char *destptr, const char *srcptr) {
  int destptrLength = s21_strlen(destptr);
  int srcptrLength = s21_strlen(srcptr);

  for (int x = 0; x <= srcptrLength; x += 1)
    destptr[destptrLength + x] = srcptr[x];

  return destptr;
}
