
CPPFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -Werror
DEBUG = -g
EXEC = matrix

matrix: matrix.cpp main.cpp
	mkdir -p build/
	g++ $(CPPFLAGS) -o build/$(EXEC) main.cpp matrix.cpp 


test: matrix.cpp test/catch_main.cpp test/matrix_test.cpp
	g++ $(CPPFLAGS) -o build/tests matrix.cpp test/catch_main.cpp test/matrix_test.cpp
	build/tests
	rm build/tests

test-debug: matrix.cpp test/catch_main.cpp test/matrix_test.cpp
	g++ $(CPPFLAGS) $(DEBUG) -o build/tests matrix.cpp test/catch_main.cpp test/matrix_test.cpp
	lldb -f build/tests
	rm build/tests

clean:
	rm -rf build/