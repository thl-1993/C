CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11

C_FILES = s21_*.c big_decimal.c
O_FILES = s21_*.o big_decimal.o
S21_FUNC_FILES_DIR = another_functions/*.c arithmetic_operators/*.c comparison_operators/*.c convertors_and_parsers/*.c

all: clean s21_decimal.a

clean:
		rm -rf *.o *.gch *.out *.gcno *.gcda *.info *.gcov *.a *.log
		rm -rf report/

test: s21_decimal.a
		${CC} ${FLAGS} test.c tests/test_*.c s21_decimal.a -g `pkg-config --cflags --libs check` -lm
		# ${CC} ${FLAGS} test.c s21_decimal.a -g `pkg-config --cflags --libs check` -lm
		./a.out

s21_decimal.a: s21_decimal.o
		ar rc s21_decimal.a ${O_FILES}
		ranlib s21_decimal.a
		rm *.o

gcov_report:
		${CC} -fprofile-arcs -ftest-coverage ${FLAGS} ${C_FILES} test.c tests/test_*.c ${S21_FUNC_FILES_DIR} s21_decimal.a -g `pkg-config --cflags --libs check` -lm
		./a.out
		lcov -t "coverage_report" -o coverage.info -c -d .
		genhtml -o report coverage.info
		open ./report/index.html

s21_decimal.o:
		${CC} ${FLAGS} -O -c ${C_FILES} ${S21_FUNC_FILES_DIR}

style:
		cppcheck *.h *.c
		clang-format -style=Google -n *.c *.h
		clang-format -style=Google -n tests/*.c tests/*.h

leaks:
ifeq ($(shell uname -s), Linux)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --undef-value-errors=yes ./a.out 2>valgrind.log
	grep ERROR valgrind.log > valgrind_errors.log
else
	CK_FORK=no leaks --atExit -- ./a.out
endif

install:
	sudo apt install check
	sudo apt install lcov
	sudo apt install pkg-config
	sudo apt install cppcheck
	sudo apt install valgrind
	sudo apt update

clang:
	clang-format -n -style Google *.c *.h */*.c */*.h

clang_edit:
	clang-format -i -style Google *.c *.h */*.c */*.h

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c --std=c11 *.c *.h */*.c */*.h
