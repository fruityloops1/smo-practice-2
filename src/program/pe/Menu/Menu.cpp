#include "pe/Menu/Menu.h"
#include "al/Library/Controller/JoyPadUtil.h"
#include "imgui.h"
#include "pe/Menu/MenuComponent.h"
#include "pe/Menu/UserConfig.h"
#include <algorithm>

namespace pe {

sead::Heap*& getMenuHeap()
{
    static sead::Heap* sHeap { nullptr };
    return sHeap;
}

SEAD_SINGLETON_DISPOSER_IMPL(Menu)

Menu::Menu()
{
    pe::loadConfig();

// make these be localized id thingies instead
    mCategories[0].name = "";
    mCategories[0].components.allocBuffer(2, nullptr);
    mCategories[1].name = "Balls";
    mCategories[1].components.allocBuffer(2, nullptr);
    mCategories[2].name = "Stuff";
    mCategories[2].components.allocBuffer(2, nullptr);
}

void Menu::draw()
{
    updateInput();

    mBgSize = ImVec2(0, 0);
    for (int i = 0; i < IM_ARRAYSIZE(mCategories); i++) {
        ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(sCategoryFontSize, FLT_MAX, 0.f, mCategories[i].name);

        int width = sCategorySpacing + textSize.x + sCategorySpacing;
        mBgSize.x = std::max(mBgSize.x, (float)width);
    }
    mBgSize.y += getCategoryHeight(IM_ARRAYSIZE(mCategories));

    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, 0), mBgSize, IM_COL32(0, 0, 0, 128));
    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, getCategoryHeight(mCurrentCategory)), ImVec2(mBgSize.x, getCategoryHeight(mCurrentCategory + 1)), IM_COL32(255, 255, 255, 76));

    ImVec2 size = ImVec2(0, 0);
    for (int i = 0; i < IM_ARRAYSIZE(mCategories); i++) {
        ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(sCategoryFontSize, FLT_MAX, 0.f, mCategories[i].name);
        size.y += sCategorySpacing;

        ImGui::GetForegroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], sCategoryFontSize, ImVec2(size.x + sCategorySpacing, size.y), IM_COL32(255, 255, 255, 255), mCategories[i].name);

        size.y += textSize.y;
        size.y += sCategorySpacing;
    }

    if (mIsExpandedCurrentCategory)
        drawExpandedCategory();
}

void Menu::drawExpandedCategory()
{
    auto& cat = mCategories[mCurrentCategory];
    int subX = 0, subY = 0;
    int y = getCategoryHeight(mCurrentCategory);

    for (MenuComponent& component : cat.components) {
        ImVec2 size = component.getSize();
        subX = std::max((float)subX, size.x);
        subY += size.y;
    }

    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(mBgSize.x, y), ImVec2(mBgSize.x + subX, y + subY), IM_COL32(0, 0, 0, 128));

    subY = 0;
    {
        int i = 0;

        for (MenuComponent& component : cat.components) {
            ImVec2 size = component.getSize();
            ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(mBgSize.x, y + subY), ImVec2(mBgSize.x + subX, y + subY + size.y), IM_COL32(0, 0, 0, 128));
            if (mCurrentComponentInCategory == i) {
                ImU32 color = mIsFocusedOnCurrentComponent ? IM_COL32(255, 60, 60, 76) : IM_COL32(255, 255, 255, 76);
                ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(mBgSize.x, y + subY), ImVec2(mBgSize.x + subX, y + subY + size.y), color);
            }
            component.draw(ImVec2(mBgSize.x, y + subY));

            subY += size.y;

            i++;
        }
    }
}

void Menu::updateInput()
{
    if (!mIsExpandedCurrentCategory) {
        if (al::isPadTriggerDown(-1)) {
            mCurrentCategory++;
        } else if (al::isPadTriggerUp(-1)) {
            mCurrentCategory--;
        }

        if (al::isPadTriggerRight(-1)) {
            mCurrentComponentInCategory = 0;
            mIsExpandedCurrentCategory = true;
        }
    } else {
        if (!mIsFocusedOnCurrentComponent) {
            if (al::isPadTriggerDown(-1)) {
                mCurrentComponentInCategory++;
            } else if (al::isPadTriggerUp(-1)) {
                mCurrentComponentInCategory--;
            } else if (al::isPadTriggerLeft(-1)) {
                mIsExpandedCurrentCategory = false;
            }
        }

        if (al::isPadTriggerLeftStick(-1))
            mIsFocusedOnCurrentComponent = !mIsFocusedOnCurrentComponent;

        if (mCurrentComponentInCategory < 0)
            mCurrentComponentInCategory = 0;
        if (mCurrentComponentInCategory >= getCurrentCategory().components.size())
            mCurrentComponentInCategory = getCurrentCategory().components.size() - 1;
    }

    if (mCurrentCategory >= IM_ARRAYSIZE(mCategories))
        mCurrentCategory = IM_ARRAYSIZE(mCategories) - 1;
    if (mCurrentCategory < 0)
        mCurrentCategory = 0;
}

} // namespace pe
