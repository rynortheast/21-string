#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(S21_STRLEN) {
  ck_assert_msg(s21_strlen("") == strlen(""), "FAILURE! Tes \"\" failed!");
  ck_assert_msg(s21_strlen("abc") == strlen("abc"),
                "FAILURE! Test \"abc\" failed!");
  ck_assert_msg(s21_strlen("123 ") == strlen("123 "),
                "FAILURE! Test \"123 \" failed!");
  ck_assert_msg(s21_strlen("l") == strlen("l"), "FAILURE! Test \"l\" failed!");
}
END_TEST

START_TEST(S21_STRCHR) {
  char msg[50] = "Hello, World!";
  ck_assert_msg(strcmp(s21_strchr("", '\0'), strchr("", '\0')) == 0,
                "FAILURE!");
  ck_assert_msg(strcmp(s21_strchr(msg, '\0'), strchr(msg, '\0')) == 0,
                "FAILURE! ");
  ck_assert_msg(strcmp(s21_strchr(msg, ','), strchr(msg, ',')) == 0,
                "FAILURE! ");
  ck_assert_msg(s21_strchr(msg, 'h') == strchr(msg, 'h'), "FAILURE! ");
  ck_assert_msg(strcmp(s21_strchr(msg, ' '), strchr(msg, ' ')) == 0,
                "FAILURE!");
}
END_TEST

START_TEST(S21_STRCAT) {
  char msg_1[50] = "";
  char msg_2[50] = "";
  ck_assert_msg(strcmp(s21_strcat(msg_1, ""), strcat(msg_2, "")) == 0,
                "FAILURE! Test \"\" + \"\" failed!");
  ck_assert_msg(
      strcmp(s21_strcat(msg_1, "Hello, "), strcat(msg_2, "Hello, ")) == 0,
      "FAILURE! Test ");
  ck_assert_msg(
      strcmp(s21_strcat(msg_1, "World!"), strcat(msg_2, "World!")) == 0,
      "FAILURE! Test ");
  ck_assert_msg(strcmp(s21_strcat(msg_1, ""), strcat(msg_2, "")) == 0,
                "FAILURE! Test ");
}
END_TEST

START_TEST(S21_STRCMP) {
  ck_assert_msg(s21_strcmp("", "") == strcmp("", ""),
                "FAILURE! Test \"\" + \"\" failed!");
  ck_assert_int_eq(s21_strcmp("11", "1"), strcmp("11", "1"));
  ck_assert_int_eq(s21_strcmp("1", "11"), strcmp("1", "11"));
  ck_assert_int_eq(s21_strcmp("12", "11"), strcmp("12", "11"));
  ck_assert_int_eq(s21_strcmp("1a", "1"), strcmp("1b", "1"));
  char c[10] = "abcde";
  char nc[10] = "ab";
  int res_norm = 0;
  res_norm = strcmp(c, nc) > 0 ? 1 : strcmp(c, nc) < 0 ? -1 : 0;
  ck_assert_int_eq(s21_strcmp(c, nc), res_norm);
}
END_TEST

START_TEST(S21_STRNCMP) {
  int res_norm = 0;
  res_norm = strncmp("", "", 5) > 0 ? 1 : strncmp("", "", 5) < 0 ? -1 : 0;
  ck_assert_msg(s21_strncmp("", "", 1) == res_norm,
                "FAILURE! Test \"\" + \"\" failed!");
  res_norm = strncmp("11", "1", 5) > 0 ? 1 : strncmp("11", "1", 5) < 0 ? -1 : 0;
  ck_assert_int_ge(s21_strncmp("11", "1", 2), res_norm);
  res_norm = strncmp("1", "11", 1) > 0 ? 1 : strncmp("1", "11", 1) < 0 ? -1 : 0;
  ck_assert_int_eq(s21_strncmp("1", "11", 1), res_norm);
  res_norm = strncmp("12", "11", 2) > 0   ? 1
             : strncmp("12", "11", 2) < 0 ? -1
                                          : 0;
  ck_assert_int_eq(s21_strncmp("12", "11", 2), res_norm);
  res_norm = strncmp("1abcde", "1abcdf", 5) > 0   ? 1
             : strncmp("1abcde", "1abcdf", 5) < 0 ? -1
                                                  : 0;
  ck_assert_int_eq(s21_strncmp("1abcde", "1abcdf", 5),
                   strncmp("1abcde", "1abcdf", 5));
  char c[10] = "abcde";
  char nc[10] = "ab";
  res_norm = strncmp(c, nc, 5) > 0 ? 1 : strncmp(c, nc, 5) < 0 ? -1 : 0;
  ck_assert_int_ge(s21_strncmp(c, nc, 5), res_norm);
}
END_TEST

