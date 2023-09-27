#pragma once

namespace pe {

enum class ActionType {
    None,
    KillScene,
    SavePosition,
    LoadPosition
};

static constexpr const char* sActionNames[] {
        "action0", "action1", "action2", "action3"
    };

} // namespace pe
