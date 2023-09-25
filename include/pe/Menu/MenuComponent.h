#pragma once

#include "imgui.h"

namespace pe {

class MenuComponent {
public:
    virtual ImVec2 getSize() const;
    virtual void draw(const ImVec2& at);
};

} // namespace pe
