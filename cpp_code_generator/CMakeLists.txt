add_library(cpp_code_generator STATIC)
target_sources(cpp_code_generator PRIVATE
    "ast_processor.cpp"
    "code_generator.cpp"
    "compile_file.cpp"
    "scanner.cpp" 
    "parser.cpp"   
)
target_sources(cpp_code_generator PUBLIC
  FILE_SET HEADERS
  BASE_DIRS ../
  FILES
  "ast_processor.hpp"
  "compile_file.hpp"
  "code_generator.hpp"
  "scanner.hpp"
  "parser.hpp"
  "types.hpp"
  "token_type.hpp"
  "string_hasher.hpp"
  "result_macros.hpp"
)
