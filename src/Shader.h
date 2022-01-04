#pragma once

#include "string"
#include "glm/glm.hpp"

#include "unordered_map"

namespace renderer {
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class Shader
    {
        public:
            Shader(const std::string filePath);
            ~Shader();
            
            void Bind() const;
            void Unbind() const;

            // Set uniform
            void SetUniform1i(const std::string& name, int i0);
            void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
            void SetUniforMat4f(const std::string& name, const glm::mat4& matrix);
        private:
            std::string m_FilePath;
            unsigned int m_RendererID;
            std::unordered_map<std::string, int> m_UniformLocationChache;

            ShaderProgramSource ParseShader(const std::string &filePath);
            unsigned int CompileShader(unsigned int type, const std::string &source);
            unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    };
}
