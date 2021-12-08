#pragma once
#include <hangout_engine/platform/filesystem.h>

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "types.h"

#if !__EMSCRIPTEN__
#define HE_SHADER_VERSION_STRING "#version 330 core\n"
#else
#define HE_SHADER_VERSION_STRING "#version 300 es\n"
#endif

namespace HE {
    class Shader {
    public:
        virtual void Bind() = 0;
        virtual void Compile(const std::string& vertexSource, const std::string& fragmentSource) = 0;
        virtual void LoadAndCompile(std::filesystem::path&& vertexPath, std::filesystem::path&& fragmentPath)  {

            std::string vertexCode;
            std::string fragmentCode;

            Path vertexAssetPath = Filesystem::GetAssetPath() /= vertexPath;
            Path fragmentAssetPath = Filesystem::GetAssetPath() /= fragmentPath;

            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            vShaderFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
            fShaderFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

            try {
                vShaderFile.open(vertexAssetPath);
                fShaderFile.open(fragmentAssetPath);
                std::stringstream vShaderStream, fShaderStream;

                //read file's buffer contents into streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                // close handlers
                vShaderFile.close();
                fShaderFile.close();

                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();

            } catch (const std::ifstream::failure& e) {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
            }

            Compile(vertexCode, fragmentCode);
        }

        virtual const std::vector<TextureSamplerBinding>& GetTextureSamplers() { return _samplers; }
        virtual void SetTextureSamplers(std::vector<TextureSamplerBinding>&& samplers) {
            _samplers = samplers;
        }
        virtual void SetTextureSamplers(std::initializer_list<TextureSamplerBinding>&& elements) {
            _samplers = elements;
        }

        // Uniforms
        virtual void Boolean(const std::string& name, bool value) const = 0;
        virtual void Int(const std::string& name, int value) const = 0;
        virtual void Float(const std::string& name, float value) const = 0;
        virtual void Float2(const std::string& name, const glm::vec2& value) const = 0;
        virtual void Float3(const std::string& name, const glm::vec3& value) const = 0;
        virtual void Float4(const std::string& name, const glm::vec4& value) const = 0;
        virtual void UniformMat4(const std::string&, const glm::mat4&) const = 0;

        virtual uint32_t GetHandle() = 0;
    protected:
        std::vector<TextureSamplerBinding> _samplers {};

    private:

    };
}