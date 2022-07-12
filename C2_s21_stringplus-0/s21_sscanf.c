#include "s21_string.h"
#define hex_max 0xffffffffffffffff
int mod_process(const char* format, mods *md) {
    int i = 0;
    while (s21_strchr("0123456789*hlL", format[i])) {
        if (s21_strchr("0123456789", format[i])) {
            md->len = s21_atoi(format + i, -1);
            i += s21_cnt_offset(format + i, "0123456789");
        }
        switch (format[i]) {
        case 'l':
            if (format[i+1] != 'l') {
                md->l = 1; i++;
            } else {
                md->ll = 1; i += 2;
            }
            break;
        case 'L':
            md->ll = 1; i++; break;
        case '*':
            md->skip = 1; i++; break;
        case 'h':
            md->h = 1; i++; break;
        }
    }
    return i;
}

int spec_process(const char* str, const char *format, int* j, int *i, va_list* args, int *check) {
    int res = 1;
    const char numbers_dec[] = "0123456789";
    const char numbers_oct[] = "01234567";
    const char numbers_hex[] = "0123456789abcdefABCDEF";
    const char numbers_float[] = "0123456789.";
    mods md = init_default_mods();
    if (s21_strchr("0123456789*hlL", format[*i])) {
        *i += mod_process(format + *i, &md);
    }
    char sym = format[*i];
    if (sym != 'c' && sym != 'n') {
    while (!ok_sym(str[*j])) (*j)++;
    }
    switch (sym) {
    case 'c': {
        if (md.skip == -1) {
            char * symbol = va_arg(*args, char*);
            *j += specc(str + *j, symbol, md); break;
        }
        (*j)++; res = 0; break;
    }
    case 'u':
    case 'd': {
        if (!(*check = s21_check_num(str + *j, numbers_dec, md.len))) { res = 0; break;}
        *j += specnumber(str + *j, args, md, 10);
        if (md.skip != -1) res = 0;
        break;
        }
    case 'i': {
        if (!(*check = s21_check_num(str + *j, numbers_dec, md.len))) {res = 0; break;}
        int idx = *j;
        if (str[idx] == '-' || str[idx] == '+') idx++;
        if (str[idx] != '0') {
                *j += specnumber(str + *j, args, md, 10);
        } else {
            if (str[idx+1] != 'x' && str[idx+1] != 'X') {
                *j += specnumber(str + *j, args, md, 8);
            } else {
                *j += specnumber(str + *j, args, md, 16);
            }
        }
        if (md.skip != -1) res = 0;
        break;
    }
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G': {
        if (!(*check = s21_check_num(str + *j, numbers_float, md.len))) {res = 0; break;}
        if (md.skip != -1) res = 0;
        *j += specfloat(str + *j, args, md); break;
    }
    case 'o': {
        if (!(*check = s21_check_num(str + *j, numbers_oct, md.len))) {res = 0; break;}
        if (md.skip != -1) res = 0;
        *j += specnumber(str + *j, args, md, 8); break;
    }
    case 's': {
        if (md.len == 0 || md.skip != -1) res = 0;
        *j += specs(str + *j, args, md); break;
    }
    case 'x':
    case 'X': {
        if (!(*check = s21_check_num(str + *j, numbers_hex, md.len))) {res = 0; break;}
        if (md.skip != -1) res = 0;
        *j += specnumber(str + *j, args, md, 16); break;
    }
    case 'p': {
        if (!(*check = s21_check_num(str + *j, numbers_hex, md.len))) {res = 0; break;}
        if (md.skip != -1) res = 0;
        *j += specp(str + *j, args, md); break;
    }
    case 'n': {
        specn(*j, args, md); res = 0; break;
    }
    case '%': {
        res = 0;
        if
            (str[*j] == '%') (*j)++;
        else
            *check = 0;
        break;
    }
    }
    return res;
}

int s21_sscanf(const char* str, const char* format, ...) {
    int res = 0, j = 0, i = 0, check = 1;
    const char spec[] = "cdieEfgGosuxXpn%";
    const char mod[] = "0123456789*hlL";
    va_list args;
    va_start(args, format);
    for (; format[i] != '\0' && check; i++) {
        if (str[j] == '\0') break;
        if (format[i] == '%') {
            i++;
            if (s21_strchr(spec, format[i]) || s21_strchr(mod, format[i])) {
                if (!s21_check_space(str, format, i, &j)) break;
                res += spec_process(str, format, &j, &i, &args, &check);
            }
        } else if (format[i] == str[j]) { j++;
        } else if (!ok_sym(format[i])) { continue;
        } else { check = 0;
        }
    }
    if (str[j] == '\0' && format[i] == '%' && format[i+1] == 'n')
        *(int*)va_arg(args, void*) = j;
    va_end(args);
    if (s21_strlen(str) == 0) res = -1;
    return res;
}

