#include "Matter.h"

namespace Creative {

Matter::Matter()
    : m_name("Matter")
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

const std::vector<std::unique_ptr<Law>>& Matter::GetLaws() const
{
    return m_laws;
}

} // namespace Creative
