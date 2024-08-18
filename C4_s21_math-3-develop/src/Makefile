PROJECT_NAME= s21_math
FLAGS= -Wall -Wextra -Werror

all: $(PROJECT_NAME).a

$(PROJECT_NAME).a: clean
	gcc -c $(FLAGS) $(PROJECT_NAME).c -o $(PROJECT_NAME).o
	ar rc $(PROJECT_NAME).a $(PROJECT_NAME).o
	ranlib $(PROJECT_NAME).a

test: $(PROJECT_NAME).a
	checkmk $(PROJECT_NAME).check > $(PROJECT_NAME)_test.c
	gcc $(FLAGS) $(PROJECT_NAME)_test.c $(PROJECT_NAME).a  -o s21_test -g `pkg-config --cflags --libs check` -lm
	./s21_test

peer_test: $(PROJECT_NAME).a
	gcc $(FLAGS) -c test.c -g `pkg-config --cflags --libs check` -lm
	gcc $(FLAGS) test.o -L. $(PROJECT_NAME).a -o peer_test -g `pkg-config --cflags --libs check` -lm

gcov_report:
	checkmk $(PROJECT_NAME).check > $(PROJECT_NAME)_test.c
	gcc -c $(FLAGS) $(PROJECT_NAME)_test.c -o $(PROJECT_NAME)_test.o -g `pkg-config --cflags --libs check` -lm
	gcc $(FLAGS) --coverage $(PROJECT_NAME)_test.o $(PROJECT_NAME).c  -o s21_test -g `pkg-config --cflags --libs check` -lm
	./s21_test
	lcov -d ./ --capture --output-file s21_test.info
	genhtml s21_test.info --output-directory report
	open report/index.html

style: 
	clang-format -style=Google -n *.c *.h

clean:
	rm -rf *.o *.a *.out s21_test $(PROJECT_NAME)_test.c *.gcda *.gcno report *.info peer_test

clang:
	clang-format -i -style Google *.c *.h

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c --std=c11 s21_math.c test.c s21_math.h