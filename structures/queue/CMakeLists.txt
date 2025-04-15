add_library(queue STATIC
	"queue/queue_node.h" 
    "queue/queue.h" "queue.cpp")

set_target_properties(queue PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(queue PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")