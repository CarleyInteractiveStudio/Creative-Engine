#include "AppearanceLaw.h"

namespace Creative {

AppearanceLaw::AppearanceLaw(Matter* matter)
    : Law(matter)
    , color(1.0f, 1.0f, 1.0f)
{
}

AppearanceLaw::~AppearanceLaw()
{
}

void AppearanceLaw::OnUpdate(float dt)
{
}

} // namespace Creative
