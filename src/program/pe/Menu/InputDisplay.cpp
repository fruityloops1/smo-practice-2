#include "pe/Menu/InputDisplay.h"
#include "al/Library/Controller/JoyPadUtil.h"
#include "imgui.h"
#include "pe/Menu/UserConfig.h"

namespace pe {

using InputCallback = bool (*)(int port);

static ImU32 makeColor(const ImVec4& color) { return IM_COL32(u8(color.x), u8(color.y), u8(color.z), u8(color.w)); }

static void drawButton(const ImVec2& pos, InputCallback callback, float radius = 8, ImU32 color = makeColor(getInputDisplayColor(getConfig()->mInputDisplayButtonColor)), ImU32 pressedColor = makeColor(getInputDisplayColor(getConfig()->mInputDisplayButtonPressedColor)))
{
    const ImU32 col = callback(-1) ? pressedColor : color;
    ImGui::GetForegroundDrawList()->AddCircleFilled(pos, radius, col, 16);
}

static void drawButtonRect(const ImVec2& pos, InputCallback callback, ImU32 color = makeColor(getInputDisplayColor(getConfig()->mInputDisplayButtonColor)), ImU32 pressedColor = makeColor(getInputDisplayColor(getConfig()->mInputDisplayButtonPressedColor)))
{
    const ImU32 col = callback(-1) ? pressedColor : color;
    const ImVec2 min(pos.x - 13, pos.y - 6);
    const ImVec2 max(pos.x + 13, pos.y + 6);
    ImGui::GetForegroundDrawList()->AddRectFilled(min, max, col, 10.0f);
}

void InputDisplay::draw()
{
    if (!getConfig()->mInputDisplayEnabled)
        return;

    const sead::Vector2f leftStick = al::getLeftStick(-1);
    const sead::Vector2f rightStick = al::getRightStick(-1);

    ImVec2 pos = getConfig()->mInputDisplayPos;
    pos.x -= 200;
    pos.y -= 100;

    if (getConfig()->mInputDisplayBackColor != InputDisplayColor::None) {
        ImVec4 color = getInputDisplayColor(getConfig()->mInputDisplayBackColor);
        color.w = 128;
        ImGui::GetForegroundDrawList()->AddRectFilled({ pos.x - 50, pos.y - 100 }, { pos.x + 200, pos.y + 100 }, makeColor(color), 20);
    }

    ImGui::GetForegroundDrawList()->AddCircle(pos, 25, makeColor(getInputDisplayColor(getConfig()->mInputDisplayRingColor)), 0, 2);
    ImVec2 leftPos = { pos.x + leftStick.x * 30, pos.y - leftStick.y * 30 };
    drawButton(leftPos, al::isPadHoldPressLeftStick, 16, makeColor(getInputDisplayColor(getConfig()->mInputDisplayStickColor)));

    pos.x += 40;
    pos.y += 30;
    drawButton(pos, al::isPadHoldUp);
    pos.y += 30;
    drawButton(pos, al::isPadHoldDown);
    pos.x -= 15;
    pos.y -= 15;
    drawButton(pos, al::isPadHoldLeft);
    pos.x += 30;
    drawButton(pos, al::isPadHoldRight);

    pos.x += 60;
    ImGui::GetForegroundDrawList()->AddCircle(pos, 25, makeColor(getInputDisplayColor(getConfig()->mInputDisplayRingColor)), 0, 2);
    ImVec2 rightPos = { pos.x + rightStick.x * 30, pos.y - rightStick.y * 30 };
    drawButton(rightPos, al::isPadHoldPressRightStick, 16, makeColor(getInputDisplayColor(getConfig()->mInputDisplayStickColor)));

    pos.x += 40;
    pos.y -= 60;
    drawButton(pos, al::isPadHoldX);
    pos.y += 30;
    drawButton(pos, al::isPadHoldB);
    pos.x -= 15;
    pos.y -= 15;
    drawButton(pos, al::isPadHoldY);
    pos.x += 30;
    drawButton(pos, al::isPadHoldA);

    pos.y -= 10;
    pos.x -= 75;
    drawButton(pos, al::isPadHoldPlus, 5);
    pos.x -= 40;
    drawButton(pos, al::isPadHoldMinus, 5);

    pos = getConfig()->mInputDisplayPos;
    pos.x -= 200;
    pos.y -= 160;
    drawButtonRect(pos, al::isPadHoldL);
    pos.y -= 16;
    drawButtonRect(pos, al::isPadHoldZL);
    pos.x += 155;
    drawButtonRect(pos, al::isPadHoldZR);
    pos.y += 16;
    drawButtonRect(pos, al::isPadHoldR);
}

} // namespace pe
