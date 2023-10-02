#pragma once

#include "imgui.h"
#include "pe/Menu/Action.h"
#include "pe/Menu/Timer.h"
#include "pe/Util/Localization.h"

namespace pe {

struct UserConfig {
    PeepaLanguage currentLanguage = PeepaLanguage::English;
    ActionType mDUpBind = ActionType::None;
    ActionType mDDownBind = ActionType::None;
    ActionType mDLeftBind = ActionType::None;
    ActionType mDRightBind = ActionType::None;
    ActionType mQuickMenuBinds[8] { ActionType::None };
    ImVec2 mTimerPos = ImVec2(1600.f / 2, 900.f / 2);
    bool mTimerEnabled = true;
    bool mTimerIsRTA = true;
    float mTimerFontSize = 50;
    TimerHookType mTimerStartType = TimerHookType::ShineGrab;
    TimerHookType mTimerEndType = TimerHookType::ShineGrab;
    bool mInputDisplayEnabled = true;
    ImVec2 mInputDisplayPos = ImVec2(1600.f / 2, 900.f / 2);

    bool mIsGrayShineRefreshEnabled = false;
};

UserConfig*& getConfig();
void saveConfig();
void loadConfig();

} // namespace pe
