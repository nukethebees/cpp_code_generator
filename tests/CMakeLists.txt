find_package(GTest CONFIG REQUIRED)

add_executable(tests
    # Helpers
    "gtest_printing.cpp" 
    
    # Test fixtures / parameterised tests
    "testp_passing_file.cpp" 
    "testp_no_fail.cpp" 
    
    
    # Test definitions
    "test_files.cpp"
    "test_input.hpp"
    "test_named_array.cpp"   
 "misc.cpp")
target_link_libraries(tests PRIVATE 
    GTest::gtest_main cpp_code_generator
)

