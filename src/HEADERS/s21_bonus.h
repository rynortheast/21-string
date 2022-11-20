#ifndef SRC_HEADERS_S21_BONUS_H_
#define SRC_HEADERS_S21_BONUS_H_

char *s21_reverse(char *str);
void *s21_to_upper(const char *str);
char *s21_strncat(char *str_main, const char *str_aux, s21_size_t accuracy);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif  // SRC_HEADERS_S21_BONUS_H_
