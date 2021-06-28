//
// Created by Igor Obradovic.
//
#pragma once

#include <common/GameData.hpp>
#include <game/state/State.hpp>
#include <resource/gui/GUILoader.hpp>

namespace machine
{

class EndgameState : public State
{
public:
    explicit EndgameState(::common::GameData& gameData);

    void update(float const deltaTime) override;
    void handleInput() override;
    void draw() override;

private:
    void initializeScoreboard();
    void positionPlayers();
    void populateCallbacks();

    ::common::GameData& m_GameData;
    sf::Sprite          m_Background;

    std::vector<std::unique_ptr<IGuiComponent>> m_GuiComponents;
};

}  // namespace machine
