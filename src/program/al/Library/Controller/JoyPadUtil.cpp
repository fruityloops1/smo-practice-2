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

bool isPadTriggerLeftStick(s32 port)
{
    return isPadTrigger(port, 0xF00000);
}

} // namespace al
