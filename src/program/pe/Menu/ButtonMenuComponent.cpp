#include "pe/Menu/ButtonMenuComponent.h"
#include "al/Library/Controller/JoyPadUtil.h"
#include "pe/Menu/Menu.h"

namespace pe {

ImVec2 ButtonMenuComponent::getSize() const
{
    ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(mFontSize, FLT_MAX, 0.f, mText);
    ImVec2 size(textSize.x + Menu::sCategorySpacing * 2, textSize.y + Menu::sCategorySpacing * 2);
    return size;
}

void ButtonMenuComponent::draw(const ImVec2& at)
{
    if (al::isPadTriggerPressLeftStick(-1)) {
        (*mFunctor)();
    }
    ImGui::GetForegroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], mFontSize, ImVec2(at.x + Menu::sCategorySpacing, at.y + Menu::sCategorySpacing), IM_COL32(255, 255, 255, 255), mText);
}

} // namespace pe
