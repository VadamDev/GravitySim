#include "ShaderProgram.h"
#include "../../utils/FileReader.h"

#include <glad/glad.h>

namespace engine {
    ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath)
    {
        const std::string vertexSource = utils::readFile(vertexPath);
        const std::string fragmentSource = utils::readFile(fragmentPath);

        if (vertexSource.empty() || fragmentSource.empty())
        {
            //TODO: throw error
        }

        programId = glCreateProgram();

        vertexShader = createShader(vertexSource.c_str(), GL_VERTEX_SHADER);
        fragmentShader = createShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

        glAttachShader(programId, vertexShader);
        glAttachShader(programId, fragmentShader);

        glLinkProgram(programId);
        //TODO: retrieve link log

        glValidateProgram(programId);
        //TODO: get validate log

        glDetachShader(programId, vertexShader);
        glDetachShader(programId, fragmentShader);

        //TODO: setup uniforms
    }

    ShaderProgram::~ShaderProgram()
    {
        unbind();

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glDeleteProgram(programId);
    }

    void ShaderProgram::bind() const
    {
        glUseProgram(programId);
    }

    void ShaderProgram::unbind() const
    {
        glUseProgram(0);
    }

    /*
       Private
     */

    unsigned int ShaderProgram::createShader(const char *source, const unsigned int type)
    {
        unsigned int shaderId = glCreateShader(type);
        //todo: if shader = 0 --> throw error

        glShaderSource(shaderId, 1, &source, nullptr);
        glCompileShader(shaderId);

        return shaderId;
    }

}