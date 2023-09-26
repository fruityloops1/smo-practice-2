#pragma once

#include "al/Library/Controller/JoyPadUtil.h"
#include "imgui.h"
#include "pe/Menu/Menu.h"
#include "pe/Menu/MenuComponent.h"
#include "pe/Util/Localization.h"
#include <algorithm>

namespace pe {

template <typename T>
class EnumMenuComponent : public MenuComponent {
    T* mValue = nullptr;
    const char* const* mEnumValues = nullptr;
    int mNumEnumValues = 0;
    const char* mTitle = nullptr;
    bool mLocalized = false;
    int mFontSize = 35;

public:
    template <int N>
    EnumMenuComponent(T* value, const char* const (&values)[N], const char* title, bool localized = false, int fontSize = 35)
        : mValue(value)
        , mEnumValues(values)
        , mNumEnumValues(N)
        , mTitle(title)
        , mLocalized(localized)
        , mFontSize(fontSize)
    {
    }

#define ENUM_MENU_COMPONENT_BUFFER                                            \
    const char* curEnumValue = mEnumValues[int(*mValue)];                     \
    if (mLocalized)                                                           \
        curEnumValue = pe::getLocalizedString(curEnumValue);                  \
    const char* title = mLocalized ? pe::getLocalizedString(mTitle) : mTitle; \
    char buffer[strlen(title) + 2 + strlen(curEnumValue) + 1] { 0 };          \
    strcpy(buffer, title);                                                    \
    strcat(buffer, ": ");                                                     \
    strcat(buffer, curEnumValue)

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

            if (int(*mValue) < 0)
                *mValue = 0;
            if (int(*mValue) >= mNumEnumValues)
                *mValue = mNumEnumValues - 1;
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
