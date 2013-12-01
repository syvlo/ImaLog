set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -g -ggdb")

add_executable (ImaLogViewer src/Parser.cpp src/Log.cpp src/Date.cpp src/main.cpp)
