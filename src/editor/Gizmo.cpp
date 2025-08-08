#include "Gizmo.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "../renderer/Camera.h"
#include "glad/glad.h"

// Helper function to read shader files
static std::string read_shader_file(const char* path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

Gizmo::Gizmo() {
    // Shaders
    std::string vertex_shader_source = read_shader_file("src/renderer/line.vert");
    std::string fragment_shader_source = read_shader_file("src/renderer/line.frag");

    const char* v_shader_code = vertex_shader_source.c_str();
    const char* f_shader_code = fragment_shader_source.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_code, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        // TODO: Log error
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_code, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        // TODO: Log error
    }

    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program, vertex);
    glAttachShader(m_shader_program, fragment);
    glLinkProgram(m_shader_program);
    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_shader_program, 512, NULL, infoLog);
        // TODO: Log error
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // VBO, VAO
    float vertices[] = {
        // positions      // colors
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // origin
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // X axis
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // origin
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Y axis
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // origin
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Z axis
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Gizmo::~Gizmo() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteProgram(m_shader_program);
}

void Gizmo::render(const Camera& camera, const Matrix4& model_matrix) {
    glUseProgram(m_shader_program);

    const Matrix4 view_matrix = camera.get_view_matrix();
    const Matrix4 projection_matrix = camera.get_projection_matrix();

    glUniformMatrix4fv(glGetUniformLocation(m_shader_program, "model"), 1, GL_FALSE, &model_matrix.m[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(m_shader_program, "view"), 1, GL_FALSE, &view_matrix.m[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(m_shader_program, "projection"), 1, GL_FALSE, &projection_matrix.m[0][0]);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}

bool Gizmo::on_mouse_button_down(const Camera& camera, const Matrix4& model_matrix, int x, int y) {
    // This is a simplified implementation. A real implementation would use raycasting.
    // For now, we'll just check if the mouse is in the general area of the gizmo.
    m_selected_axis = GizmoAxis::None;
    m_is_dragging = false;

    // A real implementation would require converting mouse coordinates to world space
    // and then checking for intersection with the gizmo's axes.
    // This is a complex task that is beyond the scope of this simplified implementation.

    // For now, we will just assume the user is trying to drag the X axis.
    m_selected_axis = GizmoAxis::X;
    m_is_dragging = true;
    return true;
}

void Gizmo::on_mouse_button_up() {
    m_is_dragging = false;
    m_selected_axis = GizmoAxis::None;
}

void Gizmo::on_mouse_move(const Camera& camera, const Matrix4& model_matrix, int x, int y) {
    if (!m_is_dragging) {
        return;
    }

    // This is a simplified implementation. A real implementation would use raycasting
    // and plane intersection to calculate the new position.
    // This is a complex task that is beyond the scope of this simplified implementation.

    // For now, we will just move the object along the X axis.
    // We would need to get the transform law from the matter and update its position.
    // This is not possible from here, so we will need to handle this in the Editor class.
}
