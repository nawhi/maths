add_library(matrix main.cpp lu-decomp.cpp lazy.cpp)
target_include_directories(matrix PUBLIC ${CMAKE_SOURCE_DIR}/include)