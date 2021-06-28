//
// Created by Igor Obradovic.
//
#include <common/ScreenSize.hpp>
#include <game/state/impl/GameState.hpp>

namespace machine
{

GameState::GameState(common::GameData& gameData)  //
    : State{}
    , m_GameData{ gameData }
    , m_Background{ m_GameData.resource().texture("Background") }
    , m_Board{ m_GameData.boardDimensions().first,
               m_GameData.boardDimensions().second,
               m_GameData.resource(),
               m_GameData.players() }

    , m_Rectangle{ { (float) screenWidth, (float) screenHeight } }
    , m_FadeAnimation{ &m_Rectangle, 3.5 }
    , m_Timeout{ [this]() { m_FadeAnimation.startAnimation(); }, 0.0 }
{
}

void GameState::update(float const deltaTime)
{
    m_Board.update(deltaTime);
    m_FadeAnimation.updateAnimation(deltaTime);
    if (m_Board.isGameOver())
    {
        m_Timeout.update(deltaTime);
        if (m_FadeAnimation.isOver())
        {
            m_GameData.switchState(StateType::END);
        }
    }
}

void GameState::handleInput()
{
    sf::Event         eventToProcess{};
    sf::RenderWindow& window = m_GameData.window();
    while (window.pollEvent(eventToProcess))
    {
        if (eventToProcess.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }

        m_Board.handleInput((sf::Vector2i) window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    }
}

void GameState::draw()
{
    auto& window = m_GameData.window();

    window.clear();
    window.setView(window.getDefaultView());
    window.draw(m_Background);

    window.draw(m_Rectangle);
    m_Board.draw(window);
    window.display();
}

}  // namespace machine
