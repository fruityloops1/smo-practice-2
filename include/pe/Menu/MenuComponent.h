#pragma once

#include "imgui.h"

namespace pe {

class MenuComponent {
protected:
    bool mIsFocused = false;
    bool mIsHovered = false;

public:
    virtual ImVec2 getSize() const;
    virtual void draw(const ImVec2& at);
    virtual bool canHaveFocus() const { return false; }

    void setIsFocused(bool isFocused) { mIsFocused = isFocused; }
    void setIsHovered(bool isHovered) { mIsHovered = isHovered; }
};

} // namespace pe
