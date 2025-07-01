find_package(CLI11 REQUIRED)

add_executable(cli
    main.cpp 
)

target_link_libraries(cli PRIVATE 
    cpp_code_generator
    CLI11::CLI11
)

set_target_properties(cli PROPERTIES
    OUTPUT_NAME "cpp_code_generator"
)