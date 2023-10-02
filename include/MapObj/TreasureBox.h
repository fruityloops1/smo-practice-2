#pragma once

#include "MapObj/Shine.h"
#include "al/Library/LiveActor/LiveActor.h"

class TreasureBox : public al::LiveActor {
public:
    TreasureBox(const char* name);

    void setupOpenNerve();

    void* _108;
    Shine* mShine = nullptr;
    al::LiveActor* mCloseCollisionObj = nullptr;
    al::LiveActor* mOpenCollisionObj = nullptr;
};
