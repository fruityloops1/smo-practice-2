#pragma once

#include "Scene/StageSceneStateStageMap.h"
#include "System/GameDataHolder.h"
#include "al/Library/Scene/Scene.h"

class StageSceneStateCollectionList {
public:
    u8 _0[0x38];
    StageSceneStateStageMap* mStateStageMap = nullptr;
};

class StageScene : public al::Scene {
public:
    bool isEnableSave() const;

    u8 _D8[0x98];
    StageSceneStateCollectionList* mStateCollection = nullptr;
    u8 _178[0x90];
    GameDataHolder* mHolder = nullptr;
};
