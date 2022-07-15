#include "tests_includes/s21_tests.h"

int main(void) {
    run_tests();

    return 0;
}

void run_testcase(Suite *testcase) {
    setlocale(LC_ALL, "");
    static int counter_testcase = 1;

    if (counter_testcase > 1)
        putchar('\n');
    printf("%s%d%s", "CURRENT TEST: ", counter_testcase, "\n");
    counter_testcase++;

    SRunner *sr = srunner_create(testcase);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    srunner_free(sr);
    sleep(1);
}

void run_tests(void) {
    Suite *list_cases[] = {
        suite_memcmp(), suite_insert(), suite_trim(),
        suite_sprintf(), suite_sscanf(), NULL};

    for (Suite **current_testcase = list_cases; *current_testcase != NULL;
         current_testcase++) {
        run_testcase(*current_testcase);
    }
}
