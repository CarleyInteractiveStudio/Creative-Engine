#pragma once

#include <memory>

// This file serves as a placeholder for a future, more complex memory management system.
// A real implementation would involve custom allocators, memory pools, and detailed tracking
// to optimize performance and control memory fragmentation in a high-performance game engine.

// For now, we establish conventions using standard C++ smart pointers.

namespace Creative {

// Scoped pointer (unique ownership)
template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// Reference-counted pointer (shared ownership)
template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

} // namespace Creative
