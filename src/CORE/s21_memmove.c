#include "../s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t size) {
  char *aux = (char *)malloc(sizeof(char) * size);

  if (aux) {
    s21_memcpy(aux, ((char *)src), size);
    s21_memcpy(((char *)dest), aux, size);
    free(aux);
  }

  return dest;
}
