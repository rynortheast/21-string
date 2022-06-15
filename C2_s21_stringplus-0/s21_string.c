#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
    s21_size_t len = 0;
    for (; str[len]; len++) {}
    return len;
}

char * s21_strchr(const char * str, int symbol) {
    const char * result = s21_NULL;
    int str_len = s21_strlen(str) + 1;
    for (int counter = 0; counter < str_len; counter++) {
        if (str[counter] == symbol) {
            result = (str + counter);
            break;
        }
    }
    return (char *) result;
}

char * s21_strrchr(const char * str, int symbol) {
    const char * result = s21_NULL;
    int str_len = s21_strlen(str);
    for (int counter = str_len; counter >= 0; counter--) {
        if (str[counter] == symbol) {
            result = (str + counter);
            break;
        }
    }
    return (char *) result;
}

char * s21_strcat(char * str_main, const char * str_aux) {
    int str_aux_len = s21_strlen(str_aux);
    int str_main_len = s21_strlen(str_main);
    for (int counter = 0; counter <= str_aux_len; counter++)
        str_main[str_main_len + counter] = str_aux[counter];
    return str_main;
}

int s21_strcmp(const char * str_1, const char * str_2) {
    int counter = 0;
    while (str_1[counter] && str_2[counter] && (str_1[counter] == str_2[counter]))
        counter += 1;
    return str_1[counter] > str_2[counter] ? 1 : str_1[counter] < str_2[counter] ? (-1) : 0;
}

int s21_strncmp(const char * str_1, const char * str_2, s21_size_t n) {
    s21_size_t counter = 0;
    while (counter < n - 1 && str_1[counter] && str_2[counter] && (str_1[counter] == str_2[counter]))
        counter += 1;
    return str_1[counter] > str_2[counter] ? 1 : str_1[counter] < str_2[counter] ? (-1) : 0;
}

char * s21_strcpy(char * str_main, const char * str_aux) {
    int str_aux_len = s21_strlen(str_aux);
    for (int x = 0; x <= str_aux_len; x++) {
        str_main[x] = str_aux[x];
    }
    return str_main;
}

// works wrong (FIXED)
char * s21_strncpy(char * str_main, const char * str_aux, s21_size_t n) {
    s21_size_t str_aux_len = s21_strlen(str_aux);
    s21_size_t copy_len = str_aux_len < n ? str_aux_len : n;
    s21_size_t x = 0;
    for (; x < copy_len; x++) {
        str_main[x] = str_aux[x];
    }
    str_main[x] = '\0'; 
    return str_main;
}

s21_size_t s21_strcspn(const char * str, const char * key) {
    s21_size_t result = 0;
    for (result = 0; result <= (s21_strlen(str) + 1); result++) {
        if (s21_strchr(key, str[result]))
            break;
    }
    return result;
}

// works wrong (not returning NULL) (FIXED)
char * s21_strpbrk(const char * str, const char * key) {
    s21_size_t result = 0;
    int check = 0;
    for (result = 0; result < (s21_strlen(str)); result++) {
        if (s21_strchr(key, str[result])) {
            check = 1;
            break;
        }
    }
    return (char*)((check == 1) ? str + result : s21_NULL);
}

s21_size_t s21_strspn(const char * str, const char * key) {
    s21_size_t str_len = s21_strlen(str), result = 0;
    for (s21_size_t x = 0; x < str_len; x++) {
        if (s21_strchr(key, str[x]) != s21_NULL) {
            result = x + 1;
            continue;
        }
        break;
    }
    return result;
}

//mistake somewhere
char * s21_strstr(const char * str_main, const char * str_aux) {
    size_t str_aux_len = s21_strlen(str_aux);
    char * result = s21_NULL;
    char * first_symbol = s21_strchr(str_main, str_aux[0]);
    for (;;) {
        if (first_symbol != s21_NULL) {
            if (s21_strncmp(first_symbol, str_aux, str_aux_len) == 0) {
                result = first_symbol;
            } else {
                first_symbol = s21_strchr(first_symbol + 1, str_aux[0]);
                continue;
            }
        }
        break;
    }
    return result;
}

char * s21_strtok(char * str, const char * key) {
    static char * next = s21_NULL;
    char * result = s21_NULL;
    if (str == s21_NULL) {
        str = next;
    }
    if (str[0] != '\0') {
        s21_size_t str_len = s21_strlen(str);
        for (s21_size_t x = 0; x <= str_len; x++) {
            if (str[x] == '\0') {
                next = (str + x);
                result = str;
                break;
            } else if (s21_strchr(key, str[x])) {
                while (s21_strchr(key, str[x])) {
                    str[x] = '\0';
                    x += 1;
                }
                next = (str + x);
                result = str;
                break;
            }
        }
    }
    return result;
}

