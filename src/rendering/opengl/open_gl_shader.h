#pragma once
#include "open_gl_graphics.h"
#include <hangout_engine/rendering/shader.h>

namespace HE {
    class OpenGLShader : public Shader {
    public:
        ~OpenGLShader();
        void Bind() override;
        void Compile(const std::string& vertexSource, const std::string& fragmentSource) override;

        void Boolean(const std::string &name, bool value) const override;
        void Int(const std::string &name, int value) const override;
        void Float(const std::string &name, float value) const override;
        void Float2(const std::string &name, const glm::vec2& value) const override;
        void Float3(const std::string &name, const glm::vec3& value) const override;
        void Float4(const std::string &name, const glm::vec4& value) const override;
        void UniformMat4(const std::string& name, const glm::mat4& matrix) const override;

        uint32_t GetHandle() override { return _program; }

    private:
        [[nodiscard]] GLint getShaderLocation(const std::string& name) const;
        uint32_t _program = 0;
    };
}

