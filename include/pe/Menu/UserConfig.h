#pragma once

#include "imgui.h"
#include "pe/Menu/Action.h"
#include "pe/Menu/Timer.h"
#include "pe/Util/Localization.h"

namespace pe {

enum MofumofuPattern : s8 {
    Random,
    Ghost,
    Nose,
    C,
    W,
    J,
    Medal,
    Plane,
    Five,
    Hangman,
    Spanish,
    Siblings,
    Snake,
    Eight,
    Mushroom,
    Z,
    Tetris,
    Ear,
    Bomb,
    Bird,
    L,
    O,
    Star
};

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

    bool mIsBgmDisabled = false;
    bool mIsShineRefreshEnabled = false;
    bool mIsGrayShineRefreshEnabled = false;
    MofumofuPattern mCurPattern = Random;

    struct MofumofuPatternEntry {
        const char* typeStr;
        int target;
        bool reverse;
    };

    constexpr static const MofumofuPatternEntry sPatternEntries[22] = {
        { "Ghost", 0, false }, { "Nose", 0, true }, { "C", 1, false }, { "W", 1, true }, { "J", 2, false }, { "Medal", 2, true }, { "Plane", 3, false }, { "5", 3, true }, { "Hangman", 4, false }, { "Spanish", 4, true },
        { "Siblings", 5, false }, { "Snake", 5, true }, { "8", 6, false }, { "Mushroom", 6, true }, { "Z", 7, false }, { "Tetris", 7, true }, { "Ear", 8, false }, { "Bomb", 8, true }, { "Bird", 9, false }, { "L", 9, true }, { "O", 10, false }, { "Star", 10, true }
    };
};

UserConfig*& getConfig();
void saveConfig();
void loadConfig();

} // namespace pe
