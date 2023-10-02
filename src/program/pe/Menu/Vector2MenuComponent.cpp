#include "pe/Menu/Vector2MenuComponent.h"
#include "al/Library/Controller/JoyPadUtil.h"
#include "pe/Menu/Menu.h"
#include "pe/Util/Localization.h"
#include <algorithm>

namespace pe {

ImVec2 Vector2MenuComponent::getSize() const
{
    ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(mFontSize, FLT_MAX, 0.f, mLocalized ? pe::getLocalizedString(mText) : mText);
    ImVec2 size(textSize.x + Menu::sCategorySpacing * 2, textSize.y + Menu::sCategorySpacing * 2);
    return size;
}

void Vector2MenuComponent::draw(const ImVec2& at)
{
    if (mIsFocused) {
        const sead::Vector2f& stick = al::getLeftStick(-1);
        mValue->x += stick.x;
        mValue->y -= stick.y;
        if (mMin.x != FLT_MAX) {
            mValue->x = std::clamp(mValue->x, mMin.x, mMax.x);
            mValue->y = std::clamp(mValue->y, mMin.y, mMax.y);
        }
    }

    ImGui::GetForegroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], mFontSize, ImVec2(at.x + Menu::sCategorySpacing, at.y + Menu::sCategorySpacing), IM_COL32(255, 255, 255, 255), mLocalized ? pe::getLocalizedString(mText) : mText);
}

} // namespace pe
