#include "Camera.h"
#include <cmath>

Camera::Camera() {
    position = Vector3(0, 0, 0);
    forward = Vector3(0, 0, -1);
    up = Vector3(0, 1, 0);
    right = Vector3(1, 0, 0);
    view_matrix = Matrix4::identity();
    projection_matrix = Matrix4::identity();
}

void Camera::set_position(const Vector3& pos) {
    position = pos;
}

Vector3 Camera::get_position() const {
    return position;
}

void Camera::look_at(const Vector3& target, const Vector3& up_dir) {
    forward = target - position;
    forward.normalize();

    right = up_dir.operator+(forward); // A bit of a hack to get a perpendicular vector
    right.normalize();

    up = right.operator+(forward);
    up.normalize();

    view_matrix.m[0][0] = right.x;
    view_matrix.m[1][0] = right.y;
    view_matrix.m[2][0] = right.z;
    view_matrix.m[0][1] = up.x;
    view_matrix.m[1][1] = up.y;
    view_matrix.m[2][1] = up.z;
    view_matrix.m[0][2] = -forward.x;
    view_matrix.m[1][2] = -forward.y;
    view_matrix.m[2][2] = -forward.z;
    view_matrix.m[3][0] = -right.dot(position);
    view_matrix.m[3][1] = -up.dot(position);
    view_matrix.m[3][2] = forward.dot(position);
}

Matrix4 Camera::get_view_matrix() const {
    return view_matrix;
}

Matrix4 Camera::get_projection_matrix() const {
    return projection_matrix;
}

void Camera::set_perspective(float fov, float aspect, float near, float far) {
    float tan_half_fov = std::tan(fov / 2.0f);
    projection_matrix.m[0][0] = 1.0f / (aspect * tan_half_fov);
    projection_matrix.m[1][1] = 1.0f / tan_half_fov;
    projection_matrix.m[2][2] = -(far + near) / (far - near);
    projection_matrix.m[2][3] = -1.0f;
    projection_matrix.m[3][2] = -(2.0f * far * near) / (far - near);
    projection_matrix.m[3][3] = 0.0f;
}
