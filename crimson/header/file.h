#pragma once
#include "pch.h"

namespace File
{
    std::string read(fs::path location);
    void write(fs::path location, std::string data);
}
