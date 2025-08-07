#pragma once

namespace Creative {

class Matter;

class Law {
public:
    Law(Matter* matter) : m_matter(matter) {}
    virtual ~Law() = default;

    virtual void OnUpdate(float dt) = 0;

protected:
    Matter* m_matter;
};

} // namespace Creative
