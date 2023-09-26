#include "pe/Menu/BoolMenuComponent.h"
#include "pe/Menu/EnumMenuComponent.h"

namespace pe {

static constexpr const char* sValues[] { "false", "true" };

BoolMenuComponent::BoolMenuComponent(bool* value, const char* title, int fontSize)
    : EnumMenuComponent(reinterpret_cast<s8*>(value), sValues, title, true, fontSize)
{
}

} // namespace pe
