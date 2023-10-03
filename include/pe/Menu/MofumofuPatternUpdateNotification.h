#pragma once

#include "basis/seadTypes.h"
#include "imgui.h"
#include "pe/Menu/IComponent.h"

namespace pe {

class MofumofuPatternUpdateNotification : public IComponent {
    int mUpdateFrames = 0;

public:
    MofumofuPatternUpdateNotification()
    {
        sInstance = this;
    }

    void setUpdated() { mUpdateFrames = 90; }
    void draw() override;

    static MofumofuPatternUpdateNotification* sInstance;
};

} // namespace pe
