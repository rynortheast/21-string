
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -fsanitize=address -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage

HEADERS = s21_string.h
SOURCES = $(wildcard ./CORE/*.c)

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES))

%.o: %.c $(HEADER)
	gcc $(CFLAGS) -c $< -o $@

all: s21_string.a gcov_report test

s21_string.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_string.a $(OBJ_LIBRARY)
	ranlib s21_string.a
	rm -rf ./*/*.o

test: s21_string.a TESTS/SUITE_main.c
	gcc $(CFLAGS) TESTS/SUITE_main.c s21_string.a -o test.out -lm -lcheck
	./test.out

personal: s21_string.a TESTS/personal.c
	gcc $(CFLAGS) TESTS/personal.c s21_string.a -o test.out -lm
	./personal.out

test_1: s21_string.a TESTS/SUITE_aux__1.c
	gcc $(CFLAGS) TESTS/SUITE_aux__1.c s21_string.a -o test.out -lm -lcheck
	./test_1.out

test_2: s21_string.a TESTS/SUITE_aux__2.c
	gcc $(CFLAGS) TESTS/SUITE_aux__2.c s21_string.a -o test.out -lm -lcheck
	./test_2.out

test_3: s21_string.a TESTS/SUITE_aux__3.c
	gcc $(CFLAGS) TESTS/SUITE_aux__3.c s21_string.a -o test.out -lm -lcheck
	./test_3.out

gcov_report: s21_string.a TESTS/SUITE_main.c
	gcc $(GCOVFLAGS) TESTS/SUITE_main.c $(SOURCES) -o report.out -lm -lcheck
	./report.out
	gcov -f $(SOURCES)
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html

check:
	clang-format -style=Google -n ./*/*.c

rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report
