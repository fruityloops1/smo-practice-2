#include "pe/Hacks/MenuDPadDisable.h"
#include "al/Library/Controller/JoyPadUtil.h"
#include "hook/trampoline.hpp"
#include "pe/Menu/Action.h"
#include "pe/Menu/Menu.h"
#include "pe/Menu/UserConfig.h"
#include "pe/Util/Offsets.h"

namespace pe {

HOOK_DEFINE_TRAMPOLINE(DPadUp) { static bool Callback(int port); };
HOOK_DEFINE_TRAMPOLINE(DPadDown) { static bool Callback(int port); };
HOOK_DEFINE_TRAMPOLINE(DPadLeft) { static bool Callback(int port); };
HOOK_DEFINE_TRAMPOLINE(DPadRight) { static bool Callback(int port); };

static bool dpadHook(int port, int mask)
{
    if (pe::Menu::instance()->isEnabled())
        return false;
    return al::isPadTrigger(port, mask);
}

bool DPadUp::Callback(int port)
{
    if (getConfig()->mDUpBind != ActionType::None)
        return false;
    return dpadHook(port, 1 << 16);
}
bool DPadDown::Callback(int port)
{
    if (getConfig()->mDDownBind != ActionType::None)
        return false;
    return dpadHook(port, 1 << 17);
}
bool DPadLeft::Callback(int port)
{
    if (getConfig()->mDLeftBind != ActionType::None)
        return false;
    return dpadHook(port, 1 << 18);
}
bool DPadRight::Callback(int port)
{
    if (getConfig()->mDRightBind != ActionType::None)
        return false;
    return dpadHook(port, 1 << 19);
}

void initMenuDPadDisableHooks()
{
    DPadUp::InstallAtOffset(offsets::IsPadTriggerDpadUp);
    DPadDown::InstallAtOffset(offsets::IsPadTriggerDpadDown);
    DPadLeft::InstallAtOffset(offsets::IsPadTriggerDpadLeft);
    DPadRight::InstallAtOffset(offsets::IsPadTriggerDpadRight);
}

} // namespace pe
