cmake_minimum_required(VERSION 3.7)

project(Sandbox2D)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED COMPONENTS main)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(Box2D REQUIRED)
find_package(Threads REQUIRED)

# Adds Project Source Files into a library
add_library(libSandbox2D "")

# Need to use include() instead of add_subdirectory() because we want to
# be able to use target_link_libraries() to add a library to a dependency
# for a target defined in a parent directory
include(Sandbox2D/CMakeLists.txt)
include(GameFiles/CMakeLists.txt)

add_executable(Sandbox2D.exe main.cpp)

target_link_libraries(Sandbox2D.exe SDL2)
target_link_libraries(Sandbox2D.exe SDL2_ttf)
target_link_libraries(Sandbox2D.exe SDL2_image)
target_link_libraries(Sandbox2D.exe SDL2_mixer)
target_link_libraries(Sandbox2D.exe Box2D)
target_link_libraries(Sandbox2D.exe ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(Sandbox2D.exe libSandbox2D)

# Copy SDL2 DLLs to output folder on Windows
if(WIN32)
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET CMakeDemo POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:Sandbox2D.exe>)
    endforeach()
endif()
