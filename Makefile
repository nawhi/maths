
CPPFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -Werror
EXEC = matrix

matrix: matrix.cpp main.cpp
	mkdir -p build/
	g++ $(CPPFLAGS) -o build/$(EXEC) main.cpp matrix.cpp 

clean: 
	rm -rf build/