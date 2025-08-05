find_package(ml_cpp_utils REQUIRED)

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
  "token_type.hpp"
  "result_macros.hpp"
  "type_expr.hpp"
)

target_link_libraries(cpp_code_generator 
    PRIVATE 
        ml_cpp_utils::ml_cpp_utils
)