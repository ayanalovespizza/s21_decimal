CC = gcc
FLAGS =  -std=c11

all: test

s21_decimal.a:
	$(CC) $(FLAGS) -c comparison/s21_is_equal.c
#	$(CC) $(FLAGS) -c another/negate.c
#	$(CC) $(FLAGS) -c another/*.c
	$(CC) $(FLAGS) -c arithmetic/*.c
	$(CC) $(FLAGS) -c convertors/*.c
	$(CC) $(FLAGS) -c extra.c
	$(CC) $(FLAGS) -c get_and_set_functions/*.c
	ar rc s21_decimal.a *.o

main: s21_decimal.a
	$(CC) $(FLAGS) main.c s21_decimal.a
	./a.out

test: clean
	$(CC) $(FLAGS) -c comparison/s21_is_equal.c --coverage
#	$(CC) $(FLAGS) -c another/negate.c --coverage
#	$(CC) $(FLAGS) -c another/*.c --coverage
	$(CC) $(FLAGS) -c arithmetic/s21_add.c arithmetic/s21_sub.c get_and_set_functions/*.c --coverage
#	$(CC) $(FLAGS) -c convertors/*.c --coverage
	$(CC) $(FLAGS) -c extra.c tests/add_tests.c tests/sub_tests.c tests/run_tests.c 
	$(CC) $(FLAGS) -o s21_test *.o -lcheck --coverage
	./s21_test

gcov_report: test
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o coverage-html
	open coverage-html/index.html

clean: 
	rm -rf *.o s21_test *.gcda *.gcno coverage-html coverage.info s21_decimal.a a.out

rebuld: clean all