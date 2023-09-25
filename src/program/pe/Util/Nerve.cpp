#include "pe/Util/Nerve.h"
#include "al/Library/Nerve/NerveUtil.h"
#include "util/modules.hpp"

namespace pe {
namespace util {

    const al::Nerve* getNerveAt(uintptr_t offset)
    {
        return (al::Nerve*)exl::util::modules::GetTargetOffset(offset);
    }

    const void setNerveAt(al::IUseNerve* to, uintptr_t offset)
    {
        al::setNerve(to, getNerveAt(offset));
    }

} // namespace util
} // namespace pe
