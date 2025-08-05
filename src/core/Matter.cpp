#include "Matter.h"

namespace Creative {

Matter::Matter()
{
}

Matter::~Matter()
{
}

void Matter::OnUpdate(float dt)
{
    for (const auto& law : m_laws) {
        law->OnUpdate(dt);
    }
}

} // namespace Creative
