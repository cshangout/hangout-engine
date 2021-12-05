#pragma once
#include <vector>
#include <hangout_engine/rendering/types.h>

namespace HE {
    constexpr int cubeNumIndices = 36;
    constexpr int cubeNumVertices = 24;

    constexpr int cubeIndices[] {
            // Front
            0, 1, 3,
            1, 2, 3,
            // Back
            4, 5, 7,
            5, 6, 7,
            // Left
            8, 9, 11,
            9, 10, 11,
            // Right
            12, 13, 15,
            13, 14, 15,
            // Top
            16, 17, 19,
            17, 18, 19,
            // Bottom
            20, 21, 23,
            21, 22, 23,
    };

    constexpr Vertex cubeVertices[] {
            // FRONT
            {
                .position = {0.5f, 0.5f, 0.5f},
                .uv = { 1.f, 1.f },
                .normal = { 0, 0, 1.f }
            },
            {
                .position = {0.5f, -0.5f, 0.5f},
                .uv = { 1.f, 0.f },
                .normal = { 0, 0, 1.f }
            },
            {
                .position = {-0.5f, -0.5f, 0.5f},
                .uv = { 0.f, 0.f },
                .normal = { 0, 0, 1.f }
            },
            {
                .position = {-0.5f, 0.5f, 0.5f},
                .uv = { 0.f, 1.f },
                .normal = { 0, 0, 1.f }
            },

            // BACK
            {
                    .position = {-0.5f, 0.5f, -0.5f},
                    .uv = { 1.f, 1.f },
                    .normal = { 0, 0, -1.f }
            },
            {
                    .position = {-0.5f, -0.5f, -0.5f},
                    .uv = { 1.f, 0.f },
                    .normal = { 0, 0, -1.f }
            },
            {
                    .position = {0.5f, -0.5f, -0.5f},
                    .uv = { 0.f, 0.f },
                    .normal = { 0, 0, -1.f }
            },
            {
                    .position = {0.5f, 0.5f, -0.5f},
                    .uv = { 0.f, 1.f },
                    .normal = { 0, 0, -1.f }
            },

            // LEFT
            {
                    .position = {-0.5f, 0.5f, 0.5f},
                    .uv = { 1.f, 1.f },
                    .normal = { -1.f, 0, 0.f }
            },
            {
                    .position = {-0.5f, -0.5f, 0.5f},
                    .uv = { 1.f, 0.f },
                    .normal = { -1.f, 0, 0.f }
            },
            {
                    .position = {-0.5f, -0.5f, -0.5f},
                    .uv = { 0.f, 0.f },
                    .normal = { -1.f, 0, 0.f }
            },
            {
                    .position = {-0.5f, 0.5f, -0.5f},
                    .uv = { 0.f, 1.f },
                    .normal = { -1.f, 0, 0.f }
            },

            // RIGHT
            {
                    .position = {0.5f, 0.5f, -0.5f},
                    .uv = { 1.f, 1.f },
                    .normal = { 1.f, 0, 0.f }
            },
            {
                    .position = {0.5f, -0.5f, -0.5f},
                    .uv = { 1.f, 0.f },
                    .normal = { 1.f, 0, 0.f }
            },

            {
                    .position = {0.5f, -0.5f, 0.5f},
                    .uv = { 0.f, 0.f },
                    .normal = { 1.f, 0, 0.f }
            },
            {
                    .position = {0.5f, 0.5f, 0.5f},
                    .uv = { 0.f, 1.f },
                    .normal = { 1.f, 0, 0.f }
            },

            // TOP
            {
                    .position = {0.5f, 0.5f, -0.5f},
                    .uv = { 1.f, 1.f },
                    .normal = { 0.f, 1.f, 0.f }
            },
            {
                    .position = {0.5f, 0.5f, 0.5f},
                    .uv = { 1.f, 0.f },
                    .normal = { 0.f, 1.f, 0.f }
            },

            {
                    .position = {-0.5f, 0.5f, 0.5f},
                    .uv = { 0.f, 0.f },
                    .normal = { 0.f, 1.f, 0.f }
            },
            {
                    .position = {-0.5f, 0.5f, -0.5f},
                    .uv = { 0.f, 1.f },
                    .normal = { 0.f, 1.f, 0.f }
            },

            // BOTTOM
            {
                    .position = {0.5f, -0.5f, 0.5f},
                    .uv = { 1.f, 1.f },
                    .normal = { 0.f, -1.f, 0.f }
            },
            {
                    .position = {0.5f, -0.5f, -0.5f},
                    .uv = { 1.f, 0.f },
                    .normal = { 0.f, -1.f, 0.f }
            },

            {
                    .position = {-0.5f, -0.5f, -0.5f},
                    .uv = { 0.f, 0.f },
                    .normal = { 0.f, -1.f, 0.f }
            },
            {
                    .position = {-0.5f, -0.5f, 0.5f},
                    .uv = { 0.f, 1.f },
                    .normal = { 0.f, -1.f, 0.f }
            },
    };


    constexpr int pyramidNumIndices = 18;
    constexpr int pyramidNumVertices = 16;

    constexpr int pyramidIndices[] {
            // Front Tri
            0, 1, 2,
            // Right Tri
            3, 4, 5,
            // Back Tri
            6, 7, 8,
            // Left Tri
            9, 10, 11,
            // Bottom quad
            12, 13, 14,
            13, 15, 14,
    };

    constexpr Vertex pyramidVertices[]{
            // FRONT TRI
            {
                    .position = {-0.5f, 0.f, 0.5f},
                    .uv = {0.f, 0.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {0.f, 1.f, 0.f},
                    .uv = {0.5f, 1.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {0.5f, 0.f, 0.5f},
                    .uv = {1.f, 0.f},
                    .normal = {0, 0, 1.f}
            },
            // RIGHT TRI
            {
                    .position = {0.5f, 0.f, 0.5f},
                    .uv = {0.f, 0.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {0.f, 1.f, 0.f},
                    .uv = {0.5f, 1.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {0.5f, 0.f, -0.5f},
                    .uv = {1.f, 0.f},
                    .normal = {0, 0, 1.f}
            },
            //BACK TRI
            {
                    .position = {0.5f, 0.f, -0.5f},
                    .uv = {0.f, 0.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {0.f, 1.f, 0.f},
                    .uv = {0.5f, 1.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {-0.5f, 0.f, -0.5f},
                    .uv = {1.f, 0.f},
                    .normal = {0, 0, 1.f}
            },
            // LEFT TRI
            {
                    .position = {-0.5f, 0.f, -0.5f},
                    .uv = {0.f, 0.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {0.f, 1.f, 0.f},
                    .uv = {0.5f, 1.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {-0.5f, 0.f, 0.5f},
                    .uv = {1.f, 0.f},
                    .normal = {0, 0, 1.f}
            },
            // Bottom square
            {
                    .position = {-0.5f, 0.f, -0.5f},
                    .uv = {0.f, 0.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {-0.5f, 0.f, 0.5f},
                    .uv = {0.f, 1.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {0.5f, 0.f, -0.5f},
                    .uv = {1.f, 0.f},
                    .normal = {0, 0, 1.f}
            },
            {
                    .position = {0.5f, 0.f, 0.5f},
                    .uv = {1.f, 1.f},
                    .normal = {0, 0, 1.f}
            }
    };
}
