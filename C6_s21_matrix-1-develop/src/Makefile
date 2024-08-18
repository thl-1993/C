.PHONY: all clean test s21_matrix.a check gcov_report valgrind_check

CC = gcc
FLAGS = -std=c11 -Wall -Werror -Wextra 

C_FILES = s21_matrix.c 
O_FILES = s21_*.o
T_FILES = test.c tests/test_*.c
H_FILES = *.h tests/*.h

all: clean s21_matrix.a

clean:
	rm -rf *.o *.gch *.out *.gcno *.gcda *.info *.gcov *.a *.log
	rm -rf report/

test: s21_matrix.a
	${CC} ${FLAGS} ${T_FILES} s21_matrix.a -g `pkg-config --cflags --libs check` -lm
	./a.out

test1: s21_matrix.a
	${CC} ${FLAGS} tests.c s21_matrix.a -g `pkg-config --cflags --libs check` -lm
	./a.out
	

s21_matrix.a: s21_matrix.o
	ar rc s21_matrix.a ${O_FILES}
	ranlib s21_matrix.a
	rm *.o

s21_matrix.o:
	${CC} ${FLAGS} -O -c ${C_FILES}

gcov_report:
	${CC} -fprofile-arcs -ftest-coverage ${FLAGS} ${C_FILES} ${T_FILES} s21_matrix.a -g `pkg-config --cflags --libs check` -lm
	./a.out
	lcov -t "coverage_report" -o coverage.info -c -d .
	genhtml -o report coverage.info
	open ./report/index.html

clang:
	clang-format -n -style Google ${H_FILES} ${C_FILES} ${T_FILES}

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c --std=c11 $(C_FILES) $(T_FILES) *.h tests/*.h

leaks:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --undef-value-errors=yes ./a.out 2>valgrind.log
	grep ERROR valgrind.log > valgrind_errors.log
