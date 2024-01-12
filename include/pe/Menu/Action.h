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
    HealMario
};

constexpr const char* sActionNames[] {
    "action0", "action1", "action2", "action3", "action4", "action5", "action6", "action7", "action8", "action9", "action10", "action11"
};

} // namespace pe
