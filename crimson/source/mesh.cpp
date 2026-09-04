#include "../header/mesh.h"
#include <glm/ext/quaternion_geometric.hpp>
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
        
        for(int x = 0; x < subdivisions; x ++){
            for(int y = 0; y < subdivisions; y ++){
                mesh->add_vertices({
                    Vertex{glm::vec3( 0+x, 0+y, 0) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3( 1+x, 0+y, 0) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3( 0+x, 1+y, 0) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3( 1+x, 1+y, 0) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3( 0+x, 1+y, 0) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3( 1+x, 0+y, 0) / (float)subdivisions, glm::vec3(1)}
                });

                // +Z face
                mesh->add_vertices({
                    Vertex{glm::vec3(  0+x,  0+y, subdivisions) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  1+x,  0+y, subdivisions) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  0+x,  1+y, subdivisions) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  1+x,  1+y, subdivisions) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  0+x,  1+y, subdivisions) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  1+x,  0+y, subdivisions) / (float)subdivisions, glm::vec3(1)}
                });

                // -X face
                mesh->add_vertices({
                    Vertex{glm::vec3(0,  0+x, 0+y) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(0,  1+x, 0+y) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(0,  0+x, 1+y) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(0,  1+x, 1+y) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(0,  0+x, 1+y) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(0,  1+x, 0+y) / (float)subdivisions, glm::vec3(1)}
                });

                // +X face
                mesh->add_vertices({
                    Vertex{glm::vec3( subdivisions,  0+x,  0+y) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3( subdivisions,  1+x,  0+y) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3( subdivisions,  0+x,  1+y) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3( subdivisions,  1+x,  1+y) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3( subdivisions,  0+x,  1+y) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3( subdivisions,  1+x,  0+y) / (float)subdivisions, glm::vec3(1)}
                });

                // -Y face
                mesh->add_vertices({
                    Vertex{glm::vec3(  0+y, 0, 0+x) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  0+y, 0, 1+x) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  1+y, 0, 0+x) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  1+y, 0, 1+x) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  1+y, 0, 0+x) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  0+y, 0, 1+x) / (float)subdivisions, glm::vec3(1)}
                });

                // +Y face
                mesh->add_vertices({
                    Vertex{glm::vec3(  0+y, subdivisions, 0+x) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  0+y, subdivisions, 1+x) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  1+y, subdivisions, 0+x) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  1+y, subdivisions, 1+x) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  1+y, subdivisions, 0+x) / (float)subdivisions, glm::vec3(1)},
                    Vertex{glm::vec3(  0+y, subdivisions, 1+x) / (float)subdivisions, glm::vec3(1)}
                });

            }
        }

        // normalizing vecs
        for(auto& vertex: mesh->mesh_data)
        {
            vertex.position = glm::normalize(vertex.position * 2.0F - 1.0F);
        }

        return mesh;
    }
}