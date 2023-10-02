#include "pe/Util/Type.h"
#include "MapObj/Shine.h"
#include "MapObj/TreasureBox.h"
#include "Player/PlayerActorHakoniwa.h"
#include "pe/Util/Offsets.h"

namespace pe {
namespace util {

    template <>
    bool checkTypeByVtable<PlayerActorHakoniwa>(const al::LiveActor* actor)
    {
        return getVftOffsetMain(actor) == offsets::PlayerActorHakoniwaVft;
    }

    template <>
    bool checkTypeByVtable<Shine>(const al::LiveActor* actor)
    {
        return getVftOffsetMain(actor) == offsets::ShineVft;
    }

    template <>
    bool checkTypeByVtable<TreasureBox>(const al::LiveActor* actor)
    {
        return getVftOffsetMain(actor) == offsets::TreasureBoxVft;
    }

} // namespace util
} // namespace pe
