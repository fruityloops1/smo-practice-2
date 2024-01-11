#pragma once

#include "imgui.h"
#include "pe/Menu/IComponent.h"
#include <sead/basis/seadTypes.h>

namespace pe {

enum class InputDisplayColor : u8 {
    None,
    White,
    Gray,
    Black,
    Red,
    Blue,
    Yellow,
    Green,
    Orange,
    Purple,
    Pink
};

constexpr static ImVec4 sInputDisplayColors[] {
    { 0, 0, 0, 0 }, // None
    { 255, 255, 255, 255 }, // White
    { 128, 128, 128, 255 }, // Gray
    { 0, 0, 0, 255 }, // Black
    { 235, 64, 52, 255 }, // Red
    { 52, 58, 235, 255 }, // Blue
    { 235, 210, 52, 255 }, // Yellow
    { 58, 235, 52, 255 }, // Green
    { 235, 152, 52, 255 }, // Orange
    { 113, 52, 235, 255 }, // Purple
    { 225, 52, 235, 255 }, // Pink
};

constexpr const char* sInputDisplayColorNames[] {
    "None",
    "White",
    "Gray",
    "Black",
    "Red",
    "Blue",
    "Yellow",
    "Green",
    "Orange",
    "Purple",
    "Pink"
};

inline ImVec4 getInputDisplayColor(InputDisplayColor color) { return sInputDisplayColors[int(color)]; }

class Menu;
class InputDisplay : public IComponent {
public:
    InputDisplay() { }

    void draw() override;
};

} // namespace pe
