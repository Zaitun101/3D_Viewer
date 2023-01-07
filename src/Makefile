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
	open report/index.html

check:
	clang-format -n parser.c
	cppcheck --suppress=missingIncludeSystem *.c *.h

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
	@rm -rf Archive_3D_Viewer_v1.0/
	@mkdir Archive_3D_Viewer_v1.0/
	@mkdir Archive_3D_Viewer_v1.0/src
	@cp ./Viewer Archive_3D_Viewer_v1.0/src/
	@tar cvzf Archive_3D_Viewer_v1.0.tgz Archive_3D_Viewer_v1.0/
	@rm -rf Archive_3D_Viewer_v1.0/

clean:
	@rm -rf *.o *.a *.cpp mainwindow.h  mainwindow.ui *.gcda *.gcno report *.out tests test.info
