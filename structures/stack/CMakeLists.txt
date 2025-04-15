add_library(stack STATIC
	"stack/stack_node.h" 
    "stack/stack.h" "stack.cpp")

set_target_properties(stack PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(stack PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")