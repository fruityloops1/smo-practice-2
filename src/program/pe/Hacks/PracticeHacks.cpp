#include "pe/Hacks/PracticeHacks.h"
#include "Layout/MapLayout.h"
#include "Scene/StageScene.h"
#include "Scene/StageSceneStateStageMap.h"
#include "System/GameDataHolderWriter.h"
#include "al/Library/Audio/AudioKeeper.h"
#include "al/Library/Controller/JoyPadUtil.h"
#include "al/Library/Math/MathRandomUtil.h"
#include "al/Library/Nerve/NerveUtil.h"
#include "hook/trampoline.hpp"
#include "patch/code_patcher.hpp"
#include "pe/Menu/Menu.h"
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

static bool isEnableCheckpointWarp(MapLayout* thisPtr)
{
    return getConfig()->mIsEnableWarpsAlways ? true : thisPtr->isEnableCheckpointWarp();
}

static bool isEnableSave(StageScene* scene)
{
    return getConfig()->mIsEnableAutosave ? scene->isEnableSave() : false;
}

HOOK_DEFINE_TRAMPOLINE(IsPadTriggerA) { static bool Callback(s32 port); };

bool IsPadTriggerA::Callback(s32 port)
{
    if (pe::Menu::instance()->isEnabled())
        return false;
    return Orig(port);
}

static void setMapTargetUpdateNullNerve(al::IUseNerve* user, const al::Nerve* nerve)
{
    StageSceneStateStageMap* map;
    __asm("mov %0, x19"
          : "=r"(map));
    void* mapThingPtr;
    __asm("mov %0, x23"
          : "=r"(mapThingPtr));

    if (mapThingPtr != nullptr)
        Menu::instance()->setLatestMapTarget(mapThingPtr);

    al::setNerve(user, nerve);
}

HOOK_DEFINE_TRAMPOLINE(IsThrowTypeRolling) { static bool Callback(void* thisPtr, const sead::Vector2f& motion); };

bool IsThrowTypeRolling::Callback(void* thisPtr, const sead::Vector2f& motion)
{
    if (getConfig()->mIsEnableDownthrowOnly && motion.x == 0 && motion.y == 0)
        return true;
    return Orig(thisPtr, motion);
}

void installPracticeHacks()
{
    using Patcher = exl::patch::CodePatcher;

    IsGotShine::InstallAtOffset(offsets::GameDataFileIsGotShine);
    SetGotShine::InstallAtOffset(offsets::GameDataFunctionSetGotShine);
    StartBgm1::InstallAtOffset(offsets::StartBgm1);
    StartBgm2::InstallAtOffset(offsets::StartBgm2);

    Patcher(0x000a46ec).BranchLinkInst((void*)getMofumofuTarget);
    Patcher(0x000a4698).BranchLinkInst((void*)isPatternReverse);
    Patcher(0x001d1584).BranchLinkInst((void*)isEnableCheckpointWarp);
    Patcher(0x004742d0).BranchLinkInst((void*)isEnableSave);
    Patcher(0x004b1c78).BranchLinkInst((void*)isEnableSave);
    Patcher(0x004b4fa4).BranchLinkInst((void*)isEnableSave);

    Patcher(0x0049d3d0).BranchLinkInst((void*)setMapTargetUpdateNullNerve);
    IsPadTriggerA::InstallAtOffset(0x005cfbd0);
    // IsThrowTypeRolling::InstallAtOffset(0x003f1530);

    exl::util::RwPages a(exl::util::modules::GetTargetOffset(offsets::ShineRefreshText), 24);
    strncpy((char*)a.GetRw(), "Practice Mod", 24);
}

} // namespace pe
