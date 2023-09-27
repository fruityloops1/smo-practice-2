#include "pe/Menu/QuickActionMenu.h"
#include "al/Library/Controller/JoyPadUtil.h"
#include "imgui.h"
#include "math/seadVectorFwd.h"
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

void QuickActionMenu::draw()
{
    if (al::isPadHoldPressLeftStick(-1)) {
        mActiveFrames++;

        float progress = float(mActiveFrames) / 25;

        if (mActiveFrames <= 25)
            mLength = easeOutQuad(progress) * 300;

        const ImVec2 center(1920.f / 2, 1080.f / 2);
        const sead::Vector2f& stick = al::getLeftStick(-1);
        const ImVec2 cursorPos(center.x + stick.x * 300, center.y + stick.y * 300);

        float lowestDistance = FLT_MAX;
        int idxLowestDistance = -1;

        for (int i = 0; i < 8; i++) {
            const ImVec2& dir = sActionDirections[i];
            ImVec2 pos(center.x + dir.x * mLength, center.y + dir.y * mLength);
            float d1 = cursorPos.x - pos.x, d2 = cursorPos.y - pos.y;
            float distance = sqrt(d1 * d1 + d2 * d2);
            if (distance < lowestDistance) {
                idxLowestDistance = i;
                lowestDistance = distance;
            }
        }

        for (int i = 0; i < 8; i++) {
            const ImVec2& dir = sActionDirections[i];
            ImVec2 pos(center.x + dir.x * mLength, center.y + dir.y * mLength);

            bool isHovered = idxLowestDistance == i;
            ImU32 circleColor = isHovered ? IM_COL32(156, 26, 26, 156) : IM_COL32(0, 0, 0, 156);
            ImGui::GetForegroundDrawList()->AddCircleFilled(pos, (isHovered ? 70 : 50) * easeOutQuad(progress), circleColor);
        }

        mSelectedActionIdx = idxLowestDistance;

        ImGui::GetForegroundDrawList()->AddCircleFilled(cursorPos, 5, IM_COL32(255, 255, 255, 255));
    } else {
        mSelectedActionIdx = -1;
        mActiveFrames = 0;
    }
}

} // namespace pe
