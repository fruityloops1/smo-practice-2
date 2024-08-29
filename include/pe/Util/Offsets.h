#pragma once

#include <cstdint>

namespace pe {
namespace offsets {

#if GAME_VERSION == 130
    const uintptr_t FileDeviceMgrCtorHookLocation = 0x00943d60;
    const uintptr_t HakoniwaSequenceInitHookLocation = 0x004b4230;
    const uintptr_t HakoniwaSequenceUpdate = 0x004b4e90;

    const uintptr_t IsPadTriggerDpadDown = 0x005d0200;
    const uintptr_t IsPadTriggerDpadLeft = 0x005d02b0;
    const uintptr_t IsPadTriggerDpadRight = 0x005d0360;
    const uintptr_t IsPadTriggerDpadUp = 0x005d0150;

    const uintptr_t StageSceneNrvPause = 0x012c5e48;
    const uintptr_t StageSceneNrvPlay = 0x012c5eb8;
    const uintptr_t StageSceneNrvShineGet = 0x012c5dc0;
    const uintptr_t StageSceneNrvWarpToCheckpoint = 0x012c5f30;

    const uintptr_t PlayerActorHakoniwaVft = 0x012b1ef8;
    const uintptr_t ShineVft = 0x01202f00;
    const uintptr_t TreasureBoxVft = 0x0127c4d0;
    const uintptr_t TreasureBoxNrvWait = 0x0127ca58;
    const uintptr_t GameDataFileIsGotShine = 0x004c9700;
    const uintptr_t GameDataFunctionSetGotShine = 0x004d3c10;
    const uintptr_t StartBgm1 = 0x0059ac30;
    const uintptr_t StartBgm2 = 0x0059acd0;
    const uintptr_t ShineRefreshText = 0x00e6dedd;

    const uintptr_t ShineNrvAppear = 0x01204060;

    const uintptr_t ShineGrabHook = 0x001b4e00;
    const uintptr_t ShineTickHook = 0x001dfd94;
    const uintptr_t CheckpointTouchHook = 0x0021dd90;

#endif

} // namespace offsets
} // namespace pe
