#pragma once

#include "pe/Menu/IComponent.h"

namespace pe {

class Menu;
class QuickActionMenu : public IComponent {
    Menu& mMenu;
    int mActiveFrames = 0;
    float mLength = 0;
    int mSelectedActionIdx = -1;

public:
    QuickActionMenu(Menu& menu)
        : mMenu(menu)
    {
    }

    void draw() override;
};

} // namespace pe
