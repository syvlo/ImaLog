include_directories (${CMAKE_SOURCE_DIR}/ImaLogCPP/src) 
link_directories (${CMAKE_BINARY_DIR}/ImaLogCPP) 

add_executable (WriteText WriteText.cpp)
target_link_libraries (WriteText ImaLog)
