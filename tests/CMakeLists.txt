find_package(GTest CONFIG REQUIRED)

add_executable(tests
    "test_files.cpp"
)
target_link_libraries(tests PRIVATE 
    GTest::gtest_main cpp_code_generator
)

