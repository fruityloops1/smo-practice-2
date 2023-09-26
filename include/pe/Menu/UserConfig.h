#pragma once

#include "pe/Menu/Action.h"
#include "pe/Util/Localization.h"

namespace pe {

struct UserConfig {
    PeepaLanguage currentLanguage = PeepaLanguage::English;
    ActionType mDUpBind = ActionType::None;
    ActionType mDDownBind = ActionType::None;
    ActionType mDLeftBind = ActionType::None;
    ActionType mDRightBind = ActionType::None;
};

UserConfig*& getConfig();
void saveConfig();
void loadConfig();

} // namespace pe
