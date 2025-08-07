#pragma once

#include "Law.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Creative {

class TransformLaw : public Law {
public:
    TransformLaw(Matter* matter);
    ~TransformLaw() override;

    void OnUpdate(float dt) override;

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Matrix4 GetTransform() const;
};

} // namespace Creative
