


all: s21_string.a gcov_report test

s21_string.a: s21_string.h s21_string.c s21_sprintf.c s21_sscanf.c
	gcc -Wall -Werror -Wextra -pedantic -std=c11 -c s21_string.c s21_sprintf.c s21_sscanf.c
	ar rc s21_string.a s21_string.o s21_sscanf.o s21_sprintf.o
	rm -f s21_string.o s21_sscanf.o s21_sprintf.o

main: s21_string.a main.c
	gcc -Wall -Wextra -pedantic -std=c11 main.c -o test -lcheck -L. s21_string.a -lm

test: s21_string.a test.c
	gcc -Wall -Werror -Wextra -pedantic -std=c11 test.c -o test -lcheck -L. s21_string.a -lm

gcov_report:
	gcc -Wall -Werror -Wextra -fprofile-arcs -ftest-coverage s21_string.c s21_sprintf.c s21_sscanf.c test.c -o test -lcheck
	./test
	lcov -t "s21_sprintf" -o s21_sprintf.info -c -d .
	lcov -t "s21_string" -o s21_string.info -c -d .
	lcov -t "s21_sscanf" -o s21_sscanf.info -c -d .
	genhtml -o gcov_report s21_string.info s21_sscanf.info
	rm -f *.gcda *.gcno *.info test

rebuild:
	make clean
	make all

clean:
	rm -f s21_string.a test
	rm -rf gcov_report
