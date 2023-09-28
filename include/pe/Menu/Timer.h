#pragma once

#include "basis/seadTypes.h"
#include "imgui.h"
#include "pe/Menu/IComponent.h"

namespace pe {

enum class TimerHookType {
    GameStart,
    EscapeWire,
    ShineGrab,
    ShineTick
};

class Timer : public IComponent {
    int mFrameTimer = 0;
    s64 mStartTick = 0;
    s64 mEndTick = 0;
    bool mIsRunning = false;

public:
    Timer();

    void start();
    void stop();
    void event(TimerHookType type);

    void draw() override;
};

} // namespace pe
