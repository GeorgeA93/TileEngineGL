cmake_minimum_required(VERSION 3.5)
project(TileEngineGL)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

include_directories(src/
        src/Mesh
        src/Renderer
        vendor/glad/include/
        vendor/glfw/include/
        vendor/glm/
        vendor/stb/)

file(GLOB VENDORS_SOURCES vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS src/*.h src/Mesh/*.h src/Renderer/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp src/Mesh/*.cpp src/Renderer/*.cpp)
file(GLOB PROJECT_TEXTURES res/textures/*.png
        res/textures/*.jpeg
        res/textures/*.jpg)
file(GLOB PROJECT_SHADERS Shaders/*.comp
        res/shaders/*.frag
        res/shaders/*.geom
        res/shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
        Readme.md
        .gitattributes
        .gitignore
        .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Textures" FILES ${PROJECT_TEXTURES})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
        ${PROJECT_SHADERS} ${PROJECT_TEXTURES} ${PROJECT_CONFIGS}
        ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw
        ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})