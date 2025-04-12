add_library(rb_tree STATIC
	 "rb_tree/rb_node.h"
	 "rb_tree/rb_tree.h"
	 "rb_tree.cpp")

set_target_properties(rb_tree PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(rb_tree PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")