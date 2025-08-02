cmake_minimum_required(VERSION 3.25)
project("cpp_code_generator")

add_subdirectory("cpp_code_generator")
add_subdirectory("cli")

# Define input and output paths
set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_input.cppg")
set(GENERATED_HEADER "${CMAKE_CURRENT_BINARY_DIR}/tests/test_input.hpp")

set(RUN_AUTOGEN ON)

# Custom command to run cpp_code_generator.exe
add_custom_command(
    OUTPUT ${GENERATED_HEADER}
    COMMAND $<TARGET_FILE:cli> ${INPUT_FILE} "--silent_on_success"
    DEPENDS cpp_code_generator ${INPUT_FILE}
    COMMENT "Running cpp_code_generator.exe to generate test_input.hpp"
)
add_custom_target(run_codegen DEPENDS ${GENERATED_HEADER})

add_subdirectory("tests")
if(RUN_AUTOGEN)
    add_dependencies(tests run_codegen)
endif()

add_subdirectory("readmegen")
add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/README.md"
    COMMAND $<TARGET_FILE:readmegen>
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS readmegen
    COMMENT "Running README generation."
)

add_custom_target(generate_readme DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/README.md")
# Force the README generator to run
if(RUN_AUTOGEN)
    add_dependencies(tests generate_readme)
endif()
