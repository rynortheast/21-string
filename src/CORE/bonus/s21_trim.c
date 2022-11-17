#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *newstr = s21_NULL;
  if (src) {
    if (trim_chars && trim_chars[0]) {
      newstr = calloc(s21_strlen(src) + 1, 1);
      s21_size_t start = 0, end = s21_strlen(src);
      while (startwith(src, trim_chars, start)) {
        start++;
      }
      if (start != end) {
        while (endwith(src, trim_chars, end)) end--;
      } else {
        newstr[0] = '\0';
      }
      for (int i = 0; start < end; i++) {
        newstr[i] = src[start];
        start++;
      }
    } else {
      newstr = s21_trim(src, "\t\n ");
    }
  }
  return newstr;
}
