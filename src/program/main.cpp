#include "al/Library/Memory/MemorySystem.h"
#include "al/Library/Sequence/Sequence.h"
#include "diag/assert.hpp"
#include "heap/seadExpHeap.h"
#include "heap/seadHeapMgr.h"
#include "hook/trampoline.hpp"
#include "lib.hpp"
#include "nn/fs.h"
#include "pe/Hacks/MenuDPadDisable.h"
#include "pe/Menu/Menu.h"
#include "pe/Menu/UserConfig.h"
#include "pe/Util/Offsets.h"
#include "program/imgui_nvn.h"
#include <sead/filedevice/seadFileDeviceMgr.h>

HOOK_DEFINE_TRAMPOLINE(FileDeviceMgrCtor) { static void Callback(sead::FileDeviceMgr * thisPtr); };
void FileDeviceMgrCtor::Callback(sead::FileDeviceMgr* thisPtr)
{
    Orig(thisPtr);
    thisPtr->mMountedSd = nn::fs::MountSdCardForDebug("sd").IsSuccess();
}

class HakoniwaSequence;
HOOK_DEFINE_TRAMPOLINE(HakoniwaSequenceInit) { static void Callback(HakoniwaSequence * thisPtr, const al::SequenceInitInfo& info); };
void HakoniwaSequenceInit::Callback(HakoniwaSequence* thisPtr, const al::SequenceInitInfo& info)
{
    Orig(thisPtr, info);

    pe::getMenuHeap() = sead::ExpHeap::create(1024 * 1024 * 1, "MenuHeap", al::getSequenceHeap(), 8, sead::ExpHeap::cHeapDirection_Forward, false);

    sead::ScopedCurrentHeapSetter setter(pe::getMenuHeap());
    pe::Menu::createInstance(nullptr);
}

HOOK_DEFINE_TRAMPOLINE(HakoniwaSequenceUpdate) { static void Callback(HakoniwaSequence * thisPtr); };
void HakoniwaSequenceUpdate::Callback(HakoniwaSequence* thisPtr)
{
    Orig(thisPtr);

    sead::ScopedCurrentHeapSetter setter(pe::getMenuHeap());
    auto* menu = pe::Menu::instance();
    if (menu) {
        al::Scene* scene = *reinterpret_cast<al::Scene**>(reinterpret_cast<u8*>(thisPtr) + 0xb0);
        menu->update(scene);
    }
}

static void drawDbgGui()
{
    sead::ScopedCurrentHeapSetter setter(pe::getMenuHeap());
    auto* menu = pe::Menu::instance();
    if (menu)
        menu->draw();
}

extern "C" void exl_main(void* x0, void* x1)
{
    exl::hook::Initialize();

    using Patcher = exl::patch::CodePatcher;
    using namespace exl::patch::inst;

    FileDeviceMgrCtor::InstallAtOffset(pe::offsets::FileDeviceMgrCtorHookLocation);
    HakoniwaSequenceInit::InstallAtOffset(pe::offsets::HakoniwaSequenceInitHookLocation);
    HakoniwaSequenceUpdate::InstallAtOffset(pe::offsets::HakoniwaSequenceUpdate);

    pe::initMenuDPadDisableHooks();

    nvnImGui::InstallHooks();
    nvnImGui::addDrawFunc(drawDbgGui);
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}
