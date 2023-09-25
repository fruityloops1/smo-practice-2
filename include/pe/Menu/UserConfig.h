#pragma once

#include "pe/Util/Localization.h"

namespace pe {

struct UserConfig {
    PeepaLanguage currentLanguage;
};

UserConfig& getConfig();
void saveConfig();
void loadConfig();

} // namespace pe
