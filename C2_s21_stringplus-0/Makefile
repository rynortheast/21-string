all: s21_string.a gcov_report test

s21_string.a: s21_string.c
	gcc -Wall -Werror -Wextra -c s21_string.c
	ar r s21_string.a s21_string.o
	rm -f s21_string.o

test: s21_string.h test.h s21_string.c test.c
	gcc -Wall -Werror -Wextra s21_string.c test.c -o test -lcheck 

gcov_report:
	gcc -Wall -Werror -Wextra -fprofile-arcs -ftest-coverage s21_string.c test.c -o test -lcheck
	./test
	lcov -t "s21_string" -o s21_string.info -c -d . 
	genhtml -o gcov_report s21_string.info
	rm -f test-s21_string.gcda test-s21_string.gcno test-test.gcda test-test.gcno s21_string.info test

rebuild:
	make clean
	make all

clean:
	rm -f s21_string.a test
	rm -rf gcov_report
	rm *.gcda *.gcno
