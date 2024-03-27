CC= g++
CFLAG= -Wall -Werror -Wextra -std=c++17 -g

TESTFLAG= -lgtest -lgmock -pthread

all: s21_matrix_oop.a

rebuild: clean s21_matrix_oop.a

s21_matrix_oop.a: s21_constructors.o s21_member_functions.o s21_operators.o s21_getters_setters.o
	ar rcs $@ $^
	rm -rf $^

s21_constructors.o: s21_constructors.cc
	$(CC) $(CFLAG) $(COVER) -c $^ -o $@

s21_member_functions.o: s21_member_functions.cc
	$(CC) $(CFLAG) $(COVER) -c $^ -o $@

s21_operators.o: s21_operators.cc
	$(CC) $(CFLAG) $(COVER) -c $^ -o $@

s21_getters_setters.o: s21_getters_setters.cc
	$(CC) $(CFLAG) $(COVER) -c $^ -o $@	

test: rebuild tests
	rm -rf *.test *.dSYM

test_matrix:
	$(CC) $(CFLAG) $(COVER) test.cc s21_matrix_oop.a -o $@.test $(TESTFLAG)
	./$@.test || true

tests: test_matrix

test_gcov: coverlib covertest

coverlib: COVER= -fprofile-arcs -ftest-coverage
coverlib: rebuild
covertest: COVER= -fprofile-arcs
covertest: test

gcov_report: test_gcov
	lcov -c -d ./ -o test.info
	lcov -e test.info -o test.info "`pwd`/*"
	lcov -r test.info -o test.info "`pwd`/tests/*"
	genhtml -o ./report test.info
	open ./report/index.html
	rm -rf *.gcda *gcno test.info *.dSYM

test_gcov: COVER=--coverage -fno-default-inline -fno-elide-constructors# Two last flags fix bug with unchecked closing bracket
test_gcov: rebuild test

paola: rebuild
	$(CC) -Wall -g paola.cc s21_matrix_oop.a -o $@
	./$@
	rm -rf paola

clean:
	rm -rf *.o *.a test.info s21_test *.gcda *gcno report *.gcov

style: 
	cp ../materials/linters/.clang-format ./
	clang-format -i -style=file *.cc *.h
	rm -rf .clang-format

