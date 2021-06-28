//
// Created by Igor Obradovic.
//
#pragma once

#include <common/GameData.hpp>
#include <game/animations/ScreenSwapAnimation.hpp>
#include <game/animations/Timeout.hpp>
#include <game/objects/Board.hpp>
#include <game/state/State.hpp>

namespace machine
{

class GameState : public State
{
public:
    explicit GameState(::common::GameData& gameData);

    void update(float const deltaTime) override;
    void handleInput() override;
    void draw() override;

private:
    common::GameData&   m_GameData;
    sf::Sprite          m_Background;
    Board               m_Board;
    sf::RectangleShape  m_Rectangle;
    ScreenSwapAnimation m_FadeAnimation;
    Timeout             m_Timeout;
};

}  // namespace machine
