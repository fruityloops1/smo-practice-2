#include "pe/Hacks/PracticeHacks.h"
#include "hook/trampoline.hpp"
#include "pe/Menu/UserConfig.h"
#include "pe/Util/Offsets.h"

namespace pe {

HOOK_DEFINE_TRAMPOLINE(IsGotShine) { static bool Callback(void* accessor, void* shineInfo); };

bool IsGotShine::Callback(void* accessor, void* shineInfo)
{
    return getConfig()->mIsGrayShineRefreshEnabled ? false : Orig(accessor, shineInfo);
}

void installPracticeHacks()
{
    IsGotShine::InstallAtOffset(offsets::GameDataFileIsGotShine);
}

} // namespace pe
