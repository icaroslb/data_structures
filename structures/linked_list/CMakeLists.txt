add_library(linked_list STATIC
	"linked_list/linked_list_node.h" 
    "linked_list/linked_list.h" "linked_list.cpp")

set_target_properties(linked_list PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(linked_list PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")