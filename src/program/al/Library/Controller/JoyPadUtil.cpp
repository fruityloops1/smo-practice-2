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

bool isPadHoldA(s32 port)
{
    return isPadHold(port, 1);
}
bool isPadHoldB(s32 port)
{
    return isPadHold(port, 1 << 1);
}
bool isPadHoldX(s32 port)
{
    return isPadHold(port, 1 << 3);
}
bool isPadHoldY(s32 port)
{
    return isPadHold(port, 1 << 4);
}
bool isPadHoldZL(s32 port)
{
    return isPadHold(port, 1 << 2);
}
bool isPadHoldZR(s32 port)
{
    return isPadHold(port, 1 << 5);
}
bool isPadHoldL(s32 port)
{
    return isPadHold(port, 1 << 13);
}
bool isPadHoldR(s32 port)
{
    return isPadHold(port, 1 << 14);
}
bool isPadHold1(s32 port)
{
    return isPadHold(port, 1 << 7);
}
bool isPadHold2(s32 port)
{
    return isPadHold(port, 1 << 6);
}
bool isPadHoldUp(s32 port)
{
    return isPadHold(port, 1 << 16);
}
bool isPadHoldDown(s32 port)
{
    return isPadHold(port, 1 << 17);
}
bool isPadHoldLeft(s32 port)
{
    return isPadHold(port, 1 << 18);
}
bool isPadHoldRight(s32 port)
{
    return isPadHold(port, 1 << 19);
}
bool isPadHoldLeftUp(s32 port)
{
    return getController(port)->isHoldAll(0x50000);
}
bool isPadHoldLeftDown(s32 port)
{
    return getController(port)->isHoldAll(0x60000);
}
bool isPadHoldRightUp(s32 port)
{
    return getController(port)->isHoldAll(0x90000);
}
bool isPadHoldRightDown(s32 port)
{
    return getController(port)->isHoldAll(0xA0000);
}
bool isPadHoldHome(s32 port)
{
    return isPadHold(port, 1 << 8);
}
bool isPadHoldStart(s32 port)
{
    return isPadHold(port, 1 << 11);
}
bool isPadHoldSelect(s32 port)
{
    return isPadHold(port, 1 << 12);
}
bool isPadHoldPlus(s32 port)
{
    return isPadHold(port, 1 << 10);
}
bool isPadHoldMinus(s32 port)
{
    return isPadHold(port, 1 << 9);
}
bool isPadHoldAny(s32 port)
{
    return isPadHold(port, 0xFFF7FFF);
}
bool isPadHoldAnyWithoutStick(s32 port)
{
    return isPadHold(port, 0xF7FFF);
}
bool isPadHoldUpLeftStick(s32 port)
{
    return isPadHold(port, 1 << 20);
}
bool isPadHoldDownLeftStick(s32 port)
{
    return isPadHold(port, 1 << 21);
}
bool isPadHoldLeftLeftStick(s32 port)
{
    return isPadHold(port, 1 << 22);
}
bool isPadHoldRightLeftStick(s32 port)
{
    return isPadHold(port, 1 << 23);
}
bool isPadHoldUpRightStick(s32 port)
{
    return isPadHold(port, 1 << 24);
}
bool isPadHoldDownRightStick(s32 port)
{
    return isPadHold(port, 1 << 25);
}
bool isPadHoldLeftRightStick(s32 port)
{
    return isPadHold(port, 1 << 26);
}
bool isPadHoldRightRightStick(s32 port)
{
    return isPadHold(port, 1 << 27);
}
bool isPadHoldLeftStick(s32 port)
{
    return isPadHold(port, 0xF00000);
}
bool isPadHoldRightStick(s32 port)
{
    return isPadHold(port, 0xF000000);
}
bool isPadHoldPressLeftStick(s32 port)
{
    return isPadHold1(port);
}
bool isPadHoldPressRightStick(s32 port)
{
    return isPadHold2(port);
}

const sead::Vector2f& getRightStick(s32 port)
{
    return getController(port)->getRightStick();
}

} // namespace al
