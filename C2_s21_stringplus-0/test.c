#include "test.h"

START_TEST(S21_STRLEN) {
    ck_assert_msg(s21_strlen("") == strlen(""), "FAILURE! Test \"\" failed!");
    ck_assert_msg(s21_strlen("abc") == strlen("abc"), "FAILURE! Test \"abc\" failed!");
    ck_assert_msg(s21_strlen("123 ") == strlen("123 "), "FAILURE! Test \"123 \" failed!");
    ck_assert_msg(s21_strlen("l") == strlen("l"), "FAILURE! Test \"l\" failed!");
} 
END_TEST

START_TEST(S21_STRCHR) {
    char msg[50] = "Hello, World!";
    ck_assert_msg(strcmp(s21_strchr("", '\0'), strchr("", '\0')) == 0, "FAILURE! Test \"\" < \'\\0\' failed!");
    ck_assert_msg(strcmp(s21_strchr(msg, '\0'), strchr(msg, '\0')) == 0, "FAILURE! Test \"Hello, World!\" \'\\0\' failed!");
    ck_assert_msg(strcmp(s21_strchr(msg, ','), strchr(msg, ',')) == 0, "FAILURE! Test \"Hello, World!\" \',\' failed!");
    ck_assert_msg(s21_strchr(msg, 'h') == strchr(msg, 'h'), "FAILURE! Test \"Hello, World!\" \'h\' failed!");
    ck_assert_msg(strcmp(s21_strchr(msg, ' '), strchr(msg, ' ')) == 0, "FAILURE! Test \"Hello, World!\" \' \' failed!");
} 
END_TEST

START_TEST(S21_STRCAT) {
    char msg_1[50] = "";
    char msg_2[50] = "";
    ck_assert_msg(strcmp(s21_strcat(msg_1, ""), strcat(msg_2, "")) == 0, "FAILURE! Test \"\" + \"\" failed!");
    ck_assert_msg(strcmp(s21_strcat(msg_1, "Hello, "), strcat(msg_2, "Hello, ")) == 0, "FAILURE! Test \"\" + \"Hello, \" failed!");
    ck_assert_msg(strcmp(s21_strcat(msg_1, "World!"), strcat(msg_2, "World!")) == 0, "FAILURE! Test \"Hello, \" + \"World!\" failed!");
    ck_assert_msg(strcmp(s21_strcat(msg_1, ""), strcat(msg_2, "")) == 0, "FAILURE! Test \"Hello, World!\" + \"\" failed!");
}
END_TEST

START_TEST(S21_STRCMP) {
    ck_assert_msg(s21_strcmp("", "") == strcmp("", ""), "FAILURE! Test \"\" + \"\" failed!");
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
    ck_assert_msg(s21_strncmp("", "", 1) == res_norm, "FAILURE! Test \"\" + \"\" failed!");
    res_norm = strncmp("11", "1", 5) > 0 ? 1 : strncmp("11", "1", 5) < 0 ? -1 : 0; 
    ck_assert_int_eq(s21_strncmp("11", "1", 2), res_norm);
    res_norm = strncmp("1", "11", 1) > 0 ? 1 : strncmp("1", "11", 1) < 0 ? -1 : 0; 
    ck_assert_int_eq(s21_strncmp("1", "11", 1), res_norm);
    res_norm = strncmp("12", "11", 2) > 0 ? 1 : strncmp("12", "11", 2) < 0 ? -1 : 0; 
    ck_assert_int_eq(s21_strncmp("12", "11", 2), res_norm);
    res_norm = strncmp("1abcde", "1abcdf", 5) > 0 ? 1 : strncmp("1abcde", "1abcdf", 5) < 0 ? -1 : 0; 
    ck_assert_int_eq(s21_strncmp("1abcde", "1abcdf", 5), strncmp("1abcde", "1abcdf", 5));
    char c[10] = "abcde";
    char nc[10] = "ab";
    res_norm = strncmp(c, nc, 5) > 0 ? 1 : strncmp(c, nc, 5) < 0 ? -1 : 0;
    ck_assert_int_eq(s21_strncmp(c, nc, 5), res_norm);
} 
END_TEST

