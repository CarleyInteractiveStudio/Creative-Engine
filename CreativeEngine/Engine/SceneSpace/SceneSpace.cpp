#include "SceneSpace.h"
#include "Engine/Core/Log.h"

#include <algorithm>

namespace Creative {

SceneSpace::SceneSpace()
{
    Log::Core_Info("SceneSpace created.");
}

SceneSpace::~SceneSpace()
{
    // Clear the vector. The Scope<Matter> will ensure each Matter is destroyed correctly.
    m_Matters.clear();
    Log::Core_Info("SceneSpace destroyed.");
}

void SceneSpace::DestroyMatter(Matter* matter)
{
    // Find the unique_ptr that manages the given raw pointer and erase it from the vector.
    // This will trigger the Matter's destructor.
    auto it = std::remove_if(m_Matters.begin(), m_Matters.end(),
        [&](const Scope<Matter>& m) {
            return m.get() == matter;
        });

    if (it != m_Matters.end())
    {
        m_Matters.erase(it, m_Matters.end());
    }
}

void SceneSpace::Update(float deltaTime)
{
    // Iterate through all Matter objects and call their Update method.
    for (const auto& matter : m_Matters)
    {
        matter->Update(deltaTime);
    }
}

} // namespace Creative