int s21_is_digit(const char sym) {
    int res = 1;
    if (!s21_strchr("0123456789", sym)) res = 0;
    return res;
}
int is_default(mods md) {
    int res = 0;
    if (md.h == -1 && md.l == -1 && md.ll == -1 && md.len == -1 && md.skip == -1) res = 1;
    return res;
}

long long atoi_by_base(int base, const char *str, int limit) {
    long long result = 0;
    if (base == 10) result = s21_atoi(str, limit);
    else if (base == 8) result = s21_oct_atoi(str, limit);
    else if (base == 16) result = s21_hex_atoi(str, limit);
    return result;
}
int offset_by_base(int base, const char *str, int limit) {
    int result = 0;
    if (base == 10) { result = s21_cnt_offset(str, "0123456789");
    } else if (base == 8) { result = s21_cnt_offset(str, "01234567");
    } else if (base == 16) {
        int i = 0;
        if (str[i] == '-' || str[i] == '+') i++;
        if (str[i] == '0' && (str[i+1] == 'X' || str[i+1] == 'x') && i + 2 != limit) i += 2;
        result = i + s21_cnt_offset(str + i, "0123456789abcdefABCDEF");
        if (result == i) result--;
    } else if (base == 1) {
        result = s21_cnt_offset(str, "0123456789.");
    }
    return (limit == -1) ? result : (limit > result) ? result : limit;
}

int specnumber(const char *str, va_list *args, mods md, int base) {
    if (md.skip == -1) {
        long long num = atoi_by_base(base, str, md.len);
        if (md.h != -1) {
            *(short int*)va_arg(*args, void*) = num;
        } else if (md.l != -1) {
            *(long int*)va_arg(*args, void*) = num;
        } else if (md.ll != -1) {
            *(long long int*)va_arg(*args, void*) = num;
        } else {
            *(int*)va_arg(*args, void*) = num;
        }
    }
    return offset_by_base(base, str, md.len);
}
int specc(const char *str, char *result, mods md) {
    int offset = 1;
    if (is_default(md)) {
        *result = str[0];
    } else {
        if (md.len != -1) {
            *result = str[0];
            while (str[offset] != '\0' && md.len != 1) {
                offset++;
                md.len--;
            }
        }
    }
    return offset;
}

int specfloat(const char *str, va_list *args, mods md) {
    if (md.skip == -1) {
        long double result = s21_atof(str, md.len);
        if (md.l != -1) {
            *(double*)va_arg(*args, void*) = result;
        } else if (md.ll != -1) {
            *(long double*)va_arg(*args, void*) = result;
        } else {
            *(float*)va_arg(*args, void*) = result;
        }
    }
    return offset_by_base(1, str, md.len);
}
void specn(long long j, va_list *args, mods md) {
    if (md.skip == -1) {
        if (md.h != -1) *(short*)va_arg(*args, void*) = j;
        else if (md.l != -1) *(long*)va_arg(*args, void*) = j;
        else if (md.ll != -1) *(long long*)va_arg(*args, void*) = j;
        else
            *(int*)va_arg(*args, void*) = j;
    }
}
int specp(const char *str, va_list *args, mods md) {
    if (md.skip == -1) {
        int i = 0, sign = define_sign(str[i], &i);
        if (str[i] == '0' && (str[i+1] == 'X' || str[i+1] == 'x')) i += 2;
        if (offset_by_base(16, str + i, md.len) > 16) {
             *(void**)va_arg(*args, void**) = (void*)0xffffffffffffffff;
        } else {
            if (sign != -1) {
                *(void**)va_arg(*args, void**) = (void*)s21_hex_atoi(str, md.len);
            } else {
                *(void**)va_arg(*args, void**) = ((void*)(hex_max + 1 - (s21_hex_atoi(str + 1, md.len))));
            }
        }
    }
    return offset_by_base(16, str, md.len);
}
int specs(const char *str, va_list *args, mods md) {
    int i = 0;
    if (md.skip == -1) {
        char *result = va_arg(*args, char*);
        while (ok_sym(str[i]) && i != md.len) {
            result[i] = str[i]; i++;
        }
        result[i] = '\0';
    } else {
        while (ok_sym(str[i])) i++;
    }
    return i;
}

