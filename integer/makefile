FILES :=                              \
    .gitignore                        \
    .travis.yml                       \
    integer-tests/zjg95-RunInteger.out  \
    integer-tests/zjg95-TestInteger.c++ \
    integer-tests/zjg95-TestInteger.out \
    Integer.c++                       \
    Integer.h                         \
    Integer.log                       \
    html                              \
    RunInteger.c++                    \
    RunInteger.out                    \
    TestInteger.c++                   \
    TestInteger.out

ifeq ($(CXX), clang++)
    COVFLAGS := --coverage
    GCOV     := gcov-4.6
else
    CXX      := g++-4.8
    COVFLAGS := -fprofile-arcs -ftest-coverage
    GCOV     := gcov-4.8
endif

CXXFLAGS := -pedantic -std=c++11 -Wall
LDFLAGS  := -lgtest -lgtest_main -pthread
VALGRIND := valgrind

all: RunInteger TestInteger

check:
	@for i in $(FILES);                                         \
	do                                                          \
        [ -e $$i ] && echo "$$i found" || echo "$$i NOT FOUND"; \
    done

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunInteger
	rm -f TestInteger
	rm -f TestInteger.out

config:
	git config -l

test: RunInteger.out TestInteger.out

integer-tests:
	git clone https://github.com/cs378-summer-2015/integer-tests.git

html: Doxyfile Integer.h Integer.c++ RunInteger.c++ TestInteger.c++
	doxygen Doxyfile

Integer.log:
	git log > Integer.log

Doxyfile:
	doxygen -g

RunInteger: Integer.h Integer.c++ RunInteger.c++
	$(CXX) $(CXXFLAGS) Integer.c++ RunInteger.c++ -o RunInteger

RunInteger.out: RunInteger
	./RunInteger > RunInteger.out
	cat RunInteger.out

TestInteger: Integer.h Integer.c++ TestInteger.c++
	$(CXX) $(COVFLAGS) $(CXXFLAGS) Integer.c++ TestInteger.c++ -o TestInteger $(LDFLAGS)

TestInteger.out: TestInteger
	$(VALGRIND) ./TestInteger  >  TestInteger.out 2>&1
	$(GCOV) -b Integer.c++     >> TestInteger.out
	$(GCOV) -b TestInteger.c++ >> TestInteger.out
	cat TestInteger.out

zjg95: integer-tests TestInteger.out
	cp RunInteger.out integer-tests/zjg95-RunInteger.out
	cp TestInteger.c++ integer-tests/zjg95-TestInteger.c++
	cp TestInteger.out integer-tests/zjg95-TestInteger.out