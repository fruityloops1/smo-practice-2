#pragma once

#include <sead/container/seadPtrArray.h>
#include <sead/heap/seadDisposer.h>
#include <sead/heap/seadHeap.h>

namespace pe {

sead::Heap*& getMenuHeap();

class MenuComponent;

struct MenuCategory {
    const char* name;
    sead::PtrArray<MenuComponent> components;
};

class Menu {
    MenuCategory mCategories[3];
    int mCurrentCategory = 0;

    int getCategoryHeight(int idx) const { return (sCategorySpacing * 2 + sCategoryFontSize) * idx; }
    void updateInput();

    SEAD_SINGLETON_DISPOSER(Menu)
public:
    Menu();

    void draw();

    static constexpr int sCategoryFontSize = 100;
    static constexpr int sCategorySpacing = 4;
};

} // namespace pe
