
SRC = ./src

FLAGS = -Wall -Werror -Wextra -pedantic -std=c11

FILES_c = $(SRC)/s21_string.c $(SRC)/s21_sprintf.c $(SRC)/s21_sscanf.c
FILES_o = s21_string.o s21_sprintf.o s21_sscanf.o

all: s21_string.a gcov_report test

s21_string.a: $(SRC)/s21_string.h $(FILES_c)
	gcc $(FLAGS) -c $(FILES_c)
	ar rc s21_string.a $(FILES_o)
	rm -f $(FILES_o)

test: s21_string.a $(SRC)/test.c
	gcc $(FLAGS) $(SRC)/test.c -o test -lcheck -L. s21_string.a -lm

auxTest: auxTest_1 auxTest_2 auxTest_3

auxTest_1: s21_string.a $(SRC)/AUX_TEST/AT_001.c
	gcc -Wall -Werror -Wextra -pedantic -std=c11 $(SRC)/AUX_TEST/AT_001.c -o auxTest_1 -lcheck -L. s21_string.a -lm

auxTest_2: s21_string.a $(SRC)/AUX_TEST/AT_002.c
	gcc $(SRC)/AUX_TEST/AT_002.c -o auxTest_2 -lcheck -L. s21_string.a -lm

auxTest_3: 
	gcc -fsanitize=address \
		$(SRC)/AUX_TEST/AT_003/main.c \
		$(SRC)/AUX_TEST/AT_003/test_insert.c \
		$(SRC)/AUX_TEST/AT_003/test_memcmp.c \
		$(SRC)/AUX_TEST/AT_003/test_sprintf.c \
		$(SRC)/AUX_TEST/AT_003/test_sscanf.c \
		$(SRC)/AUX_TEST/AT_003/test_trim.c \
		-o auxTest_3 -lcheck -L. s21_string.a -lm

gcov_report:
	gcc $(FLAGS) -fprofile-arcs -ftest-coverage $(FILES_c) $(SRC)/test.c -o test -lcheck
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