START_TEST(S21_STRCPY) {
  char msg_1[50] = "";
  char msg_2[50] = "";
  ck_assert_msg(strcmp(s21_strcpy(msg_1, ""), strcpy(msg_2, "")) == 0,
                "FAILURE! Test ");
  ck_assert_msg(strcmp(s21_strcpy(msg_1, "TEST?"), strcpy(msg_2, "TEST?")) == 0,
                "FAILURE! Test ");
  ck_assert_msg(
      strcmp(s21_strcpy(msg_1, "HAhaHA"), strcpy(msg_2, "HAhaHA")) == 0,
      "FAILURE! Test ");
  ck_assert_msg(strcmp(s21_strcpy(msg_1, ""), strcpy(msg_2, "")) == 0,
                "FAILURE! Test copy \"\" failed!");
}
END_TEST

START_TEST(S21_STRNCPY) {
  char msg_1[50] = "";
  char msg_2[50] = "";
  ck_assert_msg(strcmp(s21_strncpy(msg_1, "", 1), strncpy(msg_2, "", 1)) == 0,
                "FAILURE! Test ");
  ck_assert_msg(
      strcmp(s21_strncpy(msg_1, "TEST?", 6), strncpy(msg_2, "TEST?", 6)) == 0,
      "FAIL");
  ck_assert_msg(
      strcmp(s21_strncpy(msg_1, "HAhaHA", 8), strncpy(msg_2, "HAhaHA", 8)) == 0,
      "FAI");
  ck_assert_msg(strcmp(s21_strncpy(msg_1, "", 2), strncpy(msg_2, "", 2)) == 0,
                "FAILURE! Test ");
}
END_TEST

// START_TEST(S21_STRERROR) {
//     for (int x = 200; x <= 201; x++) {
//         printf("%s\n", s21_strerror(x));
//         ck_assert_msg(strcmp(s21_strerror(x), strerror(x)) == 0, "FAILURE!
//         Test [-1 to 51] failed!");
//     }
// }
// END_TEST

START_TEST(S21_STRSPN) {
  ck_assert_msg(s21_strspn("", "") == strspn("", ""),
                "FAILURE! Test \"\" in \"\" failed!");
  ck_assert_msg(s21_strspn("", "TEST24") == strspn("", "TEST24"),
                "FAILURE! Test \"TEST24\" fai");
  ck_assert_msg(s21_strspn("test was success!", "TEST24") ==
                    strspn("test was success!", "TEST24"),
                "FAI");
  ck_assert_msg(s21_strspn("test was success!", "test24") ==
                    strspn("test was success!", "test24"),
                "FAI");
  ck_assert_msg(
      s21_strspn("test was success!", "") == strspn("test was success!", ""),
      "FAILURE! Test ");
}
END_TEST

START_TEST(S21_STRCSPN) {
  ck_assert_msg(s21_strcspn("", "") == strcspn("", ""),
                "FAILURE! Test \"\" in \"\" ");
  ck_assert_msg(s21_strcspn("", "TEST24") == strcspn("", "TEST24"),
                "FAILURE! Test ");
  ck_assert_msg(s21_strcspn("test was suc", "TEST24") ==
                    strcspn("test was suc", "TEST24"),
                "FAI");
  ck_assert_msg(s21_strcspn("test was suc", "test24") ==
                    strcspn("test was suc", "test24"),
                "F");
  ck_assert_msg(
      s21_strcspn("test was success!", "") == strcspn("test was success!", ""),
      "FAILURE! ");
}
END_TEST

START_TEST(S21_STRPBRK) {
  ck_assert_int_eq(
      strcmp(s21_strpbrk("this is", "abs"), strpbrk("this is", "abs")), 0);
  ck_assert_int_eq(
      strcmp(s21_strpbrk("this is", "th"), strpbrk("this is", "th")), 0);
  ck_assert_int_eq(
      strcmp(s21_strpbrk("this is", "hi"), strpbrk("this is", "hi")), 0);
  ck_assert_msg(s21_strpbrk("this is", "") == strpbrk("this is", ""),
                "FAILURE! Test");
  ck_assert_msg(s21_strpbrk("this is", "dplf") == strpbrk("this is", "dplf"),
                "Fail");
}
END_TEST

START_TEST(S21_STRRCHR) {
  char msg[50] = "Hello, World!";
  ck_assert_msg(strcmp(s21_strrchr("", '\0'), strrchr("", '\0')) == 0,
                "FAILURE! ");
  ck_assert_msg(strcmp(s21_strrchr(msg, '\0'), strrchr(msg, '\0')) == 0,
                "FAILURE! Test ");
  ck_assert_msg(strcmp(s21_strrchr(msg, ','), strrchr(msg, ',')) == 0,
                "FAILURE! Test ");
  ck_assert_msg(s21_strrchr(msg, 'h') == strrchr(msg, 'h'), "FAILURE! Test ");
  ck_assert_msg(strcmp(s21_strchr(msg, ' '), strchr(msg, ' ')) == 0,
                "FAILURE! Test ");
}
END_TEST

