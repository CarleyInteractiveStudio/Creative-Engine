#include "Matrix4.h"
#include <cmath>
#include <cstring>

Matrix4::Matrix4() {
    std::memset(m, 0, sizeof(m));
}

Matrix4 Matrix4::identity() {
    Matrix4 mat;
    mat.m[0][0] = 1;
    mat.m[1][1] = 1;
    mat.m[2][2] = 1;
    mat.m[3][3] = 1;
    return mat;
}

Matrix4 Matrix4::create_translation(const Vector3& translation) {
    Matrix4 mat = identity();
    mat.m[3][0] = translation.x;
    mat.m[3][1] = translation.y;
    mat.m[3][2] = translation.z;
    return mat;
}

Matrix4 Matrix4::create_scale(const Vector3& scale) {
    Matrix4 mat;
    mat.m[0][0] = scale.x;
    mat.m[1][1] = scale.y;
    mat.m[2][2] = scale.z;
    mat.m[3][3] = 1;
    return mat;
}

Matrix4 Matrix4::create_rotation_x(float angle) {
    Matrix4 mat = identity();
    mat.m[1][1] = std::cos(angle);
    mat.m[1][2] = std::sin(angle);
    mat.m[2][1] = -std::sin(angle);
    mat.m[2][2] = std::cos(angle);
    return mat;
}

Matrix4 Matrix4::create_rotation_y(float angle) {
    Matrix4 mat = identity();
    mat.m[0][0] = std::cos(angle);
    mat.m[0][2] = -std::sin(angle);
    mat.m[2][0] = std::sin(angle);
    mat.m[2][2] = std::cos(angle);
    return mat;
}

Matrix4 Matrix4::create_rotation_z(float angle) {
    Matrix4 mat = identity();
    mat.m[0][0] = std::cos(angle);
    mat.m[0][1] = std::sin(angle);
    mat.m[1][0] = -std::sin(angle);
    mat.m[1][1] = std::cos(angle);
    return mat;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

Vector3 Matrix4::operator*(const Vector3& vec) const {
    Vector3 result;
    result.x = vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + m[3][0];
    result.y = vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + m[3][1];
    result.z = vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + m[3][2];
    return result;
}

float* Matrix4::get_data() {
    return &m[0][0];
}

const float* Matrix4::get_const_data() const {
    return &m[0][0];
}
