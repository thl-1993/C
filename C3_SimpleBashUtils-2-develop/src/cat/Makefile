GCC = gcc -Wall -Wextra -Werror

TARGET = s21_cat

all: clang cppcheck clean default
	
default: $(TARGET)

$(TARGET):
	$(GCC) $(TARGET).c -o $(TARGET)

clean:
	rm -rf *.o *.out $(TARGET) .clang-format

clang:
	cp ../../materials/linters/.clang-format .
	clang-format -i *.c *.h
	clang-format -n *.c *.h

cppcheck:
	cppcheck --suppress=missingIncludeSystem --enable=all --language=c --std=c11 *.c *.h cat/*.c cat/*.h grep/*.c grep/*.h

valgrind:
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(TARGET)
