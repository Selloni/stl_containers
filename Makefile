G = gcc
GCC = ($G) -std=c++17 -Wall -Werror -Wextra
TESTFLAG = g++ -lgtest -lgmock -pthread
SRC = vector/s21_vector.cc


test:
	$(TESTFLAG) $(SRC) vector/test.cc -o test



leaks:
leaks -atExit -- ./s21_containers.out | grep LEAK:
