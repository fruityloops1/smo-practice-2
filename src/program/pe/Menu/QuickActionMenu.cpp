#include "pe/Menu/QuickActionMenu.h"
#include "al/Library/Controller/JoyPadUtil.h"
#include "imgui.h"
#include "math/seadVectorFwd.h"
#include "pe/Menu/Action.h"
#include "pe/Menu/Menu.h"
#include "pe/Menu/UserConfig.h"
#include "pe/Util/Localization.h"
#include <cstdio>
#include <math.h>

namespace pe {

const ImVec2 sActionDirections[] {
    ImVec2(0, -1),
    ImVec2(sqrt(2) / 2, -sqrt(2) / 2),
    ImVec2(1, 0),
    ImVec2(sqrt(2) / 2, sqrt(2) / 2),
    ImVec2(0, 1),
    ImVec2(-sqrt(2) / 2, sqrt(2) / 2),
    ImVec2(-1, 0),
    ImVec2(-sqrt(2) / 2, -sqrt(2) / 2),
};

static float easeInSine(float t) { return 1.5707963 * t; }
static float easeOutQuad(float t) { return 1 - (1 - t) * (1 - t); }

static float calcDistance(const ImVec2& vec1, const ImVec2& vec2)
{
    float d1 = vec1.x - vec2.x, d2 = vec1.y - vec2.y;
    return sqrtf(d1 * d1 + d2 * d2);
}

void QuickActionMenu::draw()
{
    if (mMenu.isEnabled())
        return;

    if (mIsRetreating && mActiveFrames <= 0)
        mIsRetreating = false;
    if (al::isPadHoldPressLeftStick(-1) || mIsRetreating) {
    draw:
        if (mIsRetreating)
            mActiveFrames--;
        else
            mActiveFrames++;

        float progress = float(mActiveFrames <= 25 ? mActiveFrames : 25) / 25;

        if (mActiveFrames <= 25)
            mLength = easeOutQuad(progress) * 300;

        const ImVec2 center(1920.f / 2, 1080.f / 2);
        const sead::Vector2f& stick = al::getLeftStick(-1);
        const ImVec2 cursorPos(center.x + stick.x * 300, center.y + -stick.y * 300);

        float lowestDistance = FLT_MAX;
        int idxLowestDistance = -1;

        if (fabs(stick.x) + fabs(stick.y) > .2)
            for (int i = 0; i < 8; i++) {
                const ImVec2& dir = sActionDirections[i];
                ImVec2 pos(center.x + dir.x * mLength, center.y + dir.y * mLength);
                float distance = calcDistance(cursorPos, pos);
                if (distance < lowestDistance) {
                    idxLowestDistance = i;
                    lowestDistance = distance;
                }
            }

        for (int i = 0; i < 8; i++) {
            const ImVec2& dir = sActionDirections[i];
            const ImVec2 pos(center.x + dir.x * mLength, center.y + dir.y * mLength);

            bool isHovered = idxLowestDistance == i && !mIsRetreating;
            ImU32 circleColor = isHovered ? IM_COL32(156, 26, 26, 156) : IM_COL32(0, 0, 0, 156);
            ImGui::GetForegroundDrawList()->AddCircleFilled(pos, (isHovered ? 70 : 50) * easeOutQuad(progress), circleColor);

            float fontSize = 1 + progress * (isHovered ? 40 : 14);
            char buffer[8] { 0 };
            snprintf(buffer, 8, "action%d", int(getConfig()->mQuickMenuBinds[i]));
            const char* str = pe::getLocalizedString(buffer);
            const ImVec2 size = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(fontSize, FLT_MAX, 0.f, str);

            ImGui::GetForegroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], fontSize, ImVec2(pos.x - size.x / 2, pos.y - size.y / 2), IM_COL32(255, 255, 255, 255), str);
        }

        if (!mIsRetreating) {
            ImGui::GetForegroundDrawList()->AddCircleFilled(cursorPos, 5, IM_COL32(255, 255, 255, 255));
            mSelectedActionIdx = idxLowestDistance;
        } else
            mSelectedActionIdx = -1;
    } else {
        if (!mIsRetreating && mActiveFrames > 0) {
            if (mActiveFrames > 25)
                mActiveFrames = 25;
            mIsRetreating = true;
            if (mSelectedActionIdx != -1)
                mMenu.callAction(getConfig()->mQuickMenuBinds[mSelectedActionIdx]);
            goto draw; // sorry
        }
        mSelectedActionIdx = -1;
    }
}

} // namespace pe
