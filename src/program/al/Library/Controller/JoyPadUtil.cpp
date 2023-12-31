#include "al/Library/Controller/JoyPadUtil.h"

namespace al {

sead::ControllerBase* getController_(s32 port)
{
    return al::isValidReplayController(port) ? getReplayController(port) : sead::ControllerMgr::instance()->getController(port);
}

sead::ControllerBase* getController(s32 port)
{
    if (port == -1) {
        port = getMainControllerPort();
    }

    return getController_(port);
}

bool isPadTrigger(s32 port, s32 button)
{
    return getController(port)->isTrig(button);
}

bool isPadTrigger1(s32 port)
{
    return isPadTrigger(port, 1 << 7);
}

bool isPadTrigger2(s32 port)
{
    return isPadTrigger(port, 1 << 6);
}

bool isPadTriggerPressLeftStick(s32 port)
{
    return isPadTrigger1(port);
}

bool isPadTriggerA(s32 port)
{
    return isPadTrigger(port, 1);
}

bool isPadTriggerUp(s32 port)
{
    return isPadTrigger(port, 1 << 16);
}

bool isPadTriggerDown(s32 port)
{
    return isPadTrigger(port, 1 << 17);
}

bool isPadTriggerLeft(s32 port)
{
    return isPadTrigger(port, 1 << 18);
}

bool isPadTriggerRight(s32 port)
{
    return isPadTrigger(port, 1 << 19);
}

bool isPadTriggerZL(s32 port)
{
    return isPadTrigger(port, 1 << 2);
}

bool isPadTriggerZR(s32 port)
{
    return isPadTrigger(port, 1 << 5);
}

bool isPadTriggerL(s32 port)
{
    return isPadTrigger(port, 1 << 13);
}

bool isPadTriggerR(s32 port)
{
    return isPadTrigger(port, 1 << 14);
}

bool isPadTriggerPressRightStick(s32 port)
{
    return isPadTrigger2(port);
}

bool isPadHold(s32 port, s32 button)
{
    return getController(port)->isHold(button);
}

bool isPadHoldL(s32 port)
{
    return isPadHold(port, 1 << 13);
}

bool isPadHold1(s32 port)
{
    return isPadHold(port, 1 << 7);
}

bool isPadHold2(s32 port)
{
    return isPadHold(port, 1 << 6);
}

bool isPadHoldPressLeftStick(s32 port)
{
    return isPadHold1(port);
}

bool isPadHoldPressRightStick(s32 port)
{
    return isPadHold2(port);
}

bool isPadHoldZL(s32 port)
{
    return isPadHold(port, 1 << 2);
}
bool isPadHoldZR(s32 port)
{
    return isPadHold(port, 1 << 5);
}

} // namespace al
