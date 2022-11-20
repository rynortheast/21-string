#ifndef SRC_HEADERS_S21_SPRINTF_H_
#define SRC_HEADERS_S21_SPRINTF_H_

typedef struct {
  char flag[10];
  int width;
  int accuracy;
  char type;
} spec;

int s21_sprintf(char *str, const char *format, ...);
int searchModifiersForString(int x, const char *format, spec *config,
                             va_list *params);
int insertStringBySpecifier(char *str, char symbol, spec config,
                            va_list *params);
int setBaseAccuracyValue(int accuracy, int symbol);

int s21_ctos(char *str, va_list *params, char *flag, int accuracy, char type);
char *s21_conf(char *str, spec config, char symbol);
char *s21_stos(char *str, va_list *params, int accuracy, char type);
char *s21_ptoa(char *str, int *variable);
char *s21_itoa(char *str, int number, int accuracy, char *flag);
char *s21_itoa_long(char *str, long int number, int accuracy, char *flag);
char *s21_itoa_short(char *str, short int number, int accuracy, char *flag);
char *s21_gtoa_long(char *str, long double number, int accuracy, char *flag,
                    int symbol);
char *s21_gtoa(char *str, double number, int accuracy, char *flag, int symbol);
char *s21_ftoa_long(char *str, long double number, int afterpoint, char *flag,
                    int kostyl_2);
char *s21_ftoa(char *str, double number, int afterpoint, char *flag,
               int kostyl_2);
char *s21_utoa(char *str, unsigned int number, int format, int accuracy,
               char *flag);
char *s21_utoa_long(char *str, unsigned long int number, int format,
                    int accuracy, char *flag);
char *s21_utoa_short(char *str, unsigned short int number, int format,
                     int accuracy, char *flag);
char *s21_ntoa_long(char *str, long double number, int accuracy, char *flag,
                    int symbol, int kostyl_2);
char *s21_ntoa(char *str, double number, int accuracy, char *flag, int symbol,
               int kostyl_2);

#endif  // SRC_HEADERS_S21_SPRINTF_H_
