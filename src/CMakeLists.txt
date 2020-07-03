add_library(matrix main.cpp lu-decomp.cpp ../include/vectors_test.h)
target_include_directories(matrix PUBLIC ${CMAKE_SOURCE_DIR}/include)