START_TEST(S21_STRCPY) {
    char msg_1[50] = "";
    char msg_2[50] = "";
    ck_assert_msg(strcmp(s21_strcpy(msg_1, ""), strcpy(msg_2, "")) == 0, "FAILURE! Test copy \"\" failed!");
    ck_assert_msg(strcmp(s21_strcpy(msg_1, "TEST?"), strcpy(msg_2, "TEST?")) == 0, "FAILURE! Test copy \"TEST?\" failed!");
    ck_assert_msg(strcmp(s21_strcpy(msg_1, "HAhaHA"), strcpy(msg_2, "HAhaHA")) == 0, "FAILURE! Test copy \"HAhaHA\" failed!");
    ck_assert_msg(strcmp(s21_strcpy(msg_1, ""), strcpy(msg_2, "")) == 0, "FAILURE! Test copy \"\" failed!");
}
END_TEST

START_TEST(S21_STRNCPY) {
    char msg_1[50] = "";
    char msg_2[50] = "";
    ck_assert_msg(strcmp(s21_strncpy(msg_1, "", 1), strncpy(msg_2, "", 1)) == 0, "FAILURE! Test copy \"\" - 2 failed!");
    ck_assert_msg(strcmp(s21_strncpy(msg_1, "TEST?", 6), strncpy(msg_2, "TEST?", 6)) == 0, "FAILURE! Test copy \"TEST?\" - 2 failed!");
    ck_assert_msg(strcmp(s21_strncpy(msg_1, "HAhaHA", 8), strncpy(msg_2, "HAhaHA", 8)) == 0, "FAILURE! Test copy \"HAhaHA\" - 8 failed!");
    ck_assert_msg(strcmp(s21_strncpy(msg_1, "", 2), strncpy(msg_2, "", 2)) == 0, "FAILURE! Test copy \"\" - 1 failed!");
}
END_TEST

// START_TEST(S21_STRERROR) {
//     for (int x = 200; x <= 201; x++) {
//         printf("%s\n", s21_strerror(x));
//         ck_assert_msg(strcmp(s21_strerror(x), strerror(x)) == 0, "FAILURE! Test [-1 to 51] failed!");
//     }
// } 
// END_TEST

START_TEST(S21_STRSPN) {
        ck_assert_msg(s21_strspn("", "") == strspn("" , ""), "FAILURE! Test \"\" in \"\" failed!");
        ck_assert_msg(s21_strspn("", "TEST24") == strspn("" , "TEST24"), "FAILURE! Test \"TEST24\" in \"\" failed!");
        ck_assert_msg(s21_strspn("test was success!", "TEST24") == strspn("test was success!" , "TEST24"), "FAILURE! Test \"\" in \"\" failed!");
        ck_assert_msg(s21_strspn("test was success!", "test24") == strspn("test was success!" , "test24"), "FAILURE! Test \"\" in \"\" failed!");
        ck_assert_msg(s21_strspn("test was success!", "") == strspn("test was success!" , ""), "FAILURE! Test \"\" in \"\" failed!");
} 
END_TEST

START_TEST(S21_STRCSPN) {
        ck_assert_msg(s21_strcspn("", "") == strcspn("" , ""), "FAILURE! Test \"\" in \"\" failed!");
        ck_assert_msg(s21_strcspn("", "TEST24") == strcspn("" , "TEST24"), "FAILURE! Test \"TEST24\" in \"\" failed!");
        ck_assert_msg(s21_strcspn("test was success!", "TEST24") == strcspn("test was success!" , "TEST24"), "FAILURE! Test \"\" in \"\" failed!");
        ck_assert_msg(s21_strcspn("test was success!", "test24") == strcspn("test was success!" , "test24"), "FAILURE! Test \"\" in \"\" failed!");
        ck_assert_msg(s21_strcspn("test was success!", "") == strcspn("test was success!" , ""), "FAILURE! Test \"\" in \"\" failed!");
} 
END_TEST

START_TEST(S21_STRPBRK) {
    ck_assert_int_eq(strcmp(s21_strpbrk("this is", "abs"), strpbrk("this is", "abs")), 0);
    ck_assert_int_eq(strcmp(s21_strpbrk("this is", "th"), strpbrk("this is", "th")), 0);
    ck_assert_int_eq(strcmp(s21_strpbrk("this is", "hi"), strpbrk("this is", "hi")), 0);
    ck_assert_msg(s21_strpbrk("this is", "") == strpbrk("this is", ""), "FAILURE! Test \"this is\" in \"\" failed!");
    ck_assert_msg(s21_strpbrk("this is", "dplf") == strpbrk("this is", "dplf"), "FAILURE! Test \"this is\" in \"\" failed!");
} 
END_TEST

