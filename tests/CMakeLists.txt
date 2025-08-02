find_package(GTest CONFIG REQUIRED)

add_executable(tests
    "test_files.cpp"
    "test_input.hpp"
    "test_named_array.cpp"
 "gtest_printing.cpp" "test_passing_file.cpp" "test_no_fail.cpp" "file_test.cpp")
target_link_libraries(tests PRIVATE 
    GTest::gtest_main cpp_code_generator
)

