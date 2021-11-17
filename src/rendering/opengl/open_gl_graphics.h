#pragma once

#if __EMSCRIPTEN__
    #define GLES
    #include <GLES3/gl3.h>
#elif __APPLE__
#include <OpenGL/gl3.h>
#else
    #define GLAD
    #include <glad/glad.h>
#endif
