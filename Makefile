CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11

all: test

s21_decimal.a:
	$(CC) $(FLAGS) -c comparison/*.c --coverage
#	$(CC) $(FLAGS) -c another/*.c --coverage
#	$(CC) $(FLAGS) -c arithmetic/*.c --coverage
#	$(CC) $(FLAGS) -c convertors/*.c --coverage
	$(CC) $(FLAGS) -c extra.c
	ar rc s21_decimal.a *.o

main: s21_decimal.a
	$(CC) $(FLAGS) main.c s21_decimal.a
	./a.out

test: 
	$(CC) $(FLAGS) -c comparison/*.c --coverage
#	$(CC) $(FLAGS) -c another/*.c --coverage
#	$(CC) $(FLAGS) -c arithmetic/*.c --coverage
#	$(CC) $(FLAGS) -c convertors/*.c --coverage
	$(CC) $(FLAGS) -c extra.c tests/*.c
	$(CC) $(FLAGS) -o s21_test *.o -lcheck --coverage
	./s21_test

gcov_report: test
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o coverage-html
	open coverage-html/index.html

clean: 
	rm -rf *.o s21_test *.gcda *.gcno coverage-html coverage.info s21_math.a

rebuld: clean all