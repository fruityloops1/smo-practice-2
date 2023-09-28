#include "pe/Util/Type.h"
#include "Player/PlayerActorHakoniwa.h"
#include "pe/Util/Offsets.h"

namespace pe {
namespace util {

    template <>
    bool checkTypeByVtable<PlayerActorHakoniwa>(const al::LiveActor* actor)
    {
        return getVftOffsetMain(actor) == offsets::PlayerActorHakoniwaVft;
    }

} // namespace util
} // namespace pe
