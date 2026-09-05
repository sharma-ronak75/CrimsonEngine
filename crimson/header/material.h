#pragma once

#include "rawshader.h"

namespace Crimson
{
    class Material
    {
    public:
        RawShader shader{};

        Material() = default;
        Material(RawShader shader): shader(shader) {}
        
        template<typename V> void set_shader_attribute(const std::string& name, V value) const;
    };

    template<typename V> void Material::set_shader_attribute(const std::string& name, V value) const
    {
        shader.use();
        shader.set_uniform(name.c_str(), value);
        Crimson::RawShader::use_none();
    }
}
