#pragma once

#include "al/Library/Nerve/Nerve.h"
#include <cstdint>

class ProductSequence;

namespace pe {
namespace util {

    const al::Nerve* getNerveAt(uintptr_t offset);

    const void setNerveAt(al::IUseNerve* to, uintptr_t offset);

} // namespace util
} // namespace pe