START_TEST(S21_STRSTR) {
  ck_assert_msg(strcmp(s21_strstr("abc", ""), strstr("abc", "")) == 0,
                "FAILURE! ");
  ck_assert_msg(strcmp(s21_strstr("abc", "a"), strstr("abc", "a")) == 0,
                "FAILURE! ");
  ck_assert_msg(strcmp(s21_strstr("hello", "el"), strstr("hello", "el")) == 0,
                "FAILURE! ");
  char msg[50] = "abcdef";
  ck_assert_msg(strcmp(s21_strstr(msg, "ab"), strstr(msg, "ab")) == 0,
                "FAILURE! Test ");
  ck_assert_msg(s21_strstr(msg, "1") == strstr(msg, "1"),
                "FAILURE! Test \"Hello, World!\" \'h\' failed!");
}
END_TEST

START_TEST(S21_STRTOK) {
  char str[30] = "abc cde,llf.ggg";
  char str2[30] = "abc cde,llf.ggg";
  ck_assert_int_eq(strcmp(s21_strtok(str, " .,"), strtok(str2, " .,")), 0);
  ck_assert_int_eq(strcmp(s21_strtok(NULL, " .,"), strtok(NULL, " .,")), 0);
  ck_assert_int_eq(strcmp(s21_strtok(NULL, " .,"), strtok(NULL, " .,")), 0);
  ck_assert_int_eq(strcmp(s21_strtok(NULL, " .,"), strtok(NULL, " .,")), 0);
  ck_assert_msg(s21_strtok(NULL, " .,") == strtok(NULL, " .,"), "FAILURE!");
}
END_TEST

START_TEST(S21_MEMCHR) {
  char str1[] = "abc\nabc";
  int a = 'a';
  size_t n1 = 3;
  ck_assert_ptr_eq(memchr(str1, a, n1), s21_memchr(str1, a, n1));

  char str2[] = "abcabc";
  int b = 'a';
  size_t n2 = 0;
  ck_assert_ptr_eq(memchr(str2, b, n2), s21_memchr(str2, b, n2));

  char str3[] = "abcabc";
  int c = 'a';
  size_t n3 = 0;
  ck_assert_ptr_eq(memchr(str3, c, n3), s21_memchr(str3, c, n3));

  char str4[] = "";
  int c1 = '\0';
  size_t n4 = 4;
  ck_assert_ptr_eq(memchr(str4, c1, n4), s21_memchr(str4, c1, n4));
}
END_TEST

START_TEST(S21_MEMCMP) {
  ck_assert_int_eq(s21_memcmp("", "", 0), memcmp("", "", 0));
  ck_assert_msg(s21_memcmp("", "", 0) == memcmp("", "", 0),
                "FAILURE! Test \'\' in \'\' failed!");
  ck_assert_msg(s21_memcmp("abc", "abc", 3) == memcmp("abc", "abc", 3),
                "FAILURE! Test ");
  ck_assert_msg(s21_memcmp("abcd", "abcd", 4) == memcmp("abcd", "abcd", 4),
                "FAILURE! Test ");
  ck_assert_msg(s21_memcmp("cba", "cba", 3) == memcmp("cba", "cba", 3),
                "FAILURE! Test ");
  ck_assert_msg(s21_memcmp("tall", "small", 4) == memcmp("tal", "small", 4),
                "FAILURE! ");
  ck_assert_msg(s21_memcmp("small", "tall", 4) == memcmp("small", "tall", 4),
                "FAILURE!");
  char *a = "at";
  char *b = "atb";
  int result = memcmp(a, b, 2);
  result = result > 0 ? 1 : (result == 0) ? 0 : -1;
  ck_assert_msg(s21_memcmp(a, b, 2) == result,
                "FAILURE! Test \"at\" in \"atb\" failed!");
  result = memcmp(b, a, 2);
  result = result > 0 ? 1 : (result == 0) ? 0 : -1;
  ck_assert_msg(s21_memcmp(b, a, 2) == result,
                "FAILURE! Test \"atb\" in \"at\" failed!");
}
END_TEST

START_TEST(S21_MEMCPY) {
  char dest[100];
  ck_assert_msg(
      memcmp(s21_memcpy(dest, "abc", 3), memcpy(dest, "abc", 3), 99) == 0,
      "FAILURE! Test ");
  ck_assert_msg(
      memcmp(s21_memcpy(dest, "aac", 1), memcpy(dest, "aac", 1), 99) == 0,
      "FAILURE! Test ");
  ck_assert_msg(memcmp(s21_memcpy(dest, "", 0), memcpy(dest, "", 0), 99) == 0,
                "FAILURE! Test \'\' ");
  ck_assert_msg(memcmp(s21_memcpy(dest, "11111111111", 10),
                       memcpy(dest, "11111111111", 10), 99) == 0,
                "F");
}
END_TEST

