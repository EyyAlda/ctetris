cmake_minimum_required(VERSION 3.10)

project(Tetris LANGUAGES C)

set(CMAKE_C_COMPILER "gcc")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)

add_executable(${PROJECT_NAME} 
    src/game.c
)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
    PkgConfig::GTK4
    PkgConfig::GLIB
)
                
# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${GTK4_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
)

# Print compiler information for debugging
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C Flags: ${CMAKE_C_FLAGS}")
