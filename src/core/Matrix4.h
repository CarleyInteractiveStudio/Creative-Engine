#pragma once

#include "Vector3.h"

struct Matrix4 {
    float m[4][4];

    Matrix4();

    static Matrix4 identity();
    static Matrix4 create_translation(const Vector3& translation);
    static Matrix4 create_scale(const Vector3& scale);
    static Matrix4 create_rotation_x(float angle);
    static Matrix4 create_rotation_y(float angle);
    static Matrix4 create_rotation_z(float angle);

    Matrix4 operator*(const Matrix4& other) const;
    Vector3 operator*(const Vector3& vec) const;

    float* get_data();
    const float* get_const_data() const;
};
