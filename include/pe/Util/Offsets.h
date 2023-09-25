#pragma once

#include <cstdint>

namespace pe {
namespace offsets {

#if GAME_VERSION == 130
    const uintptr_t FileDeviceMgrCtorHookLocation = 0x00943d60;
    const uintptr_t HakoniwaSequenceHookLocation = 0x004b4230;
#endif

} // namespace offsets
} // namespace pe
