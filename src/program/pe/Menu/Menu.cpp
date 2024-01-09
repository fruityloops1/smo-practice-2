#include "pe/Menu/Menu.h"
#include "MapObj/Shine.h"
#include "MapObj/TreasureBox.h"
#include "Player/PlayerActorHakoniwa.h"
#include "Scene/ChangeStageInfo.h"
#include "Scene/SceneObjUtil.h"
#include "Scene/StageScene.h"
#include "System/GameDataFunction.h"
#include "System/GameDataHolder.h"
#include "al/Library/Controller/JoyPadUtil.h"
#include "al/Library/LiveActor/ActorCollisionFunction.h"
#include "al/Library/LiveActor/ActorFlagFunction.h"
#include "al/Library/LiveActor/ActorPoseKeeper.h"
#include "al/Library/LiveActor/LiveActor.h"
#include "al/Library/LiveActor/LiveActorGroup.h"
#include "al/Library/LiveActor/LiveActorKit.h"
#include "al/Library/Nerve/NerveUtil.h"
#include "al/Library/Scene/Scene.h"
#include "al/Library/Thread/FunctorV0M.h"
#include "imgui.h"
#include "pe/Menu/Action.h"
#include "pe/Menu/BoolMenuComponent.h"
#include "pe/Menu/ButtonMenuComponent.h"
#include "pe/Menu/ChangeStage.h"
#include "pe/Menu/DummyMenuComponent.h"
#include "pe/Menu/EnumMenuComponent.h"
#include "pe/Menu/IntMenuComponent.h"
#include "pe/Menu/MenuComponent.h"
#include "pe/Menu/MofumofuPatternUpdateNotification.h"
#include "pe/Menu/QuickActionMenu.h"
#include "pe/Menu/Timer.h"
#include "pe/Menu/UserConfig.h"
#include "pe/Menu/Vector2MenuComponent.h"
#include "pe/Util/Localization.h"
#include "pe/Util/Nerve.h"
#include "pe/Util/Offsets.h"
#include "pe/Util/Type.h"
#include "rs/Util/PlayerUtil.h"
#include "util/modules.hpp"
#include <algorithm>
#include <cstdio>

