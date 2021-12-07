#include "open_gl_shader.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <hangout_engine/rendering/types.h>
#include <hangout_engine/rendering/texture.h>

namespace HE {
    OpenGLShader::~OpenGLShader() {
        if (_program) {
            glDeleteProgram(_program);
        }
    }

    void OpenGLShader::Bind() {
        glUseProgram(_program);

        for (auto& binding : _samplers) {
            auto textureUnit = static_cast<uint32_t>(binding.index);
            Int(binding.samplerName, static_cast<int>(binding.index));

            // Activate the appropriate texture
            glActiveTexture(GL_TEXTURE0 + textureUnit);
            // Set the uniform texture unit location
            // Bind the texture
            binding.texture->Bind();
        }
    }

    void OpenGLShader::Compile(const std::string& vertexCode, const std::string& fragmentCode) {
        auto newVertex = std::string(HE_SHADER_VERSION_STRING) + "\n" + vertexCode;
        auto newFragment = std::string(HE_SHADER_VERSION_STRING) + "\n" + fragmentCode;

        uint32_t vertex, fragment;

        int success;
        char infoLog[512];

        // Vertex Shader
        const char* vShaderCode = newVertex.c_str();
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Fragment shader
        const char* fShaderCode = newFragment.c_str();
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!fragment) {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        _program = glCreateProgram();
        glAttachShader(_program, vertex);
        glAttachShader(_program, fragment);
        glLinkProgram(_program);

        glGetProgramiv(_program, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(_program, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::LINKING FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void OpenGLShader::Boolean(const std::string &name, bool value) const {
        GLint location = getShaderLocation(name);

        glUniform1i(location, static_cast<int>(value));
    }

    void OpenGLShader::Int(const std::string &name, int value) const {
        GLint location = getShaderLocation(name);

        glUniform1i(location, value);
    }

    void OpenGLShader::Float(const std::string &name, float value) const {
        GLint location = getShaderLocation(name);

        glUniform1f(location, value);
    }

    void OpenGLShader::Float2(const std::string &name, const glm::vec2& value) const {
        GLint location = getShaderLocation(name);

        glUniform2fv(location, 1, glm::value_ptr(value));
    }

    void OpenGLShader::Float3(const std::string &name, const glm::vec3& value) const {
        GLint location = getShaderLocation(name);

        glUniform3fv(location, 1, glm::value_ptr(value));
    }

    void OpenGLShader::Float4(const std::string &name, const glm::vec4& value) const {
        GLint location = getShaderLocation(name);

        glUniform4fv(location, 1, glm::value_ptr(value));
    }

    void OpenGLShader::UniformMat4(const std::string& name, const glm::mat4 &matrix) const {
        GLint location = getShaderLocation(name);

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    GLint OpenGLShader::getShaderLocation(const std::string &name) const {
        return glGetUniformLocation(_program, name.c_str());
    }




}
