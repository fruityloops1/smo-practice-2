#include "diag/assert.hpp"
#include "hook/trampoline.hpp"
#include "lib.hpp"
#include "nn/fs.h"
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

class ProductSequence;
HOOK_DEFINE_TRAMPOLINE(ProductSequenceInit) { static void Callback(ProductSequence * thisPtr); };
void ProductSequenceInit::Callback(ProductSequence* thisPtr)
{
    Orig(thisPtr);

    pe::Menu::createInstance(nullptr);
}

void drawDbgGui()
{
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

    nvnImGui::InstallHooks();
    nvnImGui::addDrawFunc(drawDbgGui);
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}
