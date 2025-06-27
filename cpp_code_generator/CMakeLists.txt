add_library(cpp_code_generator STATIC)
target_sources(cpp_code_generator PRIVATE
    "scanner.cpp" 
 )
target_sources(cpp_code_generator PUBLIC
  FILE_SET HEADERS
  BASE_DIRS ../
  FILES
  "scanner.hpp"
)
