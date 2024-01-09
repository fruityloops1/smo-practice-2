#pragma once

#include "System/GameDataHolder.h"
#include "al/Library/Scene/Scene.h"

class StageScene : public al::Scene {
public:
    bool isEnableSave() const;

    u8 _D8[0x208];
    GameDataHolder* mHolder = nullptr;
};
