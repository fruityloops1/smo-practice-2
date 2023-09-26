#pragma once

#include "al/Library/Thread/FunctorV0M.h"
#include "pe/Menu/MenuComponent.h"

namespace pe {

class ButtonMenuComponent : public MenuComponent {
    const char* mText = nullptr;
    bool mLocalized = false;
    int mFontSize = 35;
    const al::FunctorBase* mFunctor;

public:
    ButtonMenuComponent(const char* text, const al::FunctorBase& functor, bool localized = false, int fontSize = 35)
        : mText(text)
        , mLocalized(localized)
        , mFontSize(fontSize)
        , mFunctor(functor.clone())
    {
    }

    ImVec2 getSize() const override;
    void draw(const ImVec2& at) override;
};

} // namespace pe
