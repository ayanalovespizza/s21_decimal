CC = gcc
FLAGS =  -std=c11

all: test

s21_decimal.a:
#	$(CC) $(FLAGS) -c comparison/*.c
#	$(CC) $(FLAGS) -c another/negate.c
	$(CC) $(FLAGS) -c another/truncate.c
	$(CC) $(FLAGS) -c another/floor.c
	$(CC) $(FLAGS) -c convertors/*.c
	$(CC) $(FLAGS) -c extra.c
	ar rc s21_decimal.a *.o

main: s21_decimal.a
	$(CC) $(FLAGS)  s21_decimal.a
	./a.out

test: clean
	 $(CC) $(FLAGS) -c convertors/*.c  another/truncate.c  another/floor.c  extra.c  tests/*.c comparison/is_equal.c --coverage
	$(CC) $(FLAGS) -o s21_test *.o -lcheck --coverage
	./s21_test

gcov_report: test
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o coverage-html
	open coverage-html/index.html

clean: 
	rm -rf *.o s21_test *.gcda *.gcno coverage-html coverage.info s21_decimal.a a.out

rebuld: clean all