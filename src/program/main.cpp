#include "al/Library/LiveActor/LiveActor.h"
#include "devenv/seadFontMgr.h"
#include "diag/assert.hpp"
#include "heap/seadHeapMgr.h"
#include "hook/trampoline.hpp"
#include "imgui.h"
#include "lib.hpp"
#include "nn/fs.h"
#include "nn/oe.h"
#include "nn/os.h"
#include "nn/socket.h"
#include "program/imgui_nvn.h"
#include "replace.hpp"
#include "util/modules.hpp"
#include "util/sys/rw_pages.hpp"
#include <sead/filedevice/nin/seadNinSDFileDeviceNin.h>
#include <sead/filedevice/seadFileDeviceMgr.h>
#include <sead/heap/seadExpHeap.h>
#include <sead/heap/seadHeapMgr.h>

HOOK_DEFINE_TRAMPOLINE(CreateFileDeviceMgr) { static void Callback(sead::FileDeviceMgr * thisPtr); };
void CreateFileDeviceMgr::Callback(sead::FileDeviceMgr* thisPtr)
{
    Orig(thisPtr);
    thisPtr->mMountedSd = nn::fs::MountSdCardForDebug("sd").IsSuccess();
    // sead::NinSDFileDevice* sdFileDevice = new sead::NinSDFileDevice();
    // thisPtr->mount(sdFileDevice);
}

void drawDbgGui()
{
    ImGui::ShowDemoWindow();
}

extern "C" void exl_main(void* x0, void* x1)
{
    exl::hook::Initialize();

    using Patcher = exl::patch::CodePatcher;
    using namespace exl::patch::inst;

    CreateFileDeviceMgr::InstallAtOffset(0x00943d60);

    nvnImGui::InstallHooks();
    nvnImGui::addDrawFunc(drawDbgGui);
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}
