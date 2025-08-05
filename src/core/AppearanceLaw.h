#pragma once

#include "Law.h"
#include "Vector3.h"

namespace Creative {

class AppearanceLaw : public Law {
public:
    AppearanceLaw(Matter* matter);
    ~AppearanceLaw() override;

    void OnUpdate(float dt) override;

    Vector3 color;
};

} // namespace Creative
