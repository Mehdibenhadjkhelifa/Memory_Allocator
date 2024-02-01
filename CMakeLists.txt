cmake_minimum_required(VERSION 3.27)


project(Memory_Allocator LANGUAGES C)

file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "src/*.h")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")

add_compile_options(-g)

add_executable(Memory_Allocator ${SOURCES} ${HEADERS})
