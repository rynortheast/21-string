#include "s21_string.h"

char *s21_strncpy(char *destptr, const char *srcptr, s21_size_t size) {
  int srcptrLength = s21_strlen(srcptr);
  int cpyLength = size > srcptrLength ? (srcptrLength + 1) : size;

  for (int x = 0; x < cpyLength; x += 1) {
    destptr[x] = srcptr[x];
  }

  return destptr;
}
