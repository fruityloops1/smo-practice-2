#pragma once

namespace pe {

enum class ActionType {
    None,
    KillScene,
    PrevScene,
    SavePosition,
    LoadPosition,
    StartTimer,
    StopTimer,
    ResetTimer,
    NextMofumofuPattern,
    PrevMofumofuPattern,
    LifeMaxUp,
    HealMario,
    Add1000Coin,
    Sub1000Coin
};

constexpr const char* sActionNames[] {
    "action0", "action1", "action2", "action3", "action4", "action5", "action6", "action7", "action8", "action9", "action10", "action11", "action12", "action13"
};

} // namespace pe
