#pragma once

#include "imgui.h"
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
    bool mIsExpandedCurrentCategory = false;
    int mCurrentComponentInCategory = 0;
    bool mIsFocusedOnCurrentComponent = false;
    ImVec2 mBgSize;

    int getCategoryHeight(int idx) const { return (sCategorySpacing * 2 + sCategoryFontSize) * idx; }
    void updateInput();
    void drawExpandedCategory();
    MenuCategory& getCurrentCategory() { return mCategories[mCurrentCategory]; }

    SEAD_SINGLETON_DISPOSER(Menu)
public:
    Menu();

    void draw();

    static constexpr int sCategoryFontSize = 100;
    static constexpr int sCategorySpacing = 4;
};

} // namespace pe
