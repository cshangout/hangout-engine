#pragma once
#include <array>
#include <glm/glm.hpp>
#include <hangout_engine/rendering/types.h>
#include <utility>
#include <numbers>

namespace HE {

    constexpr double PI = std::numbers::pi;

    inline glm::vec3 getNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, bool print = false) {
        glm::vec3 U = p2 - p1;
        glm::vec3 V = p3 - p1;

        auto normal = glm::cross(U, V);
//        glm::vec3 normal {
//            (U.y * V.z) - (U.z * V.y),
//            (U.z * V.x) - (U.x * V.z),
//            (U.x * V.y) - (U.y * V.x)
//        };

        if (print) {
            std::cout << "Normal: (" << normal.x << "," << normal.y << "," << normal.z << ")" << std::endl;
        }

        return normal;
    }

    constexpr std::array<uint32_t, 36> cubeIndices {
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

    constexpr std::array<uint32_t, 36> invertedCubeIndices {
            // Front
            3, 1, 0,
            3, 2, 1,
            // Back
            7, 5, 4,
            7, 6, 5,
            // Left
            11, 9, 8,
            11, 10, 9,
            // Right
            15, 13, 12,
            15, 14, 13,
            // Top
            19, 17, 16,
            19, 18, 17,
            // Bottom
            23, 21, 20,
            23, 22, 21,
    };

    constexpr std::array<Vertex, 24> cubeVertices {
            // FRONT
            Vertex {
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


    constexpr std::array<uint32_t, 18> pyramidIndices {
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

    constexpr std::array<Vertex, 16> pyramidVertices {
            // FRONT TRI
            Vertex {
                .position = {-0.5f, 0.f, 0.5f},
                .uv = {0.f, 0.f},
                .normal = {0, 0.5, 1.f}
            },
            {
                .position = {0.f, 1.f, 0.f},
                .uv = {0.5f, 1.f},
                .normal = {0, 0.5, 1.f}
            },
            {
                .position = {0.5f, 0.f, 0.5f},
                .uv = {1.f, 0.f},
                .normal = {0, 0.5, 1.f}
            },
            // RIGHT TRI
            {
                .position = {0.5f, 0.f, 0.5f},
                .uv = {0.f, 0.f},
                .normal = {1.f, 0.5f, 0.f}
            },
            {
                .position = {0.f, 1.f, 0.f},
                .uv = {0.5f, 1.f},
                .normal = {1.f, 0.5f, 0.f}
            },
            {
                .position = {0.5f, 0.f, -0.5f},
                .uv = {1.f, 0.f},
                .normal = {1.f, 0.5f, 0.f}
            },
            //BACK TRI
            {
                .position = {0.5f, 0.f, -0.5f},
                .uv = {0.f, 0.f},
                .normal = {0, 0.5, -1.f}
            },
            {
                .position = {0.f, 1.f, 0.f},
                .uv = {0.5f, 1.f},
                .normal = {0, 0.5, -1.f}
            },
            {
                .position = {-0.5f, 0.f, -0.5f},
                .uv = {1.f, 0.f},
                .normal = {0, 0.5, -1.f}
            },
            // LEFT TRI
            {
                .position = {-0.5f, 0.f, -0.5f},
                .uv = {0.f, 0.f},
                .normal = {-1.f, 0.5f, 0.f}
            },
            {
                .position = {0.f, 1.f, 0.f},
                .uv = {0.5f, 1.f},
                .normal = {-1.f, 0.5f, 0.f}
            },
            {
                .position = {-0.5f, 0.f, 0.5f},
                .uv = {1.f, 0.f},
                .normal = {-1.f, 0.5f, 0.f}
            },
            // Bottom square
            {
                .position = {-0.5f, 0.f, -0.5f},
                .uv = {0.f, 0.f},
                .normal = {0, -1.f, 0}
            },
            {
                .position = {-0.5f, 0.f, 0.5f},
                .uv = {0.f, 1.f},
                .normal = {0, -1.f, 0}
            },
            {
                .position = {0.5f, 0.f, -0.5f},
                .uv = {1.f, 0.f},
                .normal = {0, -1.f, 0}
            },
            {
                .position = {0.5f, 0.f, 0.5f},
                .uv = {1.f, 1.f},
                .normal = {0, -1.f, 0}
            }
    };

    static std::pair<std::vector<Vertex>, std::vector<uint32_t>> GenerateSphere(float radius = 1.f, uint32_t sectors = 50, uint32_t stacks = 50) {
        std::vector<Vertex> vertices {};
        std::vector<uint32_t> indices {};
        uint32_t k1, k2;
        float x, y, z, xy;                              // vertex position
        float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
        float s, t;                                     // vertex texCoord

        float sectorStep = 2 * PI / sectors;
        float stackStep = PI / stacks;
        float sectorAngle, stackAngle;

        for(uint32_t i = 0; i <= stacks; ++i)
        {
            stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
            xy = radius * cosf(stackAngle);             // r * cos(u)
            z = radius * sinf(stackAngle);              // r * sin(u)

            k1 = i * (sectors + 1);     // beginning of current stack
            k2 = k1 + sectors + 1;
            // add (sectorCount+1) vertices per stack
            // the first and last vertices have same position and normal, but different tex coords
            for(uint32_t j = 0; j <= sectors; ++j, ++k1, ++k2)
            {
                sectorAngle = static_cast<float>(j) * sectorStep;           // starting from 0 to 2pi

                // vertex position (x, y, z)
                x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
                y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

                // normalized vertex normal (nx, ny, nz)
                nx = x * lengthInv;
                ny = y * lengthInv;
                nz = z * lengthInv;

                // vertex tex coord (s, t) range between [0, 1]
                s = (float)j / static_cast<float>(sectors);
                t = (float)i / static_cast<float>(stacks);

                vertices.push_back(Vertex{
                    .position = {x, y, z},
                    .uv = {s, t},
                    .normal = {nx, ny, nz},
                });


            }
        }

        for(uint32_t i = 0; i < stacks; ++i)
        {
            k1 = i * (sectors + 1);     // beginning of current stack
            k2 = k1 + sectors + 1;      // beginning of next stack

            for(uint32_t j = 0; j < sectors; ++j, ++k1, ++k2)
            {
                // 2 triangles per sector excluding first and last stacks
                // k1 => k2 => k1+1
                if(i != 0)
                {
                    indices.push_back(k1);
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                }

                // k1+1 => k2 => k2+1
                if(i != (stacks-1))
                {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2 + 1);
                    indices.push_back(k2);
                }
            }
        }

        return {vertices, indices};
    }
}
