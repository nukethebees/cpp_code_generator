include(FetchContent)
FetchContent_Declare(
    cli11_proj
    QUIET
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG c5153634db3626a108e6ff74995f2a7658844018
)
FetchContent_MakeAvailable(cli11_proj)

add_executable(cli
    main.cpp 
)

target_link_libraries(cli 
    PRIVATE 
        cpp_code_generator
        CLI11::CLI11
)

set_target_properties(cli PROPERTIES
    OUTPUT_NAME "cpp_code_generator"
)