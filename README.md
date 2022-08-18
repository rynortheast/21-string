
# S21_string

<div align="center">PREVIEW_WILL_BE_ADDED_LATER.png</div>

## Table of contents
* [About](#about)
* [Goal & requirements](#goal--requirements)
* [Key learnings](#key-learnings)
* [Building](#building)
* [Overview of implemented code](#overview-of-implemented-code)
    * [string.h Types](#stringh-types)
    * [string.h Macro](#stringh-Macro)
    * [string.h Functions](#stringh-Functions)
    * [sprintf & sscanf](#sprintf--sscanf)
    * [sprintf & sscanf Specifiers](#sprintf--sscanf-specifiers)
    * [sprintf Flags](#sprintf-flags)
    * [sprintf & sscanf Width Description](#sprintf--sscanf-width-description)
    * [sprintf Precision Description](#sprintf-precision-description)
    * [sprintf & sscanf Length Description](#sprintf--sscanf-length-description)
* [Credits](#credits)

## About 

Implementation of some functions of `string.h` library with tests.

## Goal & requirements 

The goal of this project is to understand how string processing functions work using C language. In the course of the work, analyze the existing auxiliary functions of string processing, determine how other data types are translated into strings.

## Key learnings

- Working with arrays of characters
- Working with pointers of `void` type
- Functions with variable number of arguments
- Algorithms for processing other types of data to translate them into an array of characters
- Unit-testing with Check framework
- Evaluating test coverage with gcov

## Overview of implemented code

### string.h Types

| No. | Variable | Description | Status |
| ------ | ------ | ------ | ------ |
| 1 | size_t | This is the unsigned integral type and is the result of the sizeof keyword. | ✅ |

### string.h Macro

| No. | Macro | Description | Status |
| ------ | ------ | ------ | ------ |
| 1 | NULL | This macro is the value of a null pointer constant. | ✅ |

### string.h Functions

| No. | Function | Description | Status |
| ------ | ------ | ------ | ------ |
| 1 | void *memchr(const void *str, int c, size_t n) | Searches for the first occurrence of the character c (an unsigned char) in the first n bytes of the string pointed to, by the argument str. | ☑️ |
| 2 | int memcmp(const void *str1, const void *str2, size_t n) | Compares the first n bytes of str1 and str2. | ☑️ |
| 3 | void *memcpy(void *dest, const void *src, size_t n) | Copies n characters from src to dest. | ☑️ |
| 4 | void *memmove(void *dest, const void *src, size_t n) | Another function to copy n characters from src to dest. | ☑️ |
| 5 | void *memset(void *str, int c, size_t n) | Copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str. | ☑️ |
| 6 | char *strcat(char *dest, const char *src) | Appends the string pointed to, by src to the end of the string pointed to by dest. | ✅ |
| 7 | char *strncat(char *dest, const char *src, size_t n) | Appends the string pointed to, by src to the end of the string pointed to, by dest up to n characters long. | ✅ |
| 8	| char *strchr(const char *str, int c) | Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str. | ✅ |
| 9 | int strcmp(const char *str1, const char *str2) | Compares the string pointed to, by str1 to the string pointed to by str2. | ✅ |
| 10 | int strncmp(const char *str1, const char *str2, size_t n) | Compares at most the first n bytes of str1 and str2. | ✅ |
| 11 | char *strcpy(char *dest, const char *src) | Copies the string pointed to, by src to dest. | ✅ |
| 12 | char *strncpy(char *dest, const char *src, size_t n) | Copies up to n characters from the string pointed to, by src to dest. | ✅ |
| 13 | size_t strcspn(const char *str1, const char *str2) | Calculates the length of the initial segment of str1 which consists entirely of characters not in str2. | ✅ |
| 14 | char *strerror(int errnum) | Searches an internal array for the error number errnum and returns a pointer to an error message string. You need to declare macros containing arrays of error messages for mac and linux operating systems. Error descriptions are available in the original library. Checking the current OS is carried out using directives. |
| 15 | size_t strlen(const char *str) | Computes the length of the string str up to but not including the terminating null character. | ✅ |
| 16 | char *strpbrk(const char *str1, const char *str2) | Finds the first character in the string str1 that matches any character specified in str2. | ✅ |
| 17 | char *strrchr(const char *str, int c) | Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str. | ✅ |
| 18 | size_t strspn(const char *str1, const char *str2) | Calculates the length of the initial segment of str1 which consists entirely of characters in str2. | ✅ |
| 19 | char *strstr(const char *haystack, const char *needle) | Finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack. | ✅ |
| 20 | char *strtok(char *str, const char *delim) | Breaks string str into a series of tokens separated by delim. | ✅ |

### sprintf & sscanf

| No. | Function | Description | Status |
| ------ | ------ | ------ | ------ |
| 1 | int sscanf(const char *str, const char *format, ...) | reads formatted input from a string. | ☑️ |
| 2 | int sprintf(char *str, const char *format, ...) | sends formatted output to a string pointed to, by str. | ✅ |

### sprintf & sscanf Specifiers

| No. | Specifier | sprintf output | sscanf output | sprintf Status | sscanf Status |
| --- | --- | --- | --- | ------ | ------ |
| 1 | c | Character | Character | ✅ | ☑️ |
| 2 | d | Signed decimal integer | Signed decimal integer | ✅ | ☑️ |
| 3 | i | Signed decimal integer | Signed integer (may be decimal, octal or hexadecimal) | ✅ | ☑️ |
| 4 | e | Scientific notation (mantissa/exponent) using e character (the output of the numbers must match up to e-6) | Decimal floating point or scientific notation (mantissa/exponent) | ✅ | ☑️ |
| 5 | E | Scientific notation (mantissa/exponent) using E character | Decimal floating point or scientific notation (mantissa/exponent) | ✅ | ☑️ |
| 6 | f | Decimal floating point | Decimal floating point or scientific notation (mantissa/exponent) | ✅ | ☑️ |
| 7 | g | Uses the shortest representation of decimal floating point | Decimal floating point or scientific notation (mantissa/exponent) | ✅ | ☑️ |
| 8 | G | Uses the shortest representation of decimal floating point | Decimal floating point or scientific notation (mantissa/exponent) | ✅ | ☑️ |
| 9 | o | Unsigned octal | Unsigned octal | ✅ | ☑️ |
| 10 | s | String of characters | String of characters | ✅ | ☑️ |
| 11 | u | Unsigned decimal integer | Unsigned decimal integer | ✅ | ☑️ |
| 12 | x | Unsigned hexadecimal integer | Unsigned hexadecimal integer (any letters) | ✅ | ☑️ |
| 13 | X | Unsigned hexadecimal integer (capital letters) | Unsigned hexadecimal integer (any letters) | ✅ | ☑️ |
| 14 | p | Pointer address | Pointer address | ✅ | ☑️ |
| 15 | n | Number of characters printed until %n occurs | Number of characters scanned until %n occurs | ✅ | ☑️ |
| 16 | % | Character % | Character % | ✅ | ☑️ |

### sprintf Flags

| No. | Flags | Description | Status |
| --- | --- | --- | ------ |
| 1 | - | Left-justify within the given field width; Right justification is the default (see width sub-specifier). | ✅ |
| 2 | + | Forces to precede the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a -ve sign. | ✅ |
| 3 | (space) | If no sign is going to be written, a blank space is inserted before the value. | ✅ |
| 4 | # | Used with o, x or X specifiers the value is preceded with 0, 0x or 0X respectively for values different than zero. Used with e, E and f, it forces the written output to contain a decimal point even if no digits would follow. By default, if no digits follow, no decimal point is written. Used with g or G the result is the same as with e or E but trailing zeros are not removed. | ✅ |
| 5 | 0 | Left-pads the number with zeroes (0) instead of spaces, where padding is specified (see width sub-specifier). | ✅ |

### sprintf & sscanf Width Description

| No. |	Width | Description | sprintf Status | sscanf Status |
| --- | --- | --- | ------ | ------ |
| 1	| (number) | Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger. | ✅ | ☑️ |
| 2 | * | In sprintf the * sign means, that the width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted. In sscanf the * sign placed after % and before the format specifier reads data of the specified type, but suppresses their assignment. | ✅ | ☑️ |

### sprintf Precision Description

| No. |	.precision | Description | Status |
| --- | --- | --- | ------ |
| 1	| .number | For integer specifiers (d, i, o, u, x, X) − precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0. For e, E and f specifiers − this is the number of digits to be printed after the decimal point. For g and G specifiers − This is the maximum number of significant digits to be printed. For s − this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered. For c type − it has no effect. When no precision is specified for specifiers e, E, f, g and G, the default one is 6. When no precision is specified for all other kind of specifiers, the default is 1. If the period is specified without an explicit value for precision, 0 is assumed. | ✅ |
| 2	| .* | The precision is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted. | ✅ |

### sprintf & sscanf Length Description

| No. |	Length | Description | sprintf Status | sscanf Status |
| --- | --- | --- | ------ | ------ |
| 1 | h | The argument is interpreted as a short int or unsigned short int (only applies to integer specifiers: i, d, o, u, x and X). | ✅ | ☑️ |
| 2 | l | The argument is interpreted as a long int or unsigned long int for integer specifiers (i, d, o, u, x and X), and as a wide character or wide character string for specifiers c and s. | ✅ | ☑️ |
| 3 | L | The argument is interpreted as a long double (only applies to floating point specifiers − e, E, f, g and G). | ✅ | ☑️ |

## Building

1. Clone this repository via
    - SSH `git@github.com:rynortheast/S21_string.git` or
    - HTTPS `https://github.com/rynortheast/S21_string.git`
2. Change code base if necessary
3. Run `make test` to build project and run main tests
4. Run `make auxTest` to build project and run aux tests
5. Run `make s21_string.a` to build a static lib

## Credits

- Developer: [RV-304 (@rynortheast)](https://github.com/rynortheast) ✅, [Artem Kain (@artemxgod)](https://github.com/artemxgod) ☑️
- 21-SCHOOL for providing this task as a part of our curriculum ✌️🔥
