#include "../header/material.h"

namespace Crimson::Primitive
{
    Material create_unlit_material()
    {
        return Material{Crimson::RawShader::load("crimson/shaders/base_unlit.glsl")};
    }
    
    Material create_lit_material()
    {
        return Material{Crimson::RawShader::load("crimson/shaders/base_lit.glsl")};
    }
}
