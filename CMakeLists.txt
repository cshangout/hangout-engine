cmake_minimum_required(VERSION 3.20)
project(hangout-engine)

set(CMAKE_CXX_STANDARD 20)

# Outputs builds to the /dist directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME})

add_subdirectory(external/SDL)
add_subdirectory(external/glm)
add_subdirectory(external/glad)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OPENGL_LIBRARY OpenGL::GL)
    # This is used to silence deprecation warnings on mac, because they're annoying.
    add_compile_definitions(GL_SILENCE_DEPRECATION=1)
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        glm
        glad

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        SDL2main
        SDL2-static
        ${OPENGL_LIBRARY}
        external/stb
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        glm
        glad

    PRIVATE
        SDL2main
        SDL2-static
        ${OPENGL_LIBRARY}

)