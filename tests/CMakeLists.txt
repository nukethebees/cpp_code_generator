find_package(GTest CONFIG REQUIRED)

add_executable(tests
    "test_files.cpp"
    "test_input.hpp"
    "test_named_array.cpp"
)
target_link_libraries(tests PRIVATE 
    GTest::gtest_main cpp_code_generator
)