namespace pe {

sead::Heap*& getMenuHeap()
{
    static sead::Heap* sHeap { nullptr };
    return sHeap;
}

SEAD_SINGLETON_DISPOSER_IMPL(Menu)

bool someBOol = false;

Menu::Menu()
{
    getConfig() = new UserConfig;
    pe::loadConfig();

    mCategories[0].name = "hacks";
    mCategories[0].components.allocBuffer(5, nullptr);
    mCategories[0].components.pushBack(new BoolMenuComponent(&getConfig()->mIsGrayShineRefreshEnabled, "grayshinerefresh"));
    mCategories[0].components.pushBack(new BoolMenuComponent(&getConfig()->mIsShineRefreshEnabled, "shinerefresh"));
    mCategories[0].components.pushBack(new BoolMenuComponent(&getConfig()->mIsBgmDisabled, "bgmdisable"));
    mCategories[0].components.pushBack(new BoolMenuComponent(&getConfig()->mIsEnableWarpsAlways, "alwaysenablewarps"));
    mCategories[0].components.pushBack(new BoolMenuComponent(&getConfig()->mIsEnableAutosave, "disableautosave"));

    static constexpr const char* patternNames[] {
        "Random",
        "Ghost",
        "Nose",
        "C",
        "W",
        "J",
        "Medal",
        "Plane",
        "Five",
        "Hangman",
        "Spanish",
        "Siblings",
        "Snake",
        "Eight",
        "Mushroom",
        "Z",
        "Tetris",
        "Ear",
        "Bomb",
        "Bird",
        "L",
        "O"
    };

    mCategories[0].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mCurPattern), patternNames, "mofumofupattern", false, true));

    mCategories[1].name = "timer";
    mCategories[1].components.allocBuffer(6, nullptr);
    mCategories[1].components.pushBack(new BoolMenuComponent(&getConfig()->mTimerEnabled, "timer"));
    mCategories[1].components.pushBack(new IntMenuComponent<float>(&getConfig()->mTimerFontSize, "fontsize", 8, 100, true));
    mCategories[1].components.pushBack(new Vector2MenuComponent(&getConfig()->mTimerPos, "position", true, ImVec2(0, 0), ImVec2(1600, 900)));
    static constexpr const char* timerNames[] {
        "timer0", "timer1", "timer2"
    };
    mCategories[1].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mTimerStartType), timerNames, "timerstart", true));
    mCategories[1].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mTimerEndType), timerNames, "timerend", true));
    mCategories[1].components.pushBack(new BoolMenuComponent(&getConfig()->mTimerSplit, "timersplit"));

    mCategories[2].name = "keybinds";
    mCategories[2].components.allocBuffer(15, nullptr);
    mCategories[2].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mDUpBind), sActionNames, "dpadup", true));
    mCategories[2].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mDDownBind), sActionNames, "dpaddown", true));
    mCategories[2].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mDLeftBind), sActionNames, "dpadleft", true));
    mCategories[2].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mDRightBind), sActionNames, "dpadright", true));
    mCategories[2].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mRsLBind), sActionNames, "rsl", true));
    mCategories[2].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mRsRBind), sActionNames, "rsr", true));
    mCategories[2].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mZLZRBind), sActionNames, "zlzr", true));

    static constexpr const char* wheelNames[] {
        "wheel1", "wheel2", "wheel3", "wheel4", "wheel5", "wheel6", "wheel7", "wheel8"
    };
    for (int i = 0; i < 8; i++) {
        mCategories[2].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->mQuickMenuBinds[i]), sActionNames, wheelNames[i], true));
    }

    mCategories[3].name = "stage";
    mCategories[3].components.allocBuffer(3, nullptr);
    mCategories[3].components.pushBack(new EnumMenuComponent<int>(&getConfig()->mSelectedStageIdx, sStageNames, "Stage", false, false));
    mCategories[3].components.pushBack(new IntMenuComponent<int>(&getConfig()->mSelectedScenario, "scenario", 0, 14, true));
    mCategories[3].components.pushBack(new ButtonMenuComponent(
        "go", [this]() {
            if (mScene && mScene->mIsAlive) {
                GameDataHolder* holder = (GameDataHolder*)al::getSceneObj(mScene, 20);
                if (holder)

                {
                    int scenario = getConfig()->mSelectedScenario;
                    if (scenario == 0)
                        scenario = -1;
                    ChangeStageInfo info = ChangeStageInfo(holder, "start", sStageNames[getConfig()->mSelectedStageIdx], false, scenario, { 0 });
                    holder->changeNextStage(&info, 0);
                }
            }
        },
        true));

    mCategories[4].name = "settings";
    mCategories[4].components.allocBuffer(2, nullptr);
    static constexpr const char* languageNames[] {
        "English", "日本語", "Deutsch"
    };
    mCategories[4].components.pushBack(new EnumMenuComponent<int>(reinterpret_cast<int*>(&getConfig()->currentLanguage), languageNames, "Language", false, false));
    mCategories[4].components.pushBack(new IntMenuComponent<int>(&getConfig()->mWheelDelayFrames, "wheeltime", 1, 40, true));

    mComponents.allocBuffer(4, nullptr);
    mComponents.pushBack(new QuickActionMenu(*this));
    mComponents.pushBack(new Timer);
    mComponents.pushBack(new MofumofuPatternUpdateNotification);
}

void Menu::update(al::Scene* scene)
{
    mScene = scene;

    if (mTimer % 3600 == 0) {
        pe::saveConfig();
    }
    mTimer++;

    for (int i = 0; i < mComponents.size(); i++) {
        IComponent* component = mComponents[i];
        if (component)
            component->update();
    }
}

