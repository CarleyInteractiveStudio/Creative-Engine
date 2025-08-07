#include "MaterialColorLaw.h"

namespace Creative {

MaterialColorLaw::MaterialColorLaw(Matter* matter)
    : Law(matter)
    , color(1.0f, 1.0f, 1.0f)
{
}

MaterialColorLaw::~MaterialColorLaw()
{
}

void MaterialColorLaw::OnUpdate(float dt)
{
}

} // namespace Creative
