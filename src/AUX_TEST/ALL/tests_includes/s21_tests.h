#ifndef SRC_TESTS_INCLUDES_S21_TESTS_H_
#define SRC_TESTS_INCLUDES_S21_TESTS_H_

#include <check.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../../../s21_string.h"

#define BUFF_SIZE BUFSIZ

Suite *suite_sprintf(void);
Suite *suite_insert(void);
Suite *suite_memcmp(void);
Suite *suite_trim(void);
Suite *suite_sscanf(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  // SRC_TESTS_INCLUDES_S21_TESTS_H_
