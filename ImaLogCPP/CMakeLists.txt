set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -g -ggdb")

add_library (ImaLog src/Logger.cpp)

add_subdirectory (test)
