add_library(matrix main.cpp matrix.cpp lu-decomp.cpp)
target_include_directories(matrix PUBLIC ${CMAKE_SOURCE_DIR}/include)