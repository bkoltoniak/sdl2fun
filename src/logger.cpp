#include "logger.h"
#include <iostream>
#include <fstream>

namespace sdl2fun
{
    const std::string filePath = "./log.txt";

    void logMessage(const std::string& message)
    {
        std::ofstream file(filePath, std::ios::app);
        file << message << '\n';
        file.close();
    }
}