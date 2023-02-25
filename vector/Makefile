G = gcc -lstdc++
GCC = $(G) -Wall -Wextra -Werror -Wuninitialized
TEST_LIBS = -lgtest

all: test

test: clean
	$(GCC) $(TEST_LIBS) test.cc -o test
	./test
#./test --gtest_repeat=10 --gtest_break_on_failure

clean:
	rm -rf a.out test