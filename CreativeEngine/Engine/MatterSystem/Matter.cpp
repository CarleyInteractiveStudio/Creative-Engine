#include "Matter.h"
#include "Engine/Core/Log.h"

namespace Creative {

Matter::Matter(std::string name)
    : m_Name(std::move(name))
{
    Log::Core_Trace("Matter '" + m_Name + "' created.");
}

Matter::~Matter()
{
    // The Scope<Law> (unique_ptr) in the vector will automatically delete the Laws,
    // but we should call their destruction hooks manually first.
    for (const auto& law : m_Laws)
    {
        law->OnDestroy();
    }
    Log::Core_Trace("Matter '" + m_Name + "' destroyed.");
}

void Matter::Update(float deltaTime)
{
    // This is the core of the Matter's behavior: it delegates the update logic
    // to all of its attached Laws.
    for (const auto& law : m_Laws)
    {
        law->OnUpdate(deltaTime);
    }
}

} // namespace Creative