START_TEST(S21_MEMMOVE) {
  char dest[100] = "abcdef";
  char dest2[100] = "abcdef";
  ck_assert_msg(
      memcmp(s21_memmove(dest, "ba", 2), memmove(dest2, "ba", 2), 99) == 0,
      "FAILURE!");
  ck_assert_msg(memcmp(s21_memmove(dest, dest + 2, 2),
                       memmove(dest2, dest2 + 2, 2), 99) == 0,
                "FAILURE!");
  ck_assert_msg(
      memcmp(s21_memmove(dest, "", 0), memmove(dest2, "", 0), 99) == 0,
      "FAILURE! Test ");
}
END_TEST

START_TEST(S21_MEMSET) {
  char dest[100] = "abcdef";
  char dest2[100] = "abcdef";
  ck_assert_msg(
      memcmp(s21_memset(dest, 'a', 2), memset(dest2, 'a', 2), 99) == 0,
      "FAILURE! ");
  ck_assert_msg(
      memcmp(s21_memset(dest, dest[2], 6), memset(dest2, dest2[2], 6), 99) == 0,
      "FAILURE!");
  ck_assert_msg(
      memcmp(s21_memset(dest, ' ', 2), memset(dest2, ' ', 2), 99) == 0,
      "FAILURE! Test  ");
}
END_TEST

START_TEST(S21_TO_UPPER) {
  char *ptr = s21_to_upper("abcde");
  ck_assert_msg(memcmp(ptr, "ABCDE", 5) == 0,
                "FAILURE! Test \'abcdef\'  failed!");
  free(ptr);
  ptr = s21_to_upper("abcde1");
  ck_assert_msg(memcmp(ptr, "ABCDE1", 6) == 0,
                "FAILURE! Test \'abcdef\' failed!");
  free(ptr);
  ptr = s21_to_upper("!?123");
  ck_assert_msg(memcmp(ptr, "!?123", 5) == 0,
                "FAILURE! Test \'!?123\'  failed!");
  free(ptr);
  ptr = s21_to_upper(" ");
  ck_assert_msg(memcmp(ptr, " ", 1) == 0,
                "FAILURE! Test \'\' in \" \" failed!");
  free(ptr);
  ptr = s21_to_upper("!?123a");
  ck_assert_msg(memcmp(ptr, "!?123A", 6) == 0,
                "FAILURE! Test \'!?123a\' ifailed!");
  free(ptr);
}
END_TEST

START_TEST(S21_TO_LOWER) {
  char *ptr = s21_to_lower("ABCDE");
  ck_assert_msg(memcmp(ptr, "abcde", 5) == 0,
                "FAILURE! Test \'abcdef\' failed!");
  free(ptr);
  ptr = s21_to_lower("ABCDE1");
  ck_assert_msg(memcmp(ptr, "abcde1", 6) == 0,
                "FAILURE! Test \'abcdef\' failed!");
  free(ptr);
  ptr = s21_to_lower("!?123");
  ck_assert_msg(memcmp(ptr, "!?123", 5) == 0,
                "FAILURE! Test \'abcdef\'  failed!");
  free(ptr);
  ptr = s21_to_lower(" ");
  ck_assert_msg(memcmp(ptr, " ", 1) == 0, "FAILURE! Test \'abcdef\' failed!");
  free(ptr);
  ptr = s21_to_lower("!?123A");
  ck_assert_msg(memcmp(ptr, "!?123a", 6) == 0,
                "FAILURE! Test \'abcdef\' failed!");
  free(ptr);
}
END_TEST

START_TEST(S21_INSERT) {
  char *ptr = s21_insert("abc", "pp", 1);
  ck_assert_msg(memcmp(ptr, "appbc", 5) == 0, "FAILURE! Test \'abc\' failed!");
  free(ptr);
  ptr = s21_insert("abc", "pp", 0);
  ck_assert_msg(memcmp(ptr, "ppabc", 5) == 0, "FAILURE! Test \'abc\' failed!");
  free(ptr);
  ptr = s21_insert("abc", "pp", 3);
  ck_assert_msg(memcmp(ptr, "abcpp", 5) == 0, "FAILURE! Test \'abc\'  failed!");
  free(ptr);
  ptr = s21_insert("abc", "pp", 2);
  ck_assert_msg(memcmp(ptr, "abppc", 5) == 0,
                "FAILURE! Test \'abcdef\' failed!");
  free(ptr);
  ptr = s21_insert("15", "234", 1);
  ck_assert_msg(memcmp(ptr, "12345", 5) == 0, "FAILURE! Test \'15\' failed!");
  free(ptr);
  ck_assert_msg(s21_insert("15", "234", 3) == NULL,
                "FAILURE! Test \'15\' failed!");
}
END_TEST

