add_library(cpp_code_generator STATIC)
target_sources(cpp_code_generator PRIVATE
    "scanner.cpp" 
    "compile_file.cpp"
    "parser.cpp"
    "code_generator.cpp"
)
target_sources(cpp_code_generator PUBLIC
  FILE_SET HEADERS
  BASE_DIRS ../
  FILES
  "compile_file.hpp"
  "code_generator.hpp"
  "scanner.hpp"
  "parser.hpp"
  "types.hpp"
  "token_type.hpp"
)
