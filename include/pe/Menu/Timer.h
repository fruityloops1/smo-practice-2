#pragma once

#include "basis/seadTypes.h"
#include "imgui.h"
#include "pe/Menu/IComponent.h"

namespace pe {

enum class TimerHookType {
    None,
    ShineGrab,
    ShineTick,
    GameStart,
    EscapeWire,
};

class Timer : public IComponent {
    int mFrameTimer = 0;
    s64 mStartTick = 0;
    s64 mEndTick = 0;
    bool mIsRunning = false;
    s64 mShowSplitTick = 0;
    int mFrames = 0;

public:
    Timer();

    void start();
    void stop();
    void reset();
    void event(TimerHookType type);
    void showSplit();

    void draw() override;

    static Timer* sInstance;
};

} // namespace pe
