#pragma once

#include "Player/PlayerActorHakoniwa.h"
#include "types.h"

#include "al/Library/LiveActor/LiveActor.h"

class Shine : public al::LiveActor, public IUseDimension {
public:
    Shine(const char* actorName);

    ActorDimensionKeeper* getActorDimensionKeeper() const override;

    void offAppear();
    void onAppear();
    void appearPopup();

    void getDirectWithDemo(void);
    void getDirect();
    void get();

    void onSwitchGet(void);

    bool isGot() const;

    void setGrandShine(void);

    char padding[0x10];
    // 0x11C mIsEmptyShine
    class ShineInfo* curShineInfo; // 0x120
    sead::Vector3f mInitialPosition;
    u8 _138[320];
    class QuestInfo* shineQuestInfo; // 0x278
    void* unkPtr1; // 0x280
    ActorDimensionKeeper* mDimensionKeeper; // 0x288
    int shineId; // 0x290
};