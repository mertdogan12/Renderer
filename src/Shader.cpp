#include "Shader.h"
#include "Renderer.h"

#include "GL/glew.h"

#include "fstream"
#include "sstream"
#include "iostream"

namespace renderer {
    Shader::Shader(const std::string& filepath)
        : m_FilePath(filepath), m_RendererID(0)
    {
      ShaderProgramSource source = ParseShader(m_FilePath);
      m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
    }

    Shader::~Shader()
    {
        GLCALL(glDeleteShader(m_RendererID));
    }

    void Shader::Bind() const
    {
        GLCALL(glUseProgram(m_RendererID));
    }

    void Shader::Unbind() const
    {
        GLCALL(glUseProgram(0));
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    {
        int location = GetUniformLocation(name);
        GLCALL(glUniform4f(location, v0, v1, v2, v3));
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
    {
        int location = GetUniformLocation(name);
        GLCALL(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
    }

    void Shader::SetUniform1i(const std::string& name, int i0)
    {
        int location = GetUniformLocation(name);
        GLCALL(glUniform1i(location, i0));
    }

    int Shader::GetUniformLocation(const std::string& name)
    {
      if (m_UniformLocationChache.find(name) != m_UniformLocationChache.end())  
          return m_UniformLocationChache[name];

      GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
      if (location == -1)
          std::cout << "Warning> uniform '" << name << "' doesn't exist!" << std::endl;

      m_UniformLocationChache[name] = location;

      return location;
    }

    // Reads the shader file and parses the two shaders into a ShaderProgramSource Object.
    ShaderProgramSource Shader::ParseShader(const std::string &filePath)
    {
        std::ifstream inputFile(filePath);

        enum class ShaderType
        {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };

        std::string line;
        ShaderType type = ShaderType::NONE;
        std::stringstream ss[2];

        while(std::getline(inputFile, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            } else
                ss[(int) type] << line << std::endl;
        }

        return { ss[0].str(), ss[1].str() };
    }

    unsigned int CompileShader(unsigned int type, const std::string &source)
    {
        GLCALL(unsigned int id = glCreateShader(type));
        const char* src = source.c_str();
        GLCALL(glShaderSource(id, 1, &src, nullptr));
        GLCALL(glCompileShader(id));

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int lenght;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
            char message[lenght];
            glGetShaderInfoLog(id, lenght, &lenght, message);
            std::cout << "Failed to compile "
                      << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                      << " shader!" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    // Creates an Program and attachts the two given shaders to it.
    // Delets the two shader after it.
    // Then return the program (unsigned int, the id of the program).
    unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
    {
      unsigned int program = glCreateProgram();
      unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
      unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

      glAttachShader(program, vs);
      glAttachShader(program, fs);
      glLinkProgram(program);
      glValidateProgram(program);

      glDeleteShader(vs);
      glDeleteShader(fs);

      return program;
    }
}
