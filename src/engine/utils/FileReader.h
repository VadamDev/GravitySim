#pragma once

#include <fstream>
#include <string>
#include <iostream>

namespace engine::utils {
    inline std::string readFile(const std::string& filePath)
    {
        std::ifstream in;
        in.open(filePath);

        std::string result;
        if (in.is_open())
        {
            std::string line;
            while(getline(in, line))
            {
                result.append(line).append("\n");
            }
        } else
            std::cout << "Could not open file " << filePath << std::endl;

        return result;
    }
}

