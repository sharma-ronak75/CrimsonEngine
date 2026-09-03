#include "../header/mesh.h"
#include <stdexcept>

namespace Crimson
{
    void Mesh::add_vertex(const Vertex& vertex)
    {
        mesh_data.emplace_back(vertex);
        vertex_count++;
    }

    void Mesh::remove_vertex(size_t index)
    {
        mesh_data.erase(mesh_data.begin() + index);
        vertex_count--;
    }
    

    void Mesh::add_vertices(const std::vector<Vertex>& vertices)
    {
        mesh_data.reserve(mesh_data.size() + vertices.size());
        for(auto& vertex: vertices) mesh_data.emplace_back(vertex);
        vertex_count += vertices.size();
    }

    void Mesh::add_vertices(const std::initializer_list<Vertex> vertices)
    {
        mesh_data.reserve(mesh_data.size() + vertices.size());
        for(auto& vertex: vertices) mesh_data.emplace_back(vertex);
        vertex_count += vertices.size();
    }

    Mesh* Primitive::create_plane()
    {
        Mesh* mesh = new Mesh();
        if(mesh == nullptr) throw std::runtime_error("memory allocation failed");
        
        mesh->add_vertex(Vertex{glm::vec3( -1, -1, 0), glm::vec3(1)});
        mesh->add_vertex(Vertex{glm::vec3(  1, -1, 0), glm::vec3(1)});
        mesh->add_vertex(Vertex{glm::vec3( -1,  1, 0), glm::vec3(1)});
        mesh->add_vertex(Vertex{glm::vec3(  1,  1, 0), glm::vec3(1)});
        mesh->add_vertex(Vertex{glm::vec3( -1,  1, 0), glm::vec3(1)});
        mesh->add_vertex(Vertex{glm::vec3(  1, -1, 0), glm::vec3(1)});
        return mesh;
    }
}