#pragma once

#include "Law.h"
#include "Vector3.h"

namespace Creative {

class MaterialColorLaw : public Law {
public:
    MaterialColorLaw(Matter* matter);
    ~MaterialColorLaw() override;

    void OnUpdate(float dt) override;

    Vector3 color;
};

} // namespace Creative
