#include "../header/pch.h" // IWYU pragma: keep

namespace File{
// Read contents of a text file
std::string read(fs::path location) 
{
    std::ifstream file(location);
    if(!file.is_open())
    {
        throw std::runtime_error(("Cannot open file " + location.string()).c_str());
    }
    
    std::string line;
    std::string content;
    while(std::getline(file, line))
    {
        content += line += '\n';
    }
    
    file.close();
    return content;
}

void write(fs::path location, std::string data)
{
    std::ofstream file(location);
    if(!file.is_open())
    {
        throw std::runtime_error(("Cannot open file " + location.string()).c_str());
    }

    file << data;
    file.close();
}
}
