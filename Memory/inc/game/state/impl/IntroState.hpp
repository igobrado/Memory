//
// Created by Igor Obradovic.
//
#pragma once

#include <common/GameData.hpp>
#include <game/animations/ScreenSwapAnimation.hpp>
#include <game/state/State.hpp>
#include <resource/gui/components/IGuiComponent.hpp>
#include <resource/gui/impl/Counter.hpp>
#include <game/animations/Timeout.hpp>

namespace machine
{

class IntroState : public State
{
public:
    explicit IntroState(::common::GameData& gameData);

    void update(float const deltaTime) override;
    void handleInput() override;
    void draw() override;

protected:
    std::string   textLocatedInTextbox(char const* textboxName);
    std::uint32_t numberLocatedInLabel(char const* labelName);
    void          toggleLabelVisibility(char const* labelName, bool visibility);
    void          populateCallbacks();

private:
    using GuiComponents = std::vector<std::unique_ptr<IGuiComponent>>;

    ::common::GameData& m_GameData;
    sf::Sprite          m_Background;
    GuiComponents       m_GuiComponents;
    Timeout m_Timeout;
};

}  // namespace machine