mods init_default_mods() {
    mods md = {-1, -1, -1, -1, -1}; return md;
}

int define_sign(const char sym, int *idx) {
    int res = 1;
    if (sym == '-') {
        res = -1; *idx += 1;
    } else if (sym == '+') {
        *idx += 1;
    }
    return res;
}

int s21_check_num(const char *str, const char *src, int limit) {
    int res = 1;
    int i = 0;
    if (str[i] != '-' && str[i] != '+' && !s21_strchr(src, str[i])) {
            res = 0;
    } else if ((str[i] == '-' || str[i] == '+') && !s21_strchr(src, str[i+1])) {
            res = 0;
    } else if ((str[i] == '-' || str[i] == '+') && limit == 1) {
            res = 0;
    }
    return res;
}

int ok_sym(const char sym) {
    int res = 0;
    if ((sym < 9 || sym > 13) && sym != '\0' && sym != ' ') res = 1;
    return res;
}

int s21_cnt_offset(const char *str, const char *src) {
    int i = 0;
    int check = 0;
    if (str[i] == '-' || str[i] == '+') i++;
    while (s21_strchr(src, str[i]) && str[i] != '\0') {
        if (str[i] == '.') {
            if (check == 1) break;
            if (check == 0) check = 1;
        }
        i++;
    }
    return i;
}

char s21_sym_to_lower(const char sym) {
    char fsym = sym;
    if (sym >= 'A' && sym <= 'Z') fsym += 32;
    return fsym;
}

long long s21_atoi(const char *str, int limit) {
    long long int res = 0;
    int i = 0;
    int sign = define_sign(str[i], &i);
    while (str[i] >=  '0' && str[i] <= '9' && i != limit) {
        res = res * 10 + (str[i] - '0'); i++;
    }
    return res * sign;
}
long long s21_oct_atoi(const char *str, int limit) {
    long long res = 0;
    int i = 0;
    int sign = define_sign(str[0], &i);
    while (str[i] >= '0' && str[i] < '8' && str[i] != '\0' && i != limit) {
        res = res * 8 + (str[i] - '0');
        i++;
    }
    return res * sign;
}

int ishex(char sym) {
    int res = 0;
    if (sym >= '0' && sym <= '9') res = 1;
    if (sym >= 'a' && sym <= 'f') res = 1;
    if (sym >= 'A' && sym <= 'F') res = 1;
    return res;
}

long long s21_hex_atoi(const char *str, int limit) {
    long long res = 0;
    int i = 0;
    int sign = define_sign(str[i], &i);
    if (!(str[i] == '0' && !ishex(str[i+1]) && str[i+1] != 'X' && str[i+1] != 'x')) {
        if (str[i] != '\0' && str[i] == '0') {
            if (str[i+1] != '\0' && (str[i + 1] == 'x' || str[i+1] == 'X')) i += 2;
            if (i == limit || i-1 == limit) {
                i = limit; res = 0;
            }
        }
        while (ishex(str[i]) && str[i] != '\0' && i != limit) {
            int number = 0;
            if (s21_is_digit(str[i])) number = str[i] - '0';
            else
                number = s21_sym_to_lower(str[i]) - 'a' + 10;
            res = res * 16 + number;
            i++;
        }
        }
    return res * sign;
}


long double s21_atof(const char *str, int limit) {
    long double res = 0;
    int i = 0;
    int sign = define_sign(str[0], &i);
    while (str[i] >= '0' && str[i] <= '9' && i != limit) {
        res = res * 10 + (str[i] - '0'); i++;
    }
    if (str[i] == '.' && i != limit) {
        i++;
        int start = 1;
        while (str[i] >= '0' && str[i] <= '9' && i != limit) {
            res = res  + ((str[i] - '0') / pow(10, start)); i++;
            start++;
        }
    }
    return res * sign;
}

int s21_check_space(const char *str, const char *format, int i, int *j) {
    int res = 1;
    if (i < 2) {
        res = 1;
    } else if (!ok_sym(format[i-2]) && format[i-2] != '\0') {
        while (str[*j] == ' ' || str[*j] == '\t' || str[*j] == '\r'
        || str[*j] == '\n' || str[*j] == '\x0B' || str[*j] == '\f') {
            (*j)++;
        }
        if (str[*j] == '\0')
            res = 0;
    }
    return res;
}
