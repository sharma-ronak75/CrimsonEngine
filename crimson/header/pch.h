#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <memory>
#include <format>
#include <utility>
#include <cstddef>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef __glew_h__
#include <GL/glew.h>
#endif
#ifndef _glfw3_h_
#include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <numbers>
#include <unordered_map>
#include <array>
#include <glm/gtx/hash.hpp>

namespace fs = std::filesystem; // NOLINT(misc-unused-alias-decls)
#include <cstdint>
