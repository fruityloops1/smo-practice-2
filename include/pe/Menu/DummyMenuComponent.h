#pragma once

#include "pe/Menu/MenuComponent.h"

namespace pe {

class DummyMenuComponent : public MenuComponent {
public:
    ImVec2 getSize() const override { return ImVec2(200, 50); };
    void draw(const ImVec2& at) override { }
};

} // namespace pe