START_TEST(S21_TRIM) {
  char *ptr = s21_trim("abc", "a");
  ck_assert_msg(memcmp(ptr, "bc", 2) == 0, "FAILURE! Test \'abc\' failed!");
  free(ptr);
  ptr = s21_trim("abacdef", "afb");
  ck_assert_msg(memcmp(ptr, "cde", 3) == 0,
                "FAILURE! Test \'abacdef\' failed!");
  free(ptr);
  ptr = s21_trim("*aaaabbbb*", "ab");
  ck_assert_msg(memcmp(ptr, "*aaaabbbb*", 5) == 0,
                "FAILURE! Test \'*aaaabbbb*\'  failed!");
  free(ptr);
  ptr = s21_trim("abc", "p");
  ck_assert_msg(memcmp(ptr, "abc", 3) == 0, "FAILURE! Test \'abcdef\' failed!");
  free(ptr);
  ptr = s21_trim("555151555", "5");
  ck_assert_msg(memcmp(ptr, "151", 3) == 0, "FAILURE! Test \'15\' failed!");
  free(ptr);
  ptr = s21_trim("555151555", "51");
  // ck_assert_msg(memcmp(ptr, "", 3) == 0 ,"FAILURE! Test \'15\' failed!");
  free(ptr);
}
END_TEST

START_TEST(S21_STRERROR) {
  char *err1 = s21_strerror(0);
  char *err2 = strerror(0);
  ck_assert_int_eq(strcmp(err1, err2), 0);
  char *err3 = s21_strerror(106);
  char *err4 = strerror(106);
  ck_assert_int_eq(strcmp(err3, err4), 0);
  char *err5 = s21_strerror(29925917);
  char *err6 = strerror(29925917);
  ck_assert_int_eq(strcmp(err5, err6), 0);
  char *err7 = s21_strerror(-29925917);
  char *err8 = strerror(-29925917);
  ck_assert_int_eq(strcmp(err7, err8), 0);
}

