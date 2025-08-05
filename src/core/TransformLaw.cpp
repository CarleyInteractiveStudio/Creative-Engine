#include "TransformLaw.h"

namespace Creative {

TransformLaw::TransformLaw(Matter* matter)
    : Law(matter)
    , position(0.0f, 0.0f, 0.0f)
    , rotation(0.0f, 0.0f, 0.0f)
    , scale(1.0f, 1.0f, 1.0f)
{
}

TransformLaw::~TransformLaw()
{
}

void TransformLaw::OnUpdate(float dt)
{
}

Matrix4 TransformLaw::GetTransform() const
{
    Matrix4 translation = Matrix4::create_translation(position);
    Matrix4 rotation_x = Matrix4::create_rotation_x(rotation.x);
    Matrix4 rotation_y = Matrix4::create_rotation_y(rotation.y);
    Matrix4 rotation_z = Matrix4::create_rotation_z(rotation.z);
    Matrix4 scale_matrix = Matrix4::create_scale(scale);

    return translation * rotation_x * rotation_y * rotation_z * scale_matrix;
}

} // namespace Creative
