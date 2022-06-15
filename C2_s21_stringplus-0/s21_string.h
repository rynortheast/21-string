#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define s21_NULL ((void*)0) 
typedef long unsigned s21_size_t;

const char * s21_strerror(int errnum);
s21_size_t s21_strlen(const char * str);
char * s21_strtok(char * str, const char * key);
char * s21_strchr(const char * str, int symbol);
char * s21_strrchr(const char * str, int symbol);
void *s21_memset(void *str, int c, s21_size_t n);
char * s21_strpbrk(const char * str, const char * key);
int s21_strcmp(const char * str_1, const char * str_2);
s21_size_t s21_strcspn(const char * str, const char * key);
void *s21_memchr(const void *str, int c, s21_size_t n);
char * s21_strcpy(char * str_main, const char * str_aux);
char * s21_strcat(char * str_main, const char * str_aux);
s21_size_t s21_strspn(const char * str, const char * key);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
char * s21_strstr(const char * str_main, const char * str_aux);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
int s21_strncmp(const char * str_1, const char * str_2, s21_size_t n);
char * s21_strncpy(char * str_main, const char * str_aux, s21_size_t n);
void* s21_to_upper(const char *str);
void* s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif  // SRC_S21_STRING_H_