void Menu::draw()
{
    updateInput();

    ImGui::GetIO().FontGlobalScale = .5;

    for (int i = 0; i < mComponents.size(); i++) {
        IComponent* component = mComponents[i];
        if (component)
            component->draw();
    }

    if (!mIsEnabled) {
        if (al::isPadTriggerUp(-1))
            callAction(getConfig()->mDUpBind);
        if (al::isPadTriggerDown(-1))
            callAction(getConfig()->mDDownBind);
        if (al::isPadTriggerLeft(-1) && !al::isPadHoldL(-1))
            callAction(getConfig()->mDLeftBind);
        if (al::isPadTriggerRight(-1))
            callAction(getConfig()->mDRightBind);
        if ((al::isPadHoldZL(-1) and al::isPadTriggerZR(-1)) or (al::isPadHoldZR(-1) and al::isPadTriggerZL(-1)))
            callAction(getConfig()->mZLZRBind);
        if (al::isPadHoldPressRightStick(-1) && al::isPadTriggerL(-1))
            callAction(getConfig()->mRsLBind);
        if (al::isPadHoldPressRightStick(-1) && al::isPadTriggerR(-1))
            callAction(getConfig()->mRsRBind);
        return;
    }

    mBgSize = ImVec2(0, 0);
    for (int i = 0; i < IM_ARRAYSIZE(mCategories); i++) {
        ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(sCategoryFontSize, FLT_MAX, 0.f, pe::getLocalizedString(mCategories[i].name));

        int width = sCategorySpacing + textSize.x + sCategorySpacing;
        mBgSize.x = std::max(mBgSize.x, (float)width);
    }
    mBgSize.y += getCategoryHeight(IM_ARRAYSIZE(mCategories));

    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, 0), mBgSize, IM_COL32(0, 0, 0, 128));
    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(0, getCategoryHeight(mCurrentCategory)), ImVec2(mBgSize.x, getCategoryHeight(mCurrentCategory + 1)), IM_COL32(255, 255, 255, 76));

    ImVec2 size = ImVec2(0, 0);
    for (int i = 0; i < IM_ARRAYSIZE(mCategories); i++) {
        ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[0]->CalcTextSizeA(sCategoryFontSize, FLT_MAX, 0.f, pe::getLocalizedString(mCategories[i].name));
        size.y += sCategorySpacing;

        ImGui::GetForegroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[0], sCategoryFontSize, ImVec2(size.x + sCategorySpacing, size.y), IM_COL32(255, 255, 255, 255), pe::getLocalizedString(mCategories[i].name));

        size.y += textSize.y;
        size.y += sCategorySpacing;
    }

    if (mIsExpandedCurrentCategory)
        drawExpandedCategory();
}

void Menu::drawExpandedCategory()
{
    auto& cat = mCategories[mCurrentCategory];
    if (mCurrentComponentInCategory >= cat.components.size())
        mCurrentComponentInCategory = cat.components.size() - 1;
    int subX = 0, subY = 0;
    int y = getCategoryHeight(mCurrentCategory);

    for (int i = 0; i < cat.components.size(); i++) {
        MenuComponent* component = cat.components[i];
        if (component == nullptr)
            continue;
        ImVec2 size = component->getSize();
        subX = std::max((float)subX, size.x);
        subY += size.y;
    }

    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(mBgSize.x, y), ImVec2(mBgSize.x + subX, y + subY), IM_COL32(0, 0, 0, 128));

    getCurrentCategory().components[mCurrentComponentInCategory]->setIsHovered(true);

    subY = 0;
    {
        for (int i = 0; i < cat.components.size(); i++) {
            MenuComponent* component = cat.components[i];
            if (component == nullptr)
                continue;

            ImVec2 size = component->getSize();
            ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(mBgSize.x, y + subY), ImVec2(mBgSize.x + subX, y + subY + size.y), IM_COL32(0, 0, 0, 128));
            if (mCurrentComponentInCategory == i) {
                ImU32 color = mIsFocusedOnCurrentComponent ? IM_COL32(255, 60, 60, 76) : IM_COL32(255, 255, 255, 76);
                ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(mBgSize.x, y + subY), ImVec2(mBgSize.x + subX, y + subY + size.y), color);
            }
            component->draw(ImVec2(mBgSize.x, y + subY));
            component->setIsHovered(false);

            subY += size.y;
        }
    }
}

void Menu::updateInput()
{
    if (al::isPadHoldL(-1) && al::isPadTriggerLeft(-1)) {
        mIsEnabled = !mIsEnabled;
        return;
    }

    if (!mIsExpandedCurrentCategory) {
        if (al::isPadTriggerDown(-1)) {
            mCurrentCategory++;
        } else if (al::isPadTriggerUp(-1)) {
            mCurrentCategory--;
        }

        if (al::isPadTriggerRight(-1)) {
            mIsExpandedCurrentCategory = true;
        }
    } else {
        if (!mIsFocusedOnCurrentComponent) {
            if (al::isPadTriggerDown(-1)) {
                mCurrentComponentInCategory++;
            } else if (al::isPadTriggerUp(-1)) {
                mCurrentComponentInCategory--;
            } else if (al::isPadTriggerLeft(-1)) {
                mIsExpandedCurrentCategory = false;
            }
        }

        if (mCurrentComponentInCategory < 0)
            mCurrentComponentInCategory = 0;
        if (mCurrentComponentInCategory >= getCurrentCategory().components.size())
            mCurrentComponentInCategory = getCurrentCategory().components.size() - 1;

        if (getCurrentCategory().components[mCurrentComponentInCategory]->canHaveFocus() && mIsEnabled) {
            if (al::isPadTriggerA(-1))
                mIsFocusedOnCurrentComponent = !mIsFocusedOnCurrentComponent;
            getCurrentCategory().components[mCurrentComponentInCategory]->setIsFocused(mIsFocusedOnCurrentComponent);
        } else
            mIsFocusedOnCurrentComponent = false;
    }

    if (mCurrentCategory >= IM_ARRAYSIZE(mCategories))
        mCurrentCategory = IM_ARRAYSIZE(mCategories) - 1;
    if (mCurrentCategory < 0)
        mCurrentCategory = 0;
}

