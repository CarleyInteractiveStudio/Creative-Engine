#pragma once

#include "../core/Matrix4.h"
#include "../core/Vector3.h"

class Camera;

enum class GizmoAxis {
    None,
    X,
    Y,
    Z
};

class Gizmo {
public:
    Gizmo();
    ~Gizmo();

    void render(const Camera& camera, const Matrix4& model_matrix);
    bool on_mouse_button_down(const Camera& camera, const Matrix4& model_matrix, int x, int y);
    void on_mouse_button_up();
    void on_mouse_move(const Camera& camera, const Matrix4& model_matrix, int x, int y);

private:
    unsigned int m_shader_program;
    unsigned int m_vao;
    unsigned int m_vbo;
    GizmoAxis m_selected_axis = GizmoAxis::None;
    bool m_is_dragging = false;
};
