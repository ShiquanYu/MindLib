cmake_minimum_required(VERSION 3.0)


project(TSQueue)

add_compile_options(-Wextra -Wall -Wno-unused)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
