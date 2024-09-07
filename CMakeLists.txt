cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(ImZoomableImage VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

# set project files
set(PRJ_HEADERS ImZoomableImage.h)
set(PRJ_SOURCES ImZoomableImage.cpp)
set(PRJ_MAIN imgui_demo.cpp)

# Set functions
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Executables 
# add_executable(${PROJECT_NAME} ${PRJ_HEADERS} ${PRJ_MAIN})
add_executable(demo ${PRJ_HEADERS} ${PRJ_SOURCES} ${PRJ_MAIN})

# Link libraries 
# find_package(glad CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
#
# find_package(glfw3 CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
#
# find_package(imgui CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
#
# find_package(OpenGL REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
#
find_package(glad CONFIG REQUIRED)
target_link_libraries(demo PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(demo PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(demo PRIVATE imgui::imgui)

find_package(OpenGL REQUIRED)
target_link_libraries(demo PRIVATE OpenGL::GL)


