#pragma once

#include <sead/heap/seadDisposer.h>

namespace pe {

class Menu {
SEAD_SINGLETON_DISPOSER(Menu)
public:
    Menu();

    void draw();
};

} // namespace pe
