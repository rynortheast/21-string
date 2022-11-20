#ifndef SRC_HEADERS_S21_SSCANF_H_
#define SRC_HEADERS_S21_SSCANF_H_

struct mods {
  int len;
  int skip;
  int h;
  int l;
  int ll;
};

typedef struct mods mods;

typedef struct {
  int format;
  long count;
  int end;
  int supr;
  int wid;
  int len;
  int err;
  char buff;
} ops;

int s21_sscanf(const char *str, const char *format, ...);
int opd(va_list args, ops *op, char **src, int base);
int opu(va_list args, ops *op, char **src, int base);
int opf(va_list args, ops *op, char **src);
int opp(va_list args, ops *op, char **src);
int opc(va_list args, ops *op, char **src);
int opst(va_list args, ops *op, char **src);
void oksym(char **src, ops *op);
void oppe(char **src, ops *op, const char *format);
int optionsin(char **src, ops *op, const char *format);
void opn(va_list args, ops *op);
void casenon(char **src, ops *op, const char *format);
int isbreak(va_list args, ops *op, char **src, const char *format);
int processformat(va_list args, ops *op, char **src, const char *format);
void check_buffer(char **src, ops *op);
long s21_atoi(char *str, char **strlim, int base);
unsigned long s21_atoul(char *str, char **strlim, int base);
long double s21_atold(char *str, char **strlim);
float s21_atof(char *str, char **strlim);
double s21_atod(char *str, char **strlim);

#endif  // SRC_HEADERS_S21_SSCANF_H_
