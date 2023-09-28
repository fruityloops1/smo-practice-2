#pragma once

#include "al/Library/Controller/JoyPadUtil.h"
#include "imgui.h"
#include "pe/Menu/Menu.h"
#include "pe/Menu/MenuComponent.h"
#include "pe/Util/Localization.h"
#include <algorithm>
#include <limits>
#include <type_traits>

namespace pe {

template <typename IntType>
class IntMenuComponent : public MenuComponent {
    IntType* mValue = nullptr;
    const char* mTitle = nullptr;
    bool mLocalized = false;
    int mFontSize = 35;
    IntType mLowerLimit = 0, mUpperLimit = std::numeric_limits<IntType>::max();

public:
    IntMenuComponent(IntType* value, const char* title, IntType lowerLimit = 0, IntType upperLimit = std::numeric_limits<IntType>::max(), bool localized = false, int fontSize = 35)
        : mValue(value)
        , mTitle(title)
        , mLocalized(localized)
        , mFontSize(fontSize)
        , mLowerLimit(lowerLimit)
        , mUpperLimit(upperLimit)
    {
    }

#define ENUM_MENU_COMPONENT_BUFFER                                            \
    const char* title = mLocalized ? pe::getLocalizedString(mTitle) : mTitle; \
    size_t bufSize = snprintf(nullptr, 0, "%s: %d", title, int(*mValue));     \
    char buffer[bufSize + 1] { 0 };                                           \
    snprintf(buffer, bufSize + 1, "%s: %d", title, int(*mValue));

    ImVec2 getSize() const override
    {
        ENUM_MENU_COMPONENT_BUFFER;

        ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(mFontSize, FLT_MAX, 0.f, buffer);
        ImVec2 size(textSize.x + Menu::sCategorySpacing * 2, textSize.y + Menu::sCategorySpacing * 2);
        return size;
    }

    void draw(const ImVec2& at) override
    {
        if (mIsFocused) {
            if (al::isPadTriggerLeft(-1))
                (*mValue)--;
            else if (al::isPadTriggerRight(-1))
                (*mValue)++;

            if (int(*mValue) < mLowerLimit)
                *mValue = mLowerLimit;
            if (int(*mValue) > mUpperLimit)
                *mValue = mUpperLimit - 1;
        }

        ENUM_MENU_COMPONENT_BUFFER;
        ImGui::GetForegroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], mFontSize, ImVec2(at.x + Menu::sCategorySpacing, at.y + Menu::sCategorySpacing), IM_COL32(255, 255, 255, 255), buffer);
    }

#undef ENUM_MENU_COMPONENT_BUFFER

    bool canHaveFocus() const override
    {
        return true;
    }
};

} // namespace pe
