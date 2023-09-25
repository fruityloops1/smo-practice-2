#include "pe/Menu/Menu.h"
#include "pe/Menu/UserConfig.h"
#include "imgui.h"

namespace pe {

SEAD_SINGLETON_DISPOSER_IMPL(Menu)

Menu::Menu()
{
    pe::loadConfig();
}

void Menu::draw()
{
    ImGui::GetForegroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], 17, ImVec2(200, 200), IM_COL32(255, 255, 255, 255), "Hello, World!");
}

} // namespace pe