// START_TEST(S21_STRRCHR) {
//     char msg[50] = "Hello, World!";
//     ck_assert_msg(strcmp(s21_strrchr("", '\0'), strrchr("", '\0')) == 0, "FAILURE! Test \"\" < \'\\0\' failed!");
//     ck_assert_msg(strcmp(s21_strrchr(msg, '\0'), strrchr(msg, '\0')) == 0, "FAILURE! Test \"Hello, World!\" \'\\0\' failed!");
//     ck_assert_msg(strcmp(s21_strrchr(msg, ','), strrchr(msg, ',')) == 0, "FAILURE! Test \"Hello, World!\" \',\' failed!");
//     ck_assert_msg(s21_strrchr(msg, 'h') == strrchr(msg, 'h'), "FAILURE! Test \"Hello, World!\" \'h\' failed!");
//     ck_assert_msg(strcmp(s21_strchr(msg, ' '), strchr(msg, ' ')) == 0, "FAILURE! Test \"Hello, World!\" \' \' failed!");
// }
// END_TEST

START_TEST(S21_STRSTR) {
    ck_assert_msg(strcmp(s21_strstr("abc", "a"), strstr("abc", "a")) == 0, "FAILURE! Test \"\" < \'\\0\' failed!");
    ck_assert_msg(strcmp(s21_strstr("hello", "el"), strstr("hello", "el")) == 0, "FAILURE! Test \"Hello, World!\" \'\\0\' failed!");
    char msg[50] = "abcdef";
    ck_assert_msg(strcmp(s21_strstr(msg, "ab"), strstr(msg, "ab")) == 0, "FAILURE! Test \"Hello, World!\" \',\' failed!");
    ck_assert_msg(s21_strstr(msg, "1") == strstr(msg, "1"), "FAILURE! Test \"Hello, World!\" \'h\' failed!");
    //ck_assert_msg(strcmp(s21_strstr(msg, " "), strstr(msg, " ")) == 0, "FAILURE! Test \"Hello, World!\" \' \' failed!");
}
END_TEST

START_TEST(S21_STRTOK) {
    char str[30] = "abc cde,llf.ggg";
    char str2[30] = "abc cde,llf.ggg";
    // char *ptr = strtok(str, " .,");
    // char *ptr2 = s21_strtok(str2, " .,");
    ck_assert_int_eq(strcmp(s21_strtok(str, " .,"), strtok(str2, " .,")), 0);
    ck_assert_int_eq(strcmp(s21_strtok(NULL, " .,"), strtok(NULL, " .,")), 0);
    ck_assert_int_eq(strcmp(s21_strtok(NULL, " .,"), strtok(NULL, " .,")), 0);
    ck_assert_int_eq(strcmp(s21_strtok(NULL, " .,"), strtok(NULL, " .,")), 0);
    ck_assert_msg(s21_strtok(NULL, " .,") == strtok(NULL, " .,"), "FAILURE! Test \'str\' in \'NULL\' failed!");
}
END_TEST

START_TEST(S21_MEMCHR) {
    ck_assert_msg(s21_memchr("", 'a', 1) == memchr("", 'a', 1), "FAILURE! Test \'\' in \'a\' failed!");
    ck_assert_msg(s21_memchr("abc", 'b', 1) == memchr("abc" , 'b', 1), "FAILURE! Test \"abc\" in \"b\" failed!");
    ck_assert_msg(memcmp(s21_memchr("tttabb", 'a', 10), memchr("tttabb", 'a', 10), 1) == 0, "FAILURE! Test \"tttab\" in \"a\" failed!");
    ck_assert_msg(s21_memchr("tttab", 'l', 10) == memchr("tttab", 'l', 10), "FAILURE! Test \"tttab\" in \"l\" failed!");
}
END_TEST

