#pragma once

#include "../core/Matrix4.h"
#include "../core/Vector3.h"

class Camera {
public:
    Camera();

    void set_position(const Vector3& pos);
    Vector3 get_position() const;

    void look_at(const Vector3& target, const Vector3& up);

    Matrix4 get_view_matrix() const;
    Matrix4 get_projection_matrix() const;

    void set_perspective(float fov, float aspect, float near, float far);

private:
    Vector3 position;
    Vector3 forward;
    Vector3 up;
    Vector3 right;

    Matrix4 view_matrix;
    Matrix4 projection_matrix;
};
