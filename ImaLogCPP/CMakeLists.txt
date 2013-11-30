set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -g -ggdb")

find_package (OpenCV REQUIRED)

add_library (ImaLog src/Logger.cpp)
target_link_libraries (ImaLog ${OpenCV_LIBS})


add_subdirectory (test)
