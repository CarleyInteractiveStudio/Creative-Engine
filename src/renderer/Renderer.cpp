#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// This is a placeholder for GLAD
#define GL_GLEXT_PROTOTYPES
#include <SDL3/SDL_opengl.h>

std::string read_shader_file(const char* path) {
    std::ifstream file(path);
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

Renderer::Renderer() {
    std::string vertex_shader_source = read_shader_file("src/renderer/simple.vert");
    std::string fragment_shader_source = read_shader_file("src/renderer/simple.frag");

    shader_program = create_shader_program(vertex_shader_source.c_str(), fragment_shader_source.c_str());

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shader_program);
}

unsigned int Renderer::compile_shader(const char* source, int type) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        std::cerr << "Shader compilation failed: " << info_log << std::endl;
    }

    return shader;
}

unsigned int Renderer::create_shader_program(const char* vertex_source, const char* fragment_source) {
    unsigned int vertex_shader = compile_shader(vertex_source, GL_VERTEX_SHADER);
    unsigned int fragment_shader = compile_shader(fragment_source, GL_FRAGMENT_SHADER);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    int success;
    char info_log[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        std::cerr << "Shader linking failed: " << info_log << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

#include "../core/Matter.h"
#include "../core/TransformLaw.h"
#include "../core/MaterialColorLaw.h"

void Renderer::render(const Mesh& mesh, const Material& material, const Camera& camera, const Matrix4& model_matrix) {
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shader_program);

    Matrix4 view_matrix = camera.get_view_matrix();
    Matrix4 projection_matrix = camera.get_projection_matrix();
    Matrix4 mvp = projection_matrix * view_matrix * model_matrix;

    unsigned int mvp_location = glGetUniformLocation(shader_program, "mvp");
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp.m[0][0]);

    unsigned int color_location = glGetUniformLocation(shader_program, "color");
    glUniform3f(color_location, material.color.x, material.color.y, material.color.z);

    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Renderer::draw(Creative::Matter& matter, const Camera& camera)
{
    auto* transform_law = matter.GetLaw<Creative::TransformLaw>();
    auto* appearance_law = matter.GetLaw<Creative::MaterialColorLaw>();

    if (transform_law && appearance_law) {
        Matrix4 model_matrix = transform_law->GetTransform();
        Material material(appearance_law->color);

        // For now, we draw a cube for any matter.
        // In the future, we would have a MeshLaw or similar.
        std::vector<Vertex> vertices = {
            // positions          // normals
            { -0.5f, -0.5f, -0.5f },
            {  0.5f, -0.5f, -0.5f },
            {  0.5f,  0.5f, -0.5f },
            { -0.5f,  0.5f, -0.5f },
            { -0.5f, -0.5f,  0.5f },
            {  0.5f, -0.5f,  0.5f },
            {  0.5f,  0.5f,  0.5f },
            { -0.5f,  0.5f,  0.5f },
        };
        std::vector<unsigned int> indices = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            7, 3, 0, 0, 4, 7,
            6, 2, 1, 1, 5, 6,
            0, 3, 2, 2, 1, 0,
            4, 7, 6, 6, 5, 4,
        };
        Mesh cube(vertices, indices);
        render(cube, material, camera, model_matrix);
    }
}
