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

    const uintptr_t PlayerActorHakoniwaVft = 0x012b1ef8;

    const uintptr_t ShineGrabHook = 0x001b4e00;
#endif

} // namespace offsets
} // namespace pe
