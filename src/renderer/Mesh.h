#pragma once

#include "../core/Vector3.h"
#include <vector>

struct Vertex {
    Vector3 position;
    Vector3 normal;
    Vector3 color;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};