START_TEST(S21_SPRINTF) {
  char MESSAGE_1[500] = "Hello, World!!";
  char MESSAGE_2[500] = "Hello, World!!";

  char TEST_c = '5';
  int TEST_d = -21475;
  int TEST_i = -50000;
  double TEST_e = -544123.43214;
  double TEST_E = -542314.4231;
  double TEST_f = -50.4324;
  double TEST_g = -134323.32400;
  double TEST_G = -24324.3243000;
  int TEST_o = -775;
  char TEST_s[20] = "FLAMES";
  int TEST_u = -3857;
  int TEST_x = -9990000;
  int TEST_X = -998;
  void *TEST_p = (void *)0x999;
  int TEST_n_1 = -999;
  int TEST_n_2 = -999;
  sprintf(MESSAGE_1, "|%c|%d|%i|%e|%E|%f|%g|%G|%o|%s|%u|%x|%X|%p|%n|%%|",
          TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_1);
  s21_sprintf(MESSAGE_2, "|%c|%d|%i|%e|%E|%f|%g|%G|%o|%s|%u|%x|%X|%p|%n|%%|",
              TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
              TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_2);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #1.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #1.2 - FAILED!");

  sprintf(MESSAGE_1,
          "%-15c|%-15d|%-15i|%-15e|%-15E|%-15f|%-15g|%-15G|%-15o%-15s%-15u%-"
          "15x%-15X%-30p",
          TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p);
  s21_sprintf(MESSAGE_2,
              "%-15c|%-15d|%-15i|%-15e|%-15E|%-15f|%-15g|%-15G|%-15o%-15s%-15u%"
              "-15x%-15X%-30p",
              TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
              TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p);
  // ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, strcat(strcat(MESSAGE_1,
  // "\ntes:0: "), MESSAGE_2));
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #2.1 - FAILED!");

  sprintf(MESSAGE_1, "|%c|%+d|%+i|%+e|%+E|%+f|%+g|%+G|%o|%s|%u|%x|%X|%p|%n|%%|",
          TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_1);
  s21_sprintf(MESSAGE_2,
              "|%c|%+d|%+i|%+e|%+E|%+f|%+g|%+G|%o|%s|%u|%x|%X|%p|%n|%%|",
              TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
              TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_2);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #3.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #3.2 - FAILED!");

  sprintf(MESSAGE_1, "|%c|% d|% i|% e|% E|% f|% g|% G|%o|%s|%u|%x|%X|%p|%n|%%|",
          TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_1);
  s21_sprintf(MESSAGE_2,
              "|%c|% d|% i|% e|% E|% f|% g|% G|%o|%s|%u|%x|%X|%p|%n|%%|",
              TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
              TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_2);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #4.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #4.2 - FAILED!");

  sprintf(MESSAGE_1,
          "|%c|%d|%i|%#e|%#E|%#f|%#g|%#G|%#o|%s|%u|%#x|%#X|%p|%n|%%|", TEST_c,
          TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G, TEST_o,
          TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_1);
  s21_sprintf(MESSAGE_2,
              "|%c|%d|%i|%#e|%#E|%#f|%#g|%#G|%#o|%s|%u|%#x|%#X|%p|%n|%%|",
              TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
              TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_2);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #5.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #5.2 - FAILED!");

  sprintf(MESSAGE_1,
          "|%c|%015d|%015i|%015e|%015E|%015f|%015g|%015G|%015o|%s|%015u|%015x|%"
          "015X|%p|",
          TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p);
  s21_sprintf(MESSAGE_2,
              "|%c|%015d|%015i|%015e|%015E|%015f|%015g|%015G|%015o|%s|%015u|%"
              "015x|%015X|%p|",
              TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
              TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #6.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #6.2 - FAILED!");

  int TEST_width = 15;
  sprintf(MESSAGE_1,
          "|%15c|%15d|%15i|%15e|%15E|%15f|%15g|%15G|%15o|%15s|%15u|%15x|%15X|%"
          "30p|%n|%%|",
          TEST_c, INT_MIN, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_1);
  s21_sprintf(MESSAGE_2,
              "|%15c|%15d|%15i|%*e|%15E|%15f|%15g|%15G|%15o|%15s|%15u|%15x|%"
              "15X|%30p|%n|%%|",
              TEST_c, INT_MIN, TEST_i, TEST_width, TEST_e, TEST_E, TEST_f,
              TEST_g, TEST_G, TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p,
              &TEST_n_2);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #7.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #7.2 - FAILED!");

  int TEST_accuracy = 2;
  sprintf(MESSAGE_1,
          "|%c|%.2d|%.2i|%.2e|%.2E|%.2f|%.2g|%.2G|%.2o|%.2s|%.2u|%.2x|%.2X|%p|%"
          "n|%%|",
          TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_1);
  s21_sprintf(MESSAGE_2,
              "|%c|%.2d|%.2i|%.*e|%.2E|%.2f|%.2g|%.2G|%.2o|%.2s|%.2u|%.2x|%.2X|"
              "%p|%n|%%|",
              TEST_c, TEST_d, TEST_i, TEST_accuracy, TEST_e, TEST_E, TEST_f,
              TEST_g, TEST_G, TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p,
              &TEST_n_2);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #8.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #8.2 - FAILED!");

  sprintf(MESSAGE_1,
          "|%c|%.15d|%.15i|%.15e|%.15E|%.15f|%.15g|%.15G|%.15o|%.15s|%.15u|%."
          "15x|%.15X",
          TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_o, TEST_s, TEST_u, TEST_x, TEST_X);
  s21_sprintf(MESSAGE_2,
              "|%c|%.15d|%.15i|%.15e|%.15E|%.15f|%.15g|%.15G|%.15o|%.15s|%.15u|"
              "%.15x|%.15X",
              TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
              TEST_o, TEST_s, TEST_u, TEST_x, TEST_X);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #9.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #9.2 - FAILED!");

  sprintf(MESSAGE_1,
          "|%c|%.d|%.i|%.e|%.E|%.f|%.g|%.G|%.o|%.s|%.u|%.x|%.X|%p|%n|%%|",
          TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_1);
  s21_sprintf(MESSAGE_2,
              "|%c|%.d|%.i|%.e|%.E|%.f|%.g|%.G|%.o|%.s|%.u|%.x|%.X|%p|%n|%%|",
              TEST_c, TEST_d, TEST_i, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
              TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_2);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #10.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #10.2 - FAILED!");

  short int TEST_ii = -10000;
  short int TEST_oo = -775;
  short int TEST_uu = -3857;
  short int TEST_xx = -10900;
  short int TEST_XX = -998;
  sprintf(MESSAGE_1, "|%c|%hd|%hi|%e|%E|%f|%g|%G|%ho|%s|%hu|%hx|%hX|%p|%n|%%|",
          TEST_c, SHRT_MIN, TEST_ii, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_oo, TEST_s, TEST_uu, TEST_xx, TEST_XX, TEST_p, &TEST_n_1);
  s21_sprintf(MESSAGE_2,
              "|%c|%hd|%hi|%e|%E|%f|%g|%G|%ho|%s|%hu|%hx|%hX|%p|%n|%%|", TEST_c,
              SHRT_MIN, TEST_ii, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
              TEST_oo, TEST_s, TEST_uu, TEST_xx, TEST_XX, TEST_p, &TEST_n_2);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #11.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #11.2 - FAILED!");

  long int TEST_iii = -50000;
  long int TEST_ooo = -775;
  long int TEST_uuu = -3857;
  long int TEST_xxx = -9990000;
  long int TEST_XXX = -998;
  sprintf(MESSAGE_1, "|%c|%ld|%li|%e|%E|%f|%g|%G|%lo|%s|%lu|%lx|%lX|%p|%n|%%|",
          TEST_c, LONG_MIN, TEST_iii, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
          TEST_ooo, TEST_s, TEST_uuu, TEST_xxx, TEST_XXX, TEST_p, &TEST_n_1);
  s21_sprintf(
      MESSAGE_2, "|%c|%ld|%li|%e|%E|%f|%g|%G|%lo|%s|%lu|%lx|%lX|%p|%n|%%|",
      TEST_c, LONG_MIN, TEST_iii, TEST_e, TEST_E, TEST_f, TEST_g, TEST_G,
      TEST_ooo, TEST_s, TEST_uuu, TEST_xxx, TEST_XXX, TEST_p, &TEST_n_2);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #12.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #12.2 - FAILED!");

  long double TEST_ee = -544123.43214;
  long double TEST_EE = -542314.4231;
  long double TEST_ff = -50.4324;
  long double TEST_gg = -134323.32400;
  long double TEST_GG = -24324.3243000;
  sprintf(MESSAGE_1, "|%c|%d|%i|%Le|%LE|%Lf|%Lg|%LG|%o|%s|%u|%x|%X|%p|%n|%%|",
          TEST_c, TEST_d, TEST_i, TEST_ee, TEST_EE, TEST_ff, TEST_gg, TEST_GG,
          TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_1);
  s21_sprintf(MESSAGE_2,
              "|%c|%d|%i|%Le|%LE|%Lf|%Lg|%LG|%o|%s|%u|%x|%X|%p|%n|%%|", TEST_c,
              TEST_d, TEST_i, TEST_ee, TEST_EE, TEST_ff, TEST_gg, TEST_GG,
              TEST_o, TEST_s, TEST_u, TEST_x, TEST_X, TEST_p, &TEST_n_2);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #13.1 - FAILED!");
  ck_assert_msg(TEST_n_1 == TEST_n_2, "TEST #13.2 - FAILED!");
}
END_TEST

START_TEST(S21_SSCANF) {
  char a, b, c;  // chars
  char a1, b1, c1;
  s21_sscanf("abcdefABCDEF", "%c %*c %c %c   ", &a, &b, &c);
  sscanf("abcdefABCDEF", "%c %*c %c %c   ", &a1, &b1, &c1);
  s21_sscanf("ab", "%2c", &c);
  s21_sscanf("ab", "%2c", &c1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);

  int x, y, z = 0;  // ints
  int x1, y1, z1 = 0;
  s21_sscanf("+12 -23 .54", "%3d %d%d", &x, &y, &z);
  sscanf("+12 -23 .54", "%3d %d %d", &x1, &y1, &z1);
  ck_assert_int_eq(x, x1);
  ck_assert_int_eq(y, y1);
  ck_assert_int_eq(z, z1);

  s21_sscanf("+0775 1-0x1324--123", " %i %*i %i-  %i", &x, &y, &z);
  sscanf("+0775 1-0x1324--123", " %i %*i %i- %i", &x1, &y1, &z1);
  ck_assert_int_eq(x, x1);
  ck_assert_int_eq(y, y1);
  ck_assert_int_eq(z, z1);

  unsigned short usx, usx1;
  unsigned int ux, ux1;
  unsigned long ulx, ulx1;
  unsigned long long ullx, ullx1;
  s21_sscanf("0 +2112 -12324", "%o %lo %llo", &ux, &ulx, &ullx);
  sscanf("0 +2112 -12324", "%o %lo %llo", &ux1, &ulx1, &ullx1);
  ck_assert_int_eq(ux, ux1);
  ck_assert_int_eq(ulx, ulx1);
  ck_assert_int_eq(ullx, ullx1);

  s21_sscanf("0 0x211a 12324 0x1", "%x %lx %llx %hx", &ux, &ulx, &ullx, &usx);
  sscanf("0 0x211a 12324 0x1", "%x %lx %llx %hx", &ux1, &ulx1, &ullx1, &usx1);
  ck_assert_int_eq(usx, usx1);
  ck_assert_int_eq(ux, ux1);
  ck_assert_int_eq(ulx, ulx1);
  ck_assert_int_eq(ullx, ullx1);

  x = 0, x1 = 0;  // errors
  s21_sscanf("a21", "%d", &x);
  sscanf("a21", "%d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("a21", "b%d", &x);
  sscanf("a21", "b%d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("--a21", "%d", &x);
  sscanf("--a21", "%d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("-21", "%1d", &x);
  sscanf("-21", "%1d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("-21", "%%%1d", &x);
  sscanf("-21", "%%%1d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("-21   ", "%d %d", &x, &y);
  sscanf("-21   ", "%d %d", &x1, &y1);
  ck_assert_int_eq(x, x1);

  float fx, fx1;  // floats
  double lfx, lfx1;
  long double llfx, llfx1;
  s21_sscanf("1 2 -123232.001 .995123 999.99.1", "%*E %*G %g %le %Lf", &fx,
             &lfx, &llfx);
  sscanf("1 2 -123232.001 .995123 999.99.1", "%*E %*G %g %le %Lf", &fx1, &lfx1,
         &llfx1);
  // printf("%f %lf %Lf\n%f %lf %Lf\n", fx, lfx, llfx, fx1, lfx1, llfx1);
  ck_assert_double_eq(fx, fx1);
  ck_assert_double_eq(lfx, lfx1);
  ck_assert_double_eq(llfx, llfx1);

  char str[100], str1[100];  // strings
  char p_str[100], p_str1[100];
  s21_sscanf("abc\n\r\t%%cba\faaa?.123", "%*s %%%s%s%n", str, str1, &x);
  sscanf("abc\n\r\t%%cba\faaa?.123", "%*s %%%s%s%n", p_str, p_str1, &x1);
  ck_assert_msg(strcmp(str, p_str) == 0, "str fail");
  ck_assert_msg(strcmp(str1, p_str1) == 0, "str1 fail");
  ck_assert_int_eq(x, x1);

  void *addr1 = s21_NULL, *addr2 = s21_NULL, *addr3 = s21_NULL;
  void *paddr1 = NULL, *paddr2 = NULL, *paddr3 = NULL;
  s21_sscanf("0x1abcd -0xfffffffff +0xffffffffffffffffffaaa", "%p %n%p %p",
             &addr1, &x, &addr2, &addr3);
  sscanf("0x1abcd -0xfffffffff +0xffffffffffffffffffaaa", "%p %n%p %p", &paddr1,
         &x1, &paddr2, &paddr3);

  float af1 = 0, af2 = 0, bf1 = 0, bf2 = 0, cf1 = 0, cf2 = 0, df1 = 0, df2 = 0;

  const char strf[] =
      "nAN           INF                   -0.1111         1e-10";
  const char fstr[] = "%G %G %G %G";

  int res1 = s21_sscanf(strf, fstr, &af1, &bf1, &cf1, &df1);
  int res2 = sscanf(strf, fstr, &af2, &bf2, &cf2, &df2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(af1);
  ck_assert_float_nan(af2);
  ck_assert_ldouble_eq(bf1, bf2);
  ck_assert_ldouble_eq(cf1, cf2);
  ck_assert_ldouble_eq(df1, df2);

  const char strf2[] = "-inF InF inF INF";

  res1 = s21_sscanf(strf2, fstr, &af1, &bf1, &cf1, &df1);
  res2 = sscanf(strf2, fstr, &af2, &bf2, &cf2, &df2);
  ck_assert_ldouble_eq(bf1, bf2);
  ck_assert_ldouble_eq(cf1, cf2);
  ck_assert_ldouble_eq(df1, df2);

  long double al1 = 0, al2 = 0, bl1 = 0, bl2 = 0, cl1 = 0, cl2 = 0, dl1 = 0,
              dl2 = 0;
  const char strf3[] = "1.4441 1.31e3 -3.31e-2 0.444e-1";

  res1 = s21_sscanf(strf3, "%LG %LG %LG %LG", &al1, &bl1, &cl1, &dl1);
  res2 = sscanf(strf3, "%LG %LG %LG %LG", &al2, &bl2, &cl2, &dl2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(al1, al2);
  ck_assert_ldouble_eq(bl1, bl2);
  ck_assert_ldouble_eq(cl1, cl2);
  ck_assert_ldouble_eq(dl1, dl2);
}
END_TEST

Suite *make_s21string_suite() {
  Suite *suite = suite_create("TESTING - s21_string.h");
  TCase *group_core = tcase_create("CORE");
  // tcase_add_test(group_core, S21_STRERROR);
  tcase_add_test(group_core, S21_STRNCPY);
  tcase_add_test(group_core, S21_STRLEN);
  tcase_add_test(group_core, S21_STRCMP);
  tcase_add_test(group_core, S21_STRNCMP);
  tcase_add_test(group_core, S21_STRCAT);
  tcase_add_test(group_core, S21_STRRCHR);
  tcase_add_test(group_core, S21_STRCHR);
  tcase_add_test(group_core, S21_STRCPY);
  tcase_add_test(group_core, S21_STRSPN);
  tcase_add_test(group_core, S21_STRCSPN);
  tcase_add_test(group_core, S21_MEMCHR);
  tcase_add_test(group_core, S21_MEMCMP);
  tcase_add_test(group_core, S21_MEMCPY);
  tcase_add_test(group_core, S21_MEMMOVE);
  tcase_add_test(group_core, S21_MEMSET);
  tcase_add_test(group_core, S21_STRPBRK);
  tcase_add_test(group_core, S21_STRSTR);
  tcase_add_test(group_core, S21_TO_UPPER);
  tcase_add_test(group_core, S21_TO_LOWER);
  tcase_add_test(group_core, S21_INSERT);
  tcase_add_test(group_core, S21_TRIM);
  tcase_add_test(group_core, S21_STRTOK);
  tcase_add_test(group_core, S21_SSCANF);
  tcase_add_test(group_core, S21_SPRINTF);
  tcase_add_test(group_core, S21_STRERROR);
  suite_add_tcase(suite, group_core);
  return suite;
}

int main() {
  setlocale(LC_ALL, "Rus");

  SRunner *suite_runner = srunner_create(make_s21string_suite());
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return failed_count ? EXIT_FAILURE : EXIT_SUCCESS;
}
