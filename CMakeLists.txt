cmake_minimum_required(VERSION 3.20)
project(hangout-engine)

set(CMAKE_CXX_STANDARD 20)

# Outputs builds to the /dist directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME})

if (${CMAKE_BUILD_TYPE} MATCHES "Debug" OR DEFINED ${NO_OPTIMIZATIONS})
    if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Od")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Od")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    endif()
endif()

add_subdirectory(external/SDL)
add_subdirectory(external/glm)
add_subdirectory(external/glad)
add_subdirectory(external/entt)

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
        EnTT

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        SDL2main
        SDL2-static
        ${OPENGL_LIBRARY}
        external/stb
        glad
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        glm
        EnTT

    PRIVATE
        glad
        SDL2main
        SDL2-static
        ${OPENGL_LIBRARY}

)