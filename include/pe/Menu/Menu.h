#pragma once

#include "al/Library/LiveActor/LiveActor.h"
#include "al/Library/Thread/FunctorV0M.h"
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
    MenuCategory mCategories[4];
    int mCurrentCategory = 0;
    bool mIsExpandedCurrentCategory = false;
    int mCurrentComponentInCategory = 0;
    bool mIsFocusedOnCurrentComponent = false;
    ImVec2 mBgSize;
    al::Scene* mScene = nullptr;

    sead::Vector3f mSavedPosition;
    sead::Quatf mSavedQuat;
    bool mIsSavedPos = false;

    int mTimer = 0;

    int getCategoryHeight(int idx) const { return (sCategorySpacing * 2 + sCategoryFontSize) * idx; }
    void updateInput();
    void drawExpandedCategory();
    MenuCategory& getCurrentCategory() { return mCategories[mCurrentCategory]; }

    SEAD_SINGLETON_DISPOSER(Menu)
public:
    Menu();

    void update(al::Scene* scene);
    void draw();
    bool isEnabled() const { return mIsEnabled; }
    void callAction(ActionType type);

    class CallActionFunctor : public al::FunctorBase {
    private:
        Menu* mPtr = nullptr;
        ActionType mType = ActionType::None;

    public:
        CallActionFunctor(Menu* ptr, ActionType type)
            : mPtr(ptr)
            , mType(type)
        {
        }

        void operator()() const override { mPtr->callAction(mType); };
        FunctorBase* clone() const override { return new CallActionFunctor(*this); };

        ~CallActionFunctor() override = default;
    };

    __attribute__((noinline)) void savePosition(al::LiveActor* playerBase);
    __attribute__((noinline)) void loadPosition(al::LiveActor* playerBase);

    static constexpr int sCategoryFontSize = 50;
    static constexpr int sCategorySpacing = 4;
};

} // namespace pe
