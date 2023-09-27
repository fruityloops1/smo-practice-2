#pragma once

#include "al/Project/Scene/SceneCreator.h"
#include "container/seadPtrArray.h"
#include "imgui.h"
#include "math/seadQuat.h"
#include "pe/Menu/Action.h"
#include "pe/Menu/IComponent.h"
#include <sead/container/seadPtrArray.h>
#include <sead/heap/seadDisposer.h>
#include <sead/heap/seadHeap.h>
#include <sead/math/seadVector.h>

namespace pe {

sead::Heap*& getMenuHeap();

class MenuComponent;

struct MenuCategory {
    const char* name;
    sead::PtrArray<MenuComponent> components;
};

class Menu {
    bool mIsEnabled = true;
    sead::PtrArray<IComponent> mComponents;
    MenuCategory mCategories[3];
    int mCurrentCategory = 0;
    bool mIsExpandedCurrentCategory = false;
    int mCurrentComponentInCategory = 0;
    bool mIsFocusedOnCurrentComponent = false;
    ImVec2 mBgSize;
    al::Scene* mScene = nullptr;

    sead::Vector3f mSavedPosition;
    sead::Quatf mSavedQuat;

    int mTimer = 0;

    int getCategoryHeight(int idx) const { return (sCategorySpacing * 2 + sCategoryFontSize) * idx; }
    void updateInput();
    void drawExpandedCategory();
    MenuCategory& getCurrentCategory() { return mCategories[mCurrentCategory]; }
    void callAction(ActionType type);

    void ball() { mCurrentComponentInCategory = 0; }

    SEAD_SINGLETON_DISPOSER(Menu)
public:
    Menu();

    void update(al::Scene* scene);
    void draw();
    bool isEnabled() const { return mIsEnabled; }

    static constexpr int sCategoryFontSize = 50;
    static constexpr int sCategorySpacing = 4;
};

} // namespace pe