void Menu::savePosition(al::LiveActor* playerBase)
{
    if (PlayerActorHakoniwa* player = util::typeCast<PlayerActorHakoniwa>((al::LiveActor*)playerBase)) {
        al::LiveActor* hack = player->getCurrentHack();
        al::LiveActor* move = hack != nullptr ? hack : player;

        mSavedPosition = al::getTrans(move);
        mSavedQuat = move->getPoseKeeper()->getQuat();
        mIsSavedPos = true;
    }
}

void Menu::loadPosition(al::LiveActor* playerBase)
{
    if (!mIsSavedPos)
        return;
    if (PlayerActorHakoniwa* player = util::typeCast<PlayerActorHakoniwa>((al::LiveActor*)playerBase)) {
        al::LiveActor* hack = player->getCurrentHack();
        al::LiveActor* move = hack != nullptr ? hack : player;

        if (hack == nullptr)
            player->startDemoPuppetableSuperReal();

        al::offCollide(move);

        al::setTrans(move, mSavedPosition);
        al::updatePoseQuat(move, mSavedQuat);

        if (hack == nullptr)
            player->endDemoPuppetableSuperReal();

        al::onCollide(move);
    }
}

void Menu::callAction(ActionType type)
{
    if (mScene && mScene->mIsAlive) {
        const al::Nerve* nrv = mScene->getNerveKeeper()->getCurrentNerve();
        bool allowedNerve = (nrv == util::getNerveAt(offsets::StageSceneNrvPlay) || nrv == util::getNerveAt(offsets::StageSceneNrvShineGet));
        uintptr_t typeInfo = *reinterpret_cast<uintptr_t*>(pe::util::getVft(nrv) - 8);
        const char** typeName = reinterpret_cast<const char**>(typeInfo + 8);
        if (strstr(*typeName, "StageSceneNrvDemo") or allowedNerve) {
            PlayerActorBase* playerBase = reinterpret_cast<PlayerActorBase*>(rs::getPlayerActor(mScene));
            switch (type) {
            case ActionType::KillScene: {
                mScene->kill();
                return;
            }
            case ActionType::PrevScene: {
                StageScene* scene = static_cast<StageScene*>(mScene);
                scene->mHolder->returnPrevStage();
                return;
            }
            case ActionType::SavePosition: {
                if (playerBase)
                    savePosition(playerBase);

                return;
            }
            case ActionType::LoadPosition: {
                if (playerBase)
                    loadPosition(playerBase);
                return;
            }
            case ActionType::LifeMaxUp:
                GameDataFunction::getLifeMaxUpItem(static_cast<PlayerActorHakoniwa*>(playerBase));
                return;
            default:
                break;
            }
        }
    }

    switch (type) {
    case ActionType::StartTimer:
        Timer::sInstance->start();
        return;
    case ActionType::StopTimer:
        Timer::sInstance->stop();
        return;
    case ActionType::ResetTimer:
        Timer::sInstance->reset();
        return;
    default:
        break;
    }

    if (type == ActionType::PrevMofumofuPattern or type == ActionType::NextMofumofuPattern) {
        int& pattern = *reinterpret_cast<int*>(&getConfig()->mCurPattern);

        if (type == ActionType::PrevMofumofuPattern)
            pattern--;
        else
            pattern++;

        if (pattern > 22)
            pattern = 0;
        if (pattern < 0)
            pattern = 22;
        MofumofuPatternUpdateNotification::sInstance->setUpdated();
        return;
    }
}

} // namespace pe
