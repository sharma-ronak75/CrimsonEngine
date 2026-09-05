#pragma once

#include <functional>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <initializer_list>
#include <vector>
#include <memory>
#include "vertex.h"
namespace Crimson
{
    class Mesh
    {
    private:
        size_t vertex_count{};
    public:
        std::vector<Vertex> mesh_data;

        Mesh() = default;
        Mesh(const std::vector<Vertex>& mesh_data): mesh_data(mesh_data) {}
        Mesh(const std::initializer_list<Vertex> mesh_data): mesh_data(mesh_data) {}
        
        void add_vertex(const Vertex& vertex);
        void remove_vertex(size_t index);
        void add_vertices(const std::vector<Vertex>& vertices);
        void add_vertices(const std::initializer_list<Vertex> vertices);

        size_t get_vertex_count() const noexcept { return mesh_data.size(); }
    };

    namespace Primitive
    {
        std::shared_ptr<Mesh> create_plane();
        std::shared_ptr<Mesh> create_cube();
        std::shared_ptr<Mesh> create_sphere(int subdivisions = 1);
    }
}
/*

Mesh<VertexAttributeLayout<glm::vec3, int, float>>

struct _Layout
{
    glm::vec3 a0;
    int a1;
    float a2;
}

*/
