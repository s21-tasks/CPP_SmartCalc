CC=g++
SRC=Model/Model.cc Controller/Controller.cc
SRC_T=test/calculation_tests.cc
CFLAGS= -g -Wall -Werror -Wextra -std=c++17 
TESTFLAGS=-lgtest -lgtest_main --coverage

all: gcov_report run

install:
	@mkdir -p Sborka
	@cd ./Sborka; cmake ../Build/CMakeLists.txt; make

run: install
	@./Sborka/calc_view.app/Contents/MacOS/calc_view

uninstall:
	@rm -rf Sborka	

tests:
	@$(CC) $(CFLAGS) $(TESTFLAGS) $(SRC) $(SRC_T) -o test.out
	@./test.out


gcov_report: tests
	@lcov -t "test" -o test.info -c -d . --no-external
	@genhtml -o report test.info
	@open report/index.html

clean:
	@rm -rf *.out *.o s21_matrix_oop.a *.gcda *.gcno *.info 
	@rm -rf report
	@rm -rf test.out.dSYM

leaks: tests
	leaks --atExit -- ./test.out

clang:
	clang-format -i *.cc *.h
	clang-format -n *.cc *.h

dvi:
	open ../README_RUS.md
	
dist:
	tar -cvf archive.tar ../src
