cmake_minimum_required(VERSION 3.10)
project(mush VERSION 0.1.0 LANGUAGES C)

# Compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Warning flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# Include directories
#include_directories(include)

find_package(X11 REQUIRED)
#include_directories(${X11_INCLUDE_DIRS})
add_executable(mush src/main.c)
target_link_libraries(mush ${X11_LIBRARIES})
target_include_directories(mush PRIVATE ${X11_INCLUDE_DIRS})
# Find required libraries
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(X11 REQUIRED x11)

# Source files
#set(SOURCES
#    src/main.c
#)

# Optional GUI component
#if(WITH_GUI)
#    list(APPEND SOURCES src/x11_gui.c)
#  list(APPEND EXTRA_LIBS ${X11_LIBRARIES})
#    add_definitions(-DWITH_X11_GUI=1)
#endif()

# Create executable
#target_link_libraries(mush ${EXTRA_LIBS})

# Installation
install(TARGETS mush DESTINATION bin)
