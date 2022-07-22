#include "s21_string.h"
#include "string.h"

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

char * s21_strcat(char * str_main, const char * str_aux) {
    int str_aux_len = s21_strlen(str_aux);
    int str_main_len = s21_strlen(str_main);
    for (int counter = 0; counter <= str_aux_len; counter++)
        str_main[str_main_len + counter] = str_aux[counter];
    return str_main;
}

char * s21_strncat(char * str_main, const char * str_aux, s21_size_t accuracy) {
    int len = s21_strlen(str_main);
    for (s21_size_t counter = 0; counter < accuracy && str_aux[counter] != '\0'; counter += 1) {
        str_main[len + counter] = str_aux[counter];
        str_main[len + counter + 1] = '\0';
    }
    return str_main;
}

int s21_strcmp(const char * str_1, const char * str_2) {
    int counter = 0;
    while (str_1[counter] && str_2[counter] && (str_1[counter] == str_2[counter]))
        counter += 1;
    return str_1[counter] > str_2[counter] ? 1 : str_1[counter] < str_2[counter] ? (-1) : 0;
}

int s21_strncmp(const char * str_1, const char * str_2, s21_size_t n) {
    int result = 0;
    for (s21_size_t counter = 0; counter < n; counter += 1) {
        if (str_1[counter] == str_2[counter]) {
            if (str_1[counter] != '\0')
                continue;
            break;
        } else {
            result = str_1[counter] - str_2[counter];
        }
        break;
    }
    return result;
}

char * s21_strcpy(char * str_main, const char * str_aux) {
    int str_aux_len = s21_strlen(str_aux);
    for (int x = 0; x <= str_aux_len; x++) {
        str_main[x] = str_aux[x];
    }
    return str_main;
}

