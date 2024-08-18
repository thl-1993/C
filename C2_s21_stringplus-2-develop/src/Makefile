CC=gcc
CFLAGS=-c
LDFLAGS=  -Wall -Wextra -Werror
LIBS = -lcheck -lsubunit -lm -lrt -lpthread # For Linux.
# LIBS = -lcheck -lm -lpthread # For Mac.
SOURCES = s21_string.c s21_sprintf.c s21_sscanf.c
OBJECTS = $(SOURCES:.c=.o)
TEST_SOURCE = tests.c

all: s21_string.a test gcov_report

objects:
	$(CC) $(CFLAGS) $(LDFLAGS) s21_string.c -o s21_string.o
	$(CC) $(CFLAGS) $(LDFLAGS) s21_sprintf.c -o s21_sprintf.o
	$(CC) $(CFLAGS) $(LDFLAGS) s21_sscanf.c -o s21_sscanf.o

s21_string.a: objects
	ar rcs s21_string.a $(OBJECTS)
	ranlib $@
	rm -rf $(OBJECTS)

test: s21_string.a
	$(CC) tests.c s21_string.a $(LIBS) -o s21_tests
	./s21_tests

gcov_report:
	$(CC) --coverage $(SOURCES) $(TEST_SOURCE) -o s21_report $(LIBS)
	./s21_report
	lcov -t "123" -o s21_report.info -c -d .
	genhtml -o report s21_report.info
	open ./report/index.html

clean:
	rm -rf *.o report ../build/* *.out s21_tests s21_report* *.gc* s21_string.a s21_chat_tests *.log

rebuild: clean all

leaks:
	CK_FORK=no leaks --atExit -- ./s21_test

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c --std=c11 *.c *.h

valgrind: s21_string.a
	$(CC) tests.c s21_string.a $(LIBS) -o s21_tests
	valgrind --tool=memcheck --leak-check=yes  ./s21_tests 2> valgrind.log
	grep ERROR valgrind.log > valgrind_errors.log