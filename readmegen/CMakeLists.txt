find_package(ml_cpp_utils REQUIRED)

add_executable(readmegen
    main.cpp 
)

target_link_libraries(readmegen
    PRIVATE 
        cpp_code_generator
        ml_cpp_utils::ml_cpp_utils
)

