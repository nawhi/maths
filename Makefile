
# Very simple Makefile which builds:
# matrix - an executable that runs main() from main.cpp
# test - a unit-test executable (also runs it automatically)
# test-debug - a unit-test executable with debug symbols (also runs it automatically)
# clean - remove all build files

CXX = g++
CPPFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -Werror
DEBUG = -g
EXEC = matrix
LLDB = $(shell which lldb)
GDB = $(shell which gdb)

matrix: src/matrix.cpp src/main.cpp
	mkdir -p build/
	$(CXX) $(CPPFLAGS) $(DEBUG) -o build/$(EXEC) src/main.cpp src/lu-decomp.cpp src/matrix.cpp 


test: src/matrix.cpp src/lu-decomp.cpp test/catch_main.cpp test/matrix_test.cpp
	$(CXX) $(CPPFLAGS) -o build/tests src/matrix.cpp src/lu-decomp.cpp test/catch_main.cpp test/matrix_test.cpp
	build/tests

# todo: combine this with test target somehow - too much repetition at present
test-debug: src/matrix.cpp src/lu-decomp.cpp test/catch_main.cpp test/matrix_test.cpp
	$(CXX) $(CPPFLAGS) $(DEBUG) -o build/tests src/matrix.cpp src/lu-decomp.cpp test/catch_main.cpp test/matrix_test.cpp



clean:
	rm -rf build/
