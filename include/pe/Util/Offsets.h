#pragma once

#include <cstdint>

namespace pe {
namespace offsets {

#if GAME_VERSION == 130
const uintptr_t FileDeviceMgrCtorHookLocation = 0x00943d60;
#endif

} // namespace offsets
} // namespace pe
