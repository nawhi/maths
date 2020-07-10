add_executable(run_unit_tests test_main.cpp test_matrix_old.cpp test_lazy.cpp test_vector.cpp test_fraction.cpp test_matrix.cpp)
target_include_directories(run_unit_tests PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party)
target_link_libraries(run_unit_tests matrix)
add_test(NAME unit_tests COMMAND run_unit_tests)