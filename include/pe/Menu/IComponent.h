#pragma once

namespace pe {

class IComponent {
public:
    virtual void draw();
    virtual void update() {}
};

} // namespace pe
