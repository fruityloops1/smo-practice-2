#pragma once

#include "al/Library/Thread/FunctorV0M.h"
#include "pe/Menu/MenuComponent.h"
#include <functional>

namespace pe {

class ButtonMenuComponent : public MenuComponent {
    const char* mText = nullptr;
    bool mLocalized = false;
    int mFontSize = 35;
    const std::function<void()> mFunctor;

public:
    ButtonMenuComponent(const char* text, std::function<void()> functor, bool localized = false, int fontSize = 35)
        : mText(text)
        , mLocalized(localized)
        , mFontSize(fontSize)
        , mFunctor(functor)
    {
    }

    ImVec2 getSize() const override;
    void draw(const ImVec2& at) override;
};

} // namespace pe
