#pragma once

#include <string>

namespace engine {
    class ShaderProgram {

    public:
        ShaderProgram(std::string vertexPath, std::string fragmentPath);
        ~ShaderProgram();

        void bind() const;
        void unbind() const;

    private:
        unsigned int programId;
        unsigned int vertexShader, fragmentShader;

        unsigned int createShader(const char *source, unsigned int type);
    };
}
