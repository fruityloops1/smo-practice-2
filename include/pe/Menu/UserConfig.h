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
    ImVec2 mTimerPos = ImVec2(1920.f / 2, 1080.f / 2);
    bool mTimerEnabled = true;
    bool mTimerIsRTA = true;
    float mTimerFontSize = 50;
    TimerHookType mTimerStartType = TimerHookType::ShineGrab;
    TimerHookType mTimerEndType = TimerHookType::ShineGrab;
};

UserConfig*& getConfig();
void saveConfig();
void loadConfig();

} // namespace pe
