#pragma once

#include "pe/Menu/EnumMenuComponent.h"

namespace pe {

class BoolMenuComponent : public EnumMenuComponent<s8> {
public:
    BoolMenuComponent(bool* value, const char* title, int fontSize = 35);
};

} // namespace pe
