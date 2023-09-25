#include "pe/Menu/Menu.h"
#include "al/Library/Controller/JoyPadUtil.h"
#include "imgui.h"
#include "pe/Menu/UserConfig.h"

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

    mCategories[0].name = "Settings";
    mCategories[0].components.allocBuffer(2, nullptr);
    mCategories[1].name = "Balls";
    mCategories[1].components.allocBuffer(2, nullptr);
    mCategories[2].name = "Stuff";
    mCategories[2].components.allocBuffer(2, nullptr);
}

void Menu::draw()
{
    updateInput();

    ImVec2 bgSize(0, 0);
    for (int i = 0; i < IM_ARRAYSIZE(mCategories); i++) {
        ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(sCategoryFontSize, FLT_MAX, 0.f, mCategories[i].name);

        int width = sCategorySpacing + textSize.x + sCategorySpacing;
        if (width > bgSize.x)
            bgSize.x = width;
    }
    bgSize.y += getCategoryHeight(IM_ARRAYSIZE(mCategories));

    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, 0), bgSize, IM_COL32(0, 0, 0, 128));
    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, getCategoryHeight(mCurrentCategory)), ImVec2(bgSize.x, getCategoryHeight(mCurrentCategory + 1)), IM_COL32(255, 255, 255, 76));

    bgSize = ImVec2(0, 0);
    for (int i = 0; i < IM_ARRAYSIZE(mCategories); i++) {
        ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(sCategoryFontSize, FLT_MAX, 0.f, mCategories[i].name);
        bgSize.y += sCategorySpacing;

        ImGui::GetForegroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], sCategoryFontSize, ImVec2(bgSize.x + sCategorySpacing, bgSize.y), IM_COL32(255, 255, 255, 255), mCategories[i].name);

        bgSize.y += textSize.y;
        bgSize.y += sCategorySpacing;
    }

    // ImGui::GetForegroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], 50, ImVec2(200, 200), IM_COL32(0, 0, 255, 255), "Hello, World!\nハロー、ワールド！");
}

void Menu::updateInput()
{
    if (al::isPadTriggerDown(-1)) {
        mCurrentCategory++;
    } else if (al::isPadTriggerUp(-1)) {
        mCurrentCategory--;
    }

    if (mCurrentCategory >= IM_ARRAYSIZE(mCategories))
        mCurrentCategory = IM_ARRAYSIZE(mCategories) - 1;
    if (mCurrentCategory < 0)
        mCurrentCategory = 0;
}

} // namespace pe
