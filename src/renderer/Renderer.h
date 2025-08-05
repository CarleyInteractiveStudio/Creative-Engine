#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "../core/Matrix4.h"

namespace Creative {
    class Matter;
}

class Renderer {
public:
    Renderer();
    ~Renderer();

    void render(const Mesh& mesh, const Material& material, const Camera& camera, const Matrix4& model_matrix);
    void draw(Creative::Matter& matter, const Camera& camera);

private:
    unsigned int shader_program;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int compile_shader(const char* source, int type);
    unsigned int create_shader_program(const char* vertex_source, const char* fragment_source);
};
