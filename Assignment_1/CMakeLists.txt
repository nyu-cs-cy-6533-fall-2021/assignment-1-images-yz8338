cmake_minimum_required(VERSION 2.8.12)
project(Assignment1)
### Add src to the include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
### Compile all the cpp files in src
file(GLOB SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_executable(${PROJECT_NAME}_bin ${SOURCES})
