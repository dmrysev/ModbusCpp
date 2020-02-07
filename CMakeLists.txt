project(drive_modbus)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wconversion -Wsign-conversion")
endif()

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} modbus)
