add_executable(run_unit_tests ${SOURCES} catch_main.cpp matrix_test.cpp lazy_test.cpp vectors_test.cpp rational_test.cpp)
target_include_directories(run_unit_tests PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(run_unit_tests matrix)
add_test(NAME unit_tests COMMAND run_unit_tests)