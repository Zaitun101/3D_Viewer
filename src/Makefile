CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
GCOV = --coverage
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
    LIBS := -lcheck
else
    LIBS := -lcheck -lm -lsubunit
endif

all: install open

test:
	@gcc $(FLAGS) tests.c parser.c -o tests $(LIBS)
	@./tests

gcov_report:
	@gcc $(FLAGS) $(GCOV) tests.c parser.c -o tests $(LIBS)
	@./tests
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	open report/src/index.html

check:
	@cp ../materials/linters/CPPLINT.cfg .
	@python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	@cppcheck --suppress=missingIncludeSystem *.c *.h
	@CK_FORK=no leaks --atExit -- ./unit_tests	

install:
	@make clean
	@cd 3D_Viewer && qmake && make && mv Viewer ..

open:
	open Viewer

uninstall:
	@cd 3D_Viewer && make clean && rm Makefile
	@rm Viewer

dvi:
	@open dvi.md

dist:
	@rm -rf Archive_SmartCalc_v1.0/
	@mkdir Archive_SmartCalc_v1.0/
	@mkdir Archive_SmartCalc_v1.0/src
	@mv ./build_calk/restest.app Archive_SmartCalc_v1.0/src/
	@tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	@rm -rf Archive_SmartCalc_v1.0/

clean:
	@rm -rf *.o *.a *.cpp mainwindow.h  mainwindow.ui *.gcda *.gcno report *.out tests test.info