START_TEST(S21_MEMCMP) {
    ck_assert_int_eq(s21_memcmp("", "", 1), memcmp("", "", 1));
    ck_assert_msg(s21_memcmp("", "", 1) == memcmp("", "", 1), "FAILURE! Test \'\' in \'\' failed!");
    ck_assert_msg(s21_memcmp("abc", "abc", 3) == memcmp("cba", "cba", 3), "FAILURE! Test \"abc\" in \"abc\" failed!");
    ck_assert_msg(s21_memcmp("cba", "cba", 10) == memcmp("cba", "cba", 10), "FAILURE! Test \"cba\" in \"cba\" failed!");
    ck_assert_msg(s21_memcmp("tall", "small", 10) == memcmp("tal", "small", 10), "FAILURE! Test \"tall\" in \"small\" failed!");
    ck_assert_msg(s21_memcmp("small", "tall", 10) == memcmp("small", "tall", 10), "FAILURE! Test \"small\" in \"tall\" failed!");
    char *a = "at";
    char *b = "atb";
    int result = memcmp(a, b, 10);
    result = result > 0 ? 1 : (result == 0) ? 0 : -1;
    ck_assert_msg(s21_memcmp(a, b, 10) == result, "FAILURE! Test \"at\" in \"atb\" failed!");
    result = memcmp(b, a, 10);
    result = result > 0 ? 1 : (result == 0) ? 0 : -1;
    ck_assert_msg(s21_memcmp(b, a, 10) == result, "FAILURE! Test \"atb\" in \"at\" failed!");
}
END_TEST

START_TEST(S21_MEMCPY) {
    char dest[100];
    ck_assert_msg(memcmp(s21_memcpy(dest, "abc", 3), memcpy(dest, "abc", 3), 99) == 0, "FAILURE! Test \'\' in \"abc\" failed!");
    ck_assert_msg(memcmp(s21_memcpy(dest, "aac", 1), memcpy(dest , "aac", 1), 99) == 0, "FAILURE! Test \"\" in \"aac\" failed!");
    ck_assert_msg(memcmp(s21_memcpy(dest, "", 0), memcpy(dest, "", 0), 99) == 0, "FAILURE! Test \'\' in \'\' failed!");
    ck_assert_msg(memcmp(s21_memcpy(dest, "11111111111", 10), memcpy(dest, "11111111111", 10), 99) == 0, "FAILURE! Test \"\" in \"111111111\" failed!");

}
END_TEST

START_TEST(S21_MEMMOVE) {
    char dest[100] = "abcdef";
    char dest2[100] = "abcdef";
    ck_assert_msg(memcmp(s21_memmove(dest, "ba", 2), memmove(dest2, "ba", 2), 99) == 0 ,"FAILURE! Test \'abcdef\' in \"ba\" failed!");
    ck_assert_msg(memcmp(s21_memmove(dest, dest + 2, 2), memmove(dest2, dest2 + 2, 2), 99) == 0 ,"FAILURE! Test \'abcdef\' in \"cd\" failed!");
    ck_assert_msg(memcmp(s21_memmove(dest, "", 0), memmove(dest2, "", 0), 99) == 0 ,"FAILURE! Test \'abcdef\' in \"\" failed!");

}
END_TEST

START_TEST(S21_MEMSET) {
    char dest[100] = "abcdef";
    char dest2[100] = "abcdef";
    ck_assert_msg(memcmp(s21_memset(dest, 'a', 2), memset(dest2, 'a', 2), 99) == 0 ,"FAILURE! Test \'abcdef\' in \"a\" failed!");
    ck_assert_msg(memcmp(s21_memset(dest, dest[2], 6), memset(dest2, dest2[2], 6), 99) == 0 ,"FAILURE! Test \'abcdef\' in \"c\" failed!");
    ck_assert_msg(memcmp(s21_memset(dest, ' ', 2), memset(dest2, ' ', 2), 99) == 0 ,"FAILURE! Test \'abcdef\' in \" \" failed!");
}
END_TEST

START_TEST(S21_TO_UPPER) {
    char *ptr = s21_to_upper("abcde");
    ck_assert_msg(memcmp(ptr, "ABCDE", 5) == 0 ,"FAILURE! Test \'abcdef\'  failed!");
    free(ptr);
    ptr = s21_to_upper("abcde1");
    ck_assert_msg(memcmp(ptr, "ABCDE1", 6) == 0 ,"FAILURE! Test \'abcdef\' failed!");
    free(ptr);
    ptr = s21_to_upper("!?123");
    ck_assert_msg(memcmp(ptr, "!?123", 5) == 0 ,"FAILURE! Test \'!?123\'  failed!");
    free(ptr);
    ptr = s21_to_upper(" ");
    ck_assert_msg(memcmp(ptr, " ", 1) == 0 ,"FAILURE! Test \'\' in \" \" failed!");
    free(ptr);
    ptr = s21_to_upper("!?123a");
    ck_assert_msg(memcmp(ptr, "!?123A", 6) == 0 ,"FAILURE! Test \'!?123a\' ifailed!");
    free(ptr);
}
END_TEST

START_TEST(S21_TO_LOWER) {
    char *ptr = s21_to_lower("ABCDE");
    ck_assert_msg(memcmp(ptr, "abcde", 5) == 0 ,"FAILURE! Test \'abcdef\' failed!");
    free(ptr);
    ptr = s21_to_lower("ABCDE1");
    ck_assert_msg(memcmp(ptr, "abcde1", 6) == 0 ,"FAILURE! Test \'abcdef\' failed!");
    free(ptr);
    ptr = s21_to_lower("!?123");
    ck_assert_msg(memcmp(ptr, "!?123", 5) == 0 ,"FAILURE! Test \'abcdef\'  failed!");
    free(ptr);
    ptr = s21_to_lower(" ");
    ck_assert_msg(memcmp(ptr, " ", 1) == 0 ,"FAILURE! Test \'abcdef\' failed!");
    free(ptr);
    ptr = s21_to_lower("!?123A");
    ck_assert_msg(memcmp(ptr, "!?123a", 6) == 0 ,"FAILURE! Test \'abcdef\' failed!");
    free(ptr);
}
END_TEST

START_TEST(S21_INSERT) {
    char *ptr = s21_insert("abc", "pp", 1);
    ck_assert_msg(memcmp(ptr, "appbc", 5) == 0 ,"FAILURE! Test \'abc\' failed!");
    free(ptr);
    ptr = s21_insert("abc", "pp", 0);
    ck_assert_msg(memcmp(ptr, "ppabc", 5) == 0 ,"FAILURE! Test \'abc\' failed!");
    free(ptr);
    ptr = s21_insert("abc", "pp", 3);
    ck_assert_msg(memcmp(ptr, "abcpp", 5) == 0 ,"FAILURE! Test \'abc\'  failed!");
    free(ptr);
    ptr = s21_insert("abc", "pp", 2);
    ck_assert_msg(memcmp(ptr, "abppc", 5) == 0 ,"FAILURE! Test \'abcdef\' failed!");
    free(ptr);
    ptr = s21_insert("15", "234", 1);
    ck_assert_msg(memcmp(ptr, "12345", 5) == 0 ,"FAILURE! Test \'15\' failed!");
    free(ptr);
    ck_assert_msg(s21_insert("15", "234", 3) == NULL ,"FAILURE! Test \'15\' failed!");
}
END_TEST

START_TEST(S21_TRIM) {
    char *ptr = s21_trim("abc", "a");
    ck_assert_msg(memcmp(ptr, "bc", 2) == 0 ,"FAILURE! Test \'abc\' failed!");
    free(ptr);
    ptr = s21_trim("abacdef", "afb");
    ck_assert_msg(memcmp(ptr, "cde", 3) == 0 ,"FAILURE! Test \'abacdef\' failed!");
    free(ptr);
    ptr = s21_trim("*aaaabbbb*", "ab");
    ck_assert_msg(memcmp(ptr, "*aaaabbbb*", 5) == 0 ,"FAILURE! Test \'*aaaabbbb*\'  failed!");
    free(ptr);
    ptr = s21_trim("abc", "p");
    ck_assert_msg(memcmp(ptr, "abc", 3) == 0 ,"FAILURE! Test \'abcdef\' failed!");
    free(ptr);
    ptr = s21_trim("555151555", "5");
    ck_assert_msg(memcmp(ptr, "151", 3) == 0 ,"FAILURE! Test \'15\' failed!");
    free(ptr);
    ptr = s21_trim("555151555", "51");
    // ck_assert_msg(memcmp(ptr, "", 3) == 0 ,"FAILURE! Test \'15\' failed!");
    free(ptr);
}
END_TEST


Suite * make_s21string_suite() {
    Suite * suite = suite_create("TESTING - s21_string.h");
    TCase * group_core = tcase_create("CORE");
    // tcase_add_test(group_core, S21_STRERROR);
    tcase_add_test(group_core, S21_STRNCPY);
    tcase_add_test(group_core, S21_STRLEN);
    tcase_add_test(group_core, S21_STRCMP);
    tcase_add_test(group_core, S21_STRNCMP);
    tcase_add_test(group_core, S21_STRCAT);
    // tcase_add_test(group_core, S21_STRRCHR);
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
    suite_add_tcase(suite, group_core);
    return suite;
}

int main() {
    SRunner * suite_runner = srunner_create(make_s21string_suite());
    srunner_run_all(suite_runner, CK_NORMAL);
    int failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
