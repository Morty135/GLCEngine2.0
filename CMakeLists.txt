cmake_minimum_required(VERSION 3.6.3)
project(GLCEngine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*")
file(GLOB HEADERS "headers/*")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")

add_subdirectory(include/glfw)
add_subdirectory(include/glad)
add_subdirectory(include/glm)

# fix for the unzip compiler error
set(ASSIMP_BUILD_MINIZIP ON CACHE BOOL "" FORCE)
set(ASSIMP_USE_HUNTER ON CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)

add_subdirectory(include/assimp)

add_executable("${CMAKE_PROJECT_NAME}" ${SOURCES} ${HEADERS})

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw glad glm assimp)

#Solves the class conflict allows to compile 
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options("${CMAKE_PROJECT_NAME}" PRIVATE -fpermissive)
endif()