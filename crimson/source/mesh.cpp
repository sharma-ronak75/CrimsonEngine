#include "../header/mesh.h"
#include <iostream>
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
        
        mesh->add_vertices({
            Vertex{glm::vec3( -1, -1, 0), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, 0), glm::vec3(1)},
            Vertex{glm::vec3( -1,  1, 0), glm::vec3(1)},
            Vertex{glm::vec3(  1,  1, 0), glm::vec3(1)},
            Vertex{glm::vec3( -1,  1, 0), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, 0), glm::vec3(1)}
        });
        return mesh;
    }

    Mesh* Primitive::create_cube()
    {
        Mesh* mesh = new Mesh();
        if(mesh == nullptr) throw std::runtime_error("memory allocation failed");

        // -Z face
        mesh->add_vertices({
            Vertex{glm::vec3( -1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3( -1,  1, -1), glm::vec3(1)},
            Vertex{glm::vec3(  1,  1, -1), glm::vec3(1)},
            Vertex{glm::vec3( -1,  1, -1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, -1), glm::vec3(1)}
        });

        // +Z face
        mesh->add_vertices({
            Vertex{glm::vec3( -1, -1, +1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, +1), glm::vec3(1)},
            Vertex{glm::vec3( -1,  1, +1), glm::vec3(1)},
            Vertex{glm::vec3(  1,  1, +1), glm::vec3(1)},
            Vertex{glm::vec3( -1,  1, +1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, +1), glm::vec3(1)}
        });

        // -X face
        mesh->add_vertices({
            Vertex{glm::vec3(-1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3(-1,  1, -1), glm::vec3(1)},
            Vertex{glm::vec3(-1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3(-1,  1,  1), glm::vec3(1)},
            Vertex{glm::vec3(-1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3(-1,  1, -1), glm::vec3(1)}
        });

        // +X face
        mesh->add_vertices({
            Vertex{glm::vec3( +1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3( +1,  1, -1), glm::vec3(1)},
            Vertex{glm::vec3( +1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3( +1,  1,  1), glm::vec3(1)},
            Vertex{glm::vec3( +1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3( +1,  1, -1), glm::vec3(1)}
        });

        // -Y face
        mesh->add_vertices({
            Vertex{glm::vec3( -1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3( -1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3( -1, -1,  1), glm::vec3(1)}
        });

        // +Y face
        mesh->add_vertices({
            Vertex{glm::vec3( -1, +1, -1), glm::vec3(1)},
            Vertex{glm::vec3( -1, +1,  1), glm::vec3(1)},
            Vertex{glm::vec3(  1, +1, -1), glm::vec3(1)},
            Vertex{glm::vec3(  1, +1,  1), glm::vec3(1)},
            Vertex{glm::vec3(  1, +1, -1), glm::vec3(1)},
            Vertex{glm::vec3( -1, +1,  1), glm::vec3(1)}
        });

        return mesh;
    }

    Mesh* Primitive::create_sphere(int subdivisions)
    {
        if(subdivisions < 1) throw std::invalid_argument("subdivisions must be >= 1");

        Mesh* mesh = new Mesh();
        if(mesh == nullptr) throw std::runtime_error("memory allocation failed");
        
        subdivisions = 2;
        // -Z face
        for(int x = 0; x < subdivisions; x ++){
            for(int y = 0; y < subdivisions; y ++){
                mesh->add_vertices({
                    Vertex{glm::vec3( -1 + x, -1 + y, -1), glm::vec3(1)},
                    Vertex{glm::vec3(  1 + x, -1 + y, -1), glm::vec3(1)},
                    Vertex{glm::vec3( -1 + x,  1 + y, -1), glm::vec3(1)},
                    Vertex{glm::vec3(  1 + x,  1 + y, -1), glm::vec3(1)},
                    Vertex{glm::vec3( -1 + x,  1 + y, -1), glm::vec3(1)},
                    Vertex{glm::vec3(  1 + x, -1 + y, -1), glm::vec3(1)}
                });
            }
        };

        return mesh;

        // +Z face
        mesh->add_vertices({
            Vertex{glm::vec3( -1, -1, +1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, +1), glm::vec3(1)},
            Vertex{glm::vec3( -1,  1, +1), glm::vec3(1)},
            Vertex{glm::vec3(  1,  1, +1), glm::vec3(1)},
            Vertex{glm::vec3( -1,  1, +1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, +1), glm::vec3(1)}
        });

        // -X face
        mesh->add_vertices({
            Vertex{glm::vec3(-1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3(-1,  1, -1), glm::vec3(1)},
            Vertex{glm::vec3(-1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3(-1,  1,  1), glm::vec3(1)},
            Vertex{glm::vec3(-1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3(-1,  1, -1), glm::vec3(1)}
        });

        // +X face
        mesh->add_vertices({
            Vertex{glm::vec3( +1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3( +1,  1, -1), glm::vec3(1)},
            Vertex{glm::vec3( +1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3( +1,  1,  1), glm::vec3(1)},
            Vertex{glm::vec3( +1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3( +1,  1, -1), glm::vec3(1)}
        });

        // -Y face
        mesh->add_vertices({
            Vertex{glm::vec3( -1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3( -1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1,  1), glm::vec3(1)},
            Vertex{glm::vec3(  1, -1, -1), glm::vec3(1)},
            Vertex{glm::vec3( -1, -1,  1), glm::vec3(1)}
        });

        // +Y face
        mesh->add_vertices({
            Vertex{glm::vec3( -1, +1, -1), glm::vec3(1)},
            Vertex{glm::vec3( -1, +1,  1), glm::vec3(1)},
            Vertex{glm::vec3(  1, +1, -1), glm::vec3(1)},
            Vertex{glm::vec3(  1, +1,  1), glm::vec3(1)},
            Vertex{glm::vec3(  1, +1, -1), glm::vec3(1)},
            Vertex{glm::vec3( -1, +1,  1), glm::vec3(1)}
        });

        return mesh;
    }
}