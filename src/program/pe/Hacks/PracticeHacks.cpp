#include "pe/Hacks/PracticeHacks.h"
#include "System/GameDataHolderWriter.h"
#include "al/Library/Audio/AudioKeeper.h"
#include "al/Library/Math/MathRandomUtil.h"
#include "hook/trampoline.hpp"
#include "patch/code_patcher.hpp"
#include "pe/Menu/UserConfig.h"
#include "pe/Util/Offsets.h"
#include "replace.hpp"
#include "util/modules.hpp"
#include "util/sys/rw_pages.hpp"

namespace pe {

HOOK_DEFINE_TRAMPOLINE(IsGotShine) { static bool Callback(void* accessor, void* shineInfo); };
HOOK_DEFINE_TRAMPOLINE(SetGotShine) { static void Callback(GameDataHolderWriter writer, void* shineInfo); };
HOOK_DEFINE_TRAMPOLINE(StartBgm1) { static void Callback(al::IUseAudioKeeper * user, const char* bgm, int a, int b); };
HOOK_DEFINE_TRAMPOLINE(StartBgm2) { static void Callback(al::IUseAudioKeeper * user, void* request, bool a, bool b); };

bool IsGotShine::Callback(void* accessor, void* shineInfo)
{
    return getConfig()->mIsGrayShineRefreshEnabled ? false : Orig(accessor, shineInfo);
}

void SetGotShine::Callback(GameDataHolderWriter writer, void* shineInfo)
{
    if (!getConfig()->mIsShineRefreshEnabled)
        Orig(writer, shineInfo);
}

void StartBgm1::Callback(al::IUseAudioKeeper* user, const char* bgm, int a, int b)
{
    if (!getConfig()->mIsBgmDisabled)
        Orig(user, bgm, a, b);
}

void StartBgm2::Callback(al::IUseAudioKeeper* user, void* request, bool a, bool b)
{
    if (!getConfig()->mIsBgmDisabled)
        Orig(user, request, a, b);
}

static bool isPatternReverse()
{
    bool b = al::isHalfProbability();
    if (getConfig()->mCurPattern != MofumofuPattern::Random)
        b = UserConfig::sPatternEntries[getConfig()->mCurPattern - 1].reverse;
    return b;
}

static int getMofumofuTarget(int a)
{
    int r = al::getRandom(a);
    if (getConfig()->mCurPattern != MofumofuPattern::Random)
        r = UserConfig::sPatternEntries[getConfig()->mCurPattern - 1].target;
    return r;
}

void installPracticeHacks()
{
    using Patcher = exl::patch::CodePatcher;

    IsGotShine::InstallAtOffset(offsets::GameDataFileIsGotShine);
    SetGotShine::InstallAtOffset(offsets::GameDataFunctionSetGotShine);
    StartBgm1::InstallAtOffset(offsets::StartBgm1);
    StartBgm2::InstallAtOffset(offsets::StartBgm2);

    Patcher(0x000b07f8).BranchLinkInst((void*)getMofumofuTarget);
    Patcher(0x000b07a8).BranchLinkInst((void*)isPatternReverse);

    exl::util::RwPages a(exl::util::modules::GetTargetOffset(offsets::ShineRefreshText), 24);
    strncpy((char*)a.GetRw(), "Practice Mod", 24);
}

} // namespace pe
