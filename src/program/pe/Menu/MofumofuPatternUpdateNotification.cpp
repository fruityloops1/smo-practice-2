#include "pe/Menu/MofumofuPatternUpdateNotification.h"
#include "imgui.h"
#include "pe/Menu/UserConfig.h"
#include "pe/Util/Localization.h"
#include <cstdio>

namespace pe {

MofumofuPatternUpdateNotification* MofumofuPatternUpdateNotification::sInstance = nullptr;

void MofumofuPatternUpdateNotification::draw()
{
    if (mUpdateFrames > 0) {
        int cur = getConfig()->mCurPattern;
        char buffer[96] { 0 };
        snprintf(buffer, 96, "%s: %s", pe::getLocalizedString("mofumofupattern"), cur == 0 ? "Random" : UserConfig::sPatternEntries[cur - 1].typeStr);
        ImVec2 at(1600.f / 2, 120.f);
        ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(50, FLT_MAX, 0.f, buffer);
        at.x -= textSize.x / 2;
        at.y -= textSize.y / 2;

        ImGui::GetForegroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], 50, at, IM_COL32(255, 255, 255, mUpdateFrames < 31 ? (1 / (30 - mUpdateFrames)) * 255 : 255), buffer);
        mUpdateFrames--;
    }
}

} // namespace pe
