#pragma once

#include "imgui.h"
#include "pe/Menu/MenuComponent.h"

namespace pe {

class Vector2MenuComponent : public MenuComponent {
    ImVec2* mValue = nullptr;
    const char* mText = nullptr;
    bool mLocalized = false;
    int mFontSize = 35;
    ImVec2 mMin = ImVec2(FLT_MAX, FLT_MAX), mMax = ImVec2(FLT_MAX, FLT_MAX);

public:
    Vector2MenuComponent(ImVec2* value, const char* text, bool localized = false, const ImVec2& min = ImVec2(FLT_MAX, FLT_MAX), const ImVec2& max = ImVec2(FLT_MAX, FLT_MAX), int fontSize = 35)
        : mValue(value)
        , mText(text)
        , mLocalized(localized)
        , mFontSize(fontSize)
        , mMin(min)
        , mMax(max)
    {
    }

    ImVec2 getSize() const override;
    void draw(const ImVec2& at) override;
    bool canHaveFocus() const override { return true; }
};

} // namespace pe
