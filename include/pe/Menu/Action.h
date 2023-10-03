#pragma once

namespace pe {

enum class ActionType {
    None,
    KillScene,
    SavePosition,
    LoadPosition,
    StartTimer,
    StopTimer,
    ResetTimer,
    NextMofumofuPattern,
    PrevMofumofuPattern,
};

constexpr const char* sActionNames[] {
    "action0", "action1", "action2", "action3", "action4", "action5", "action6", "action7", "action8"
};

} // namespace pe
