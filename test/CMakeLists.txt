add_executable(run_unit_tests ${SOURCES} test_main.cpp test_matrix.cpp test_lazy.cpp test_vectors.cpp test_fraction.cpp)
target_include_directories(run_unit_tests PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party)
target_link_libraries(run_unit_tests matrix)
add_test(NAME unit_tests COMMAND run_unit_tests)