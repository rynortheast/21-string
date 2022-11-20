#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define s21_NULL ((void *)0)

typedef long unsigned s21_size_t;

void *s21_memchr(const void *str, int symbol, s21_size_t size);
int s21_memcmp(const void *mem_1, const void *mem_2, s21_size_t size);
void *s21_memcpy(void *dest, const void *src, s21_size_t size);
void *s21_memmove(void *dest, const void *src, s21_size_t size);
void *s21_memset(void *str, int symbol, s21_size_t size);
char *s21_strcat(char *destptr, const char *srcptr);
char *s21_strchr(const char *str, int symbol);
int s21_strcmp(const char *str_1, const char *str_2);
char *s21_strcpy(char *destptr, const char *srcptr);
s21_size_t s21_strcspn(const char *str, const char *keys);
char *s21_strerror(int errorNumber);
s21_size_t s21_strlen(const char *str);
int s21_strncmp(const char *str_1, const char *str_2, s21_size_t size);
char *s21_strncpy(char *destptr, const char *srcptr, s21_size_t size);
char *s21_strpbrk(const char *str, const char *keys);
char *s21_strrchr(const char *str, int symbol);
s21_size_t s21_strspn(const char *str, const char *keys);
char *s21_strstr(const char *destptr, const char *srcptr);
char *s21_strtok(char *str, const char *delim);
char *s21_strncat(char *result, const char *str, s21_size_t size);

#include "HEADERS/s21_bonus.h"
#include "HEADERS/s21_sprintf.h"
#include "HEADERS/s21_sscanf.h"

#endif  // SRC_S21_STRING_H_