char * s21_strncpy(char * str_main, const char * str_aux, s21_size_t n) {
    for (s21_size_t x = 0; x < n; x += 1) {
        str_main[x] = str_aux[x];
        if (str_aux[x] == '\0')
            break;
    }
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

char * s21_strstr(const char * str_main, const char * str_aux) {
    char * result = s21_NULL;
    size_t strAuxLen = s21_strlen(str_aux);
    if (strAuxLen != 0) {
        for (int x = 0; str_main[x] != '\0'; x += 1) {
            if (str_main[x] != str_aux[0]) {
                continue;
            }
            if (strncmp(str_main + x, str_aux, strAuxLen) == 0) {
                result = ((char *) str_main + x);
                break;
            }
        }
    } else {
        result = (char *) str_main;
    }
    return result;
}

char *s21_strtok(char *str, const char *delim) {
    static int next, restok;
    static s21_size_t idx;
    static char *ptr;
    static char *addr;

    if (str) {
        restok = 1;
        idx = 0, next = 0;
        addr = str + s21_strspn(str, delim);
        ptr = str + s21_strlen(str);
    }
    char *res = s21_NULL;
    if (!(addr >= ptr || next)) {
        int exdelim = 1;
        for (int i = 0; addr[i]; i++) {
            s21_size_t step = s21_strspn(addr + i, delim);
            if (step != 0) {
                exdelim = 0;
                for (s21_size_t j = i; j < i + step; j++) addr[j] = '\0';

                idx = step + i;
                break;
            }
        }
        if (restok == 1 && exdelim) next = 1;
        res = addr;
        addr += idx;
    }
    restok += 1;
    return res;
}

#if defined(__APPLE__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1
#define ERROR "Unknown error: "

const char *myerror[] = {
  "Undefined error: 0",
  "Operation not permitted",
  "No such file or directory",
  "No such process",
  "Interrupted system call",
  "Input/output error",
  "Device not configured",
  "Argument list too long",
  "Exec format error",
  "Bad file descriptor",
  "No child processes",
  "Resource deadlock avoided",
  "Cannot allocate memory",
  "Permission denied",
  "Bad address",
  "Block device required",
  "Resource busy",
  "File exists",
  "Cross-device link",
  "Operation not supported by device",
  "Not a directory",
  "Is a directory",
  "Invalid argument",
  "Too many open files in system",
  "Too many open files",
  "Inappropriate ioctl for device",
  "Text file busy",
  "File too large",
  "No space left on device",
  "Illegal seek",
  "Read-only file system",
  "Too many links",
  "Broken pipe",
  "Numerical argument out of domain",
  "Result too large",
  "Resource temporarily unavailable",
  "Operation now in progress",
  "Operation already in progress",
  "Socket operation on non-socket",
  "Destination address required",
  "Message too long",
  "Protocol wrong type for socket",
  "Protocol not available",
  "Protocol not supported",
  "Socket type not supported",
  "Operation not supported",
  "Protocol family not supported",
  "Address family not supported by protocol family",
  "Address already in use",
  "Can't assign requested address",
  "Network is down",
  "Network is unreachable",
  "Network dropped connection on reset",
  "Software caused connection abort",
  "Connection reset by peer",
  "No buffer space available",
  "Socket is already connected",
  "Socket is not connected",
  "Can't send after socket shutdown",
  "Too many references: can't splice",
  "Operation timed out",
  "Connection refused",
  "Too many levels of symbolic links",
  "File name too long",
  "Host is down",
  "No route to host",
  "Directory not empty",
  "Too many processes",
  "Too many users",
  "Disc quota exceeded",
  "Stale NFS file handle",
  "Too many levels of remote in path",
  "RPC struct is bad",
  "RPC version wrong",
  "RPC prog. not avail",
  "Program version wrong",
  "Bad procedure for program",
  "No locks available",
  "Function not implemented",
  "Inappropriate file type or format",
  "Authentication error",
  "Need authenticator",
  "Device power is off",
  "Device error",
  "Value too large to be stored in data type",
  "Bad executable (or shared library)",
  "Bad CPU type in executable",
  "Shared library version mismatch",
  "Malformed Mach-o file",
  "Operation canceled",
  "Identifier removed",
  "No message of desired type",
  "Illegal byte sequence",
  "Attribute not found",
  "Bad message",
  "EMULTIHOP (Reserved)",
  "No message available on STREAM",
  "ENOLINK (Reserved)",
  "No STREAM resources",
  "Not a STREAM",
  "Protocol error",
  "STREAM ioctl timeout",
  "Operation not supported on socket",
  "Policy not found",
  "State not recoverable",
  "Previous owner died",
  "Interface output queue is full"
};

#elif defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define ERROR  "Unknown error "

static const char *myerror[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"
};
#endif

char *s21_strerror(int errnum) {
    char *res = NULL;
    static char buf[512] = {'\0'};
    if (errnum <= MIN_ERRLIST || errnum >= MAX_ERRLIST) {
        s21_sprintf(buf, "Unknown error: %d", errnum);
        res = buf;
    } else {
        res = (char *)myerror[errnum];
    }
    return res;
}


void *s21_memchr(const void *str, int c, s21_size_t n) {
    int check = 0;
    const char * newArr = str;
    for (s21_size_t i = 0; newArr && i < n; i++) {
        if (check == 0 && newArr[i] == c) {
            check = 1;
            if (c == '\0') break;
            newArr += i;
        }
    }
    if (check == 0)
        return s21_NULL;
    else
        return (void*)newArr;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    unsigned char *tmp1 = (unsigned char *)str1;
    unsigned char *tmp2 = (unsigned char *)str2;
    int res = 0;
    for (s21_size_t i = 0; i < n; i++) {
        res = tmp1[i] - tmp2[i];
        if (tmp1[i] != tmp2[i]) break;
    }
    return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++) {
        ((char*)dest)[i] = ((char*)src)[i];
    }
    return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char *tocpy = (char *)dest;
    char *fromcpy = (char *)src;
    char *tmp = (char *)malloc(sizeof(char) * n);
    if (tmp) {
        s21_memcpy(tmp, fromcpy, n);
        s21_memcpy(tocpy, tmp, n);
        free(tmp);
    }
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++) {
        ((char*)str)[i] = c;
    }
    return str;
}

void* s21_to_upper(const char *str) {
    char *newstr = calloc(s21_strlen(str) + 1, 1);
    for (unsigned long long i = 0; i < s21_strlen(str); i++) {
        if (str[i] < 'a' || str[i] > 'z') {
            newstr[i] = str[i];
        } else {
            newstr[i] = str[i] - 32;
        }
    }
    return newstr;
}

void* s21_to_lower(const char *str) {
    char *newstr = calloc(s21_strlen(str) + 1, 1);
    for (unsigned long long i = 0; i < s21_strlen(str); i++) {
        if (str[i] < 'A' || str[i] > 'Z') {
            newstr[i] = str[i];
        } else {
            newstr[i] = str[i] + 32;
        }
    }
    return newstr;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *res = s21_NULL;
    s21_size_t src_length, str_length;
    src_length = (src == s21_NULL) ? 0 : s21_strlen(src);
    str_length = (str == s21_NULL) ? 0 : s21_strlen(str);
    s21_size_t fin_length = src_length + str_length;
    if (start_index <= src_length) {
        res = (char *)calloc(src_length + str_length + 1, sizeof(char));
    }
    if (res) {
        for (s21_size_t i = 0; i < fin_length; i++) {
            if (i < start_index) {
                res[i] = src[i];
            } else if (i < str_length + start_index) {
                res[i] = str[i - start_index];
            } else {
                res[i] = src[i - str_length];
            }
        }
    }
    return res;
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
                while (endwith(src, trim_chars, end))
                end--;
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

