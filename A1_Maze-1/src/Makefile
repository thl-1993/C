.PHONY: maze 
PROJECT = A1_MAZE
GCC = gcc -std=c11 -Wall -Werror -Wextra
GFLAGS = -fprofile-arcs -ftest-coverage
TFLAGS = -g `pkg-config --cflags --libs check` -lm
NFLAGS = -lncurses

BASIC_FILES = \
	struct/*.* \
	interface/*.* \
	maze/*.* \
	cave/*.* \
	tests/*.*

.PHONY: tests maze 

# basic goals
all:

install:

uninstall:

clean:
	rm -fr build/* libs/* logs/* a.out *.txt maze/*.txt

run_maze: style maze 
	${GCC} maze/run_maze.c libs/* \
	${TFLAGS} \
	${NFLAGS} \
	-o build/test.o
	./build/test.o

.PHONY: test

test: style maze 
	${GCC} ${GFLAGS} -o build/maze_test.o -c maze/maze_test.c
	${GCC} ${GFLAGS} build/maze_test.o libs/maze.a \
	${TFLAGS} \
	${NFLAGS} \
	-o build/test
	./build/test

# auxiliary goals
gcov_report: style test
	lcov --capture --directory . --output-file build/coverage.info
	genhtml build/coverage.info --output-directory build/coverage
	sudo xdg-open build/coverage/index.html 

maze: style
	${GCC} -c $@/$@.c -o build/$@.o
	ar rc libs/$@.a build/$@.o
	ranlib libs/$@.a

.PHONY: leaks valgrind

leaks: test
	leaks -atExit -- ./build/test

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-report.txt ./build/test

style:
	clang-format -style=Google -i maze/*.c maze/*.h