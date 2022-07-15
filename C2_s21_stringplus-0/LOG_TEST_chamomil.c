
./AUX_TEST/ALL/test_sprintf.c:759:F:sprintf_tc:null_ptr:0: Assertion 's21_sprintf(str1, format, ptr) == sprintf(str2, format, ptr)' failed: s21_sprintf(str1, format, ptr) == 3, sprintf(str2, format, ptr) == 5
./AUX_TEST/ALL/test_sprintf.c:2190:F:sprintf_tc:wide_char:0: Assertion 'str1 == str2' failed: str1 == "This is a simple wide char �", str2 == "This is a simple wide char 汉"
./AUX_TEST/ALL/test_sprintf.c:2213:F:sprintf_tc:minus_wide_char:0: Assertion 'str1 == str2' failed: str1 == "This is a simple wide char �    ", str2 == "This is a simple wide char 森  "