//may be useful for sscanf sprintf
// char *reverse(char *strnum) {
//     s21_size_t size = s21_strlen(strnum);
//     s21_size_t j = size - 1;
//     char tmpstr[size];
//     s21_strcpy(tmpstr, strnum);
//     for (s21_size_t i = 0; i < size; i++) {
//         strnum[i] = tmpstr[j];
//         j--;
//     }
//     return strnum;
// }
// char *s21_itoa(int number) {
//     int symcnt = 0;
//     int tmp = number;
//     while(tmp > 0) {
//         tmp /= 10;
//         symcnt++;
//     }
//     char *strnum = calloc(symcnt, 1);
//     for (int i = 0; i<symcnt; i++) {
//         strnum[i] = number % 10 + '0';
//         number /= 10;
//     }
//     reverse(strnum);
//     return strnum;
// }

const char * s21_strerror(int errnum) {
    const char *result = sys_errlist[errnum];
    return (sys_nerr >= errnum && errnum >= 0) ? result : "Unknown error";
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
    int check = 0;
    const char * newArr = str;
    for (s21_size_t i = 0; i < n; i++) {
        if (newArr[i] == '\0') break;
        if (check == 0 && newArr[i] == c) {
            check = 1;
            newArr += i;
        }
    }
    if (check == 0)
        return s21_NULL;
    else
        return (void*)newArr;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int res = 0;
    int stop = 0;
    const char *rstr1 = str1, *rstr2 = str2;
    for (s21_size_t i = 0; i < n && !stop; i++) {
        if (rstr1[i] == '\0' || rstr2[i] == '\0') {
            stop = 1;
            if (rstr1[i] != '\0' && rstr2[i] == '\0')
                res = 1;
            if (rstr1[i] == '\0' && rstr2[i] != '\0')
                res = -1;
        } else {
            if (rstr1[i] > rstr2[i]) {
                res = 1;
                stop = 1;
            } else if (rstr1[i] < rstr2[i]) {
                res = -1;
                stop = 1;
            }
        }
    }
    return res;
}

// by the way: you cannot make n >= sizeof(dest);
// if n > sizeof(dest) it will not compile, how to implement it?
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++) {
        ((char*)dest)[i] = ((char*)src)[i];
    }
    return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
     const char *srcstr = src;
    for (s21_size_t i = 0; i < n; i++) {
        ((char*)dest)[i] = srcstr[i];
    }
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++) {
        ((char*)str)[i] = c;
    }
    return str;
}

// mistakes?
void* s21_to_upper(const char *str) {
    char *newstr = malloc(s21_strlen(str) + 1);
    for (unsigned long long i = 0; i < s21_strlen(str); i++) {
        if (str[i] < 'a' || str[i] > 'z') {
            newstr[i] = str[i];
        } else {
            newstr[i] = str[i] - 32;
        }
    }
    return newstr;
}

// mistakes?
void* s21_to_lower(const char *str) {
    char *newstr = malloc(s21_strlen(str) + 1);
    for (unsigned long long i = 0; i < s21_strlen(str); i++) {
        if (str[i] < 'A' || str[i] > 'Z') {
            newstr[i] = str[i];
        } else {
            newstr[i] = str[i] + 32;
        }
    }
    return newstr;
}

    // check if ascii?
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    s21_size_t size = s21_strlen(src) + s21_strlen(str);
    char *newstr = calloc(size + 1, 1);
    int check = 1;
    if (start_index > s21_strlen(src)) check = 0;
    if (check != 0) {
        s21_size_t i = 0;
        s21_size_t idx = 0;
        for (; i < start_index; i++) {
            newstr[i] = src[i];
            idx++;
        }
        for (s21_size_t k = 0; k < s21_strlen(str); k++) {
            newstr[i] = str[k];
            i++;
        }
        for (; idx < s21_strlen(src); idx++) {
            newstr[i] = src[idx];
            i++;
        }
    } else {
        free(newstr);
        newstr = NULL;
    }
    return newstr;
}

int startwith(const char *src, const char *totrim, int offset) {
    int res = 0;
    int size = s21_strlen(totrim);
    for (int i = 0; i < size; i++) {
        if (src[offset] == totrim[i])
            res = 1;
    }
    return res;
}

int endwith(const char *src, const char *totrim, int offset) {
    int res = 0;
    offset--;
    int size = s21_strlen(totrim);
    for (int i = 0; i < size; i++) {
        if (src[offset] == totrim[i])
            res = 1;
    }
    return res;
}

// check is ASCII?
void *s21_trim(const char *src, const char *trim_chars) {
    char *newstr = calloc(s21_strlen(src) + 1, 1);
    s21_size_t start = 0, end = s21_strlen(src);
    while (startwith(src, trim_chars, start)) {
        start++;
    }
    if (start != end) {
        while (endwith(src, trim_chars, end))
        end--;
    } else {
        newstr[0] = '\0';
    }
    for (int i = 0; start < end; i++) {
        newstr[i] = src[start];
        start++;
    }
    return newstr;
}
