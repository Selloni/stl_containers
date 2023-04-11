G = gcc -lstdc++
GCC = $(G) -Wall -Wextra -Werror -Wuninitialized
TEST_LIBS = -lgtest -lgmock -pthread
FLAG_LEAKS = -lgtest -lstdc++ -lpthread -std=c++17 -g -lcheck
#OS= $(shell uname -s)
#
#ifeq ($(OS),Linux)
#	LIBS += -lsubunit -lrt -lpthread -lm
#endif



all: test

build:
	$(GCC) main.cc s21_vector.cc

test: clean
	$(GCC) $(TEST_LIBS) test_vector.cc -o test
	./test
#./test --gtest_repeat=10 --gtest_break_on_failure

leaks:
	$(GCC) $(FLAG_LEAKS) test_vector.cc -o vector_gtest
	CK_FORK=no leaks --atExit -- ./vector_gtest

clean:
	rm -rf a.out test *.gcdo *.gcno vector_gtest report *info *gcda *dSYM

gcov_report:
	$(GCC) --coverage test_vector.cc -o test $(LIBS)
	./test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

vg: test
    	CK_FORK=no valgrind --tool=memcheck ./test