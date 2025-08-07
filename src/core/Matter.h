#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Law.h"

namespace Creative {

class Matter {
public:
    std::string m_name;

    Matter();
    ~Matter();

    void OnUpdate(float dt);

    template<typename T>
    T* AddLaw() {
        static_assert(std::is_base_of<Law, T>::value, "T must be a descendant of Law");
        auto law = std::make_unique<T>(this);
        T* ptr = law.get();
        m_laws.push_back(std::move(law));
        return ptr;
    }

    const std::vector<std::unique_ptr<Law>>& GetLaws() const;

    template<typename T>
    T* GetLaw() {
        for (const auto& law : m_laws) {
            if (auto casted = dynamic_cast<T*>(law.get())) {
                return casted;
            }
        }
        return nullptr;
    }

private:
    std::vector<std::unique_ptr<Law>> m_laws;
};

} // namespace Creative
