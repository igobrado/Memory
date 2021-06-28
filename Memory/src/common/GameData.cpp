//
// Created by Igor Obradovic.
//
#include <common/GameData.hpp>
#include <common/ScreenSize.hpp>
#include <game/state/StateFactory.hpp>

namespace common
{

GameData::GameData(char const* applicationName)  //
    : m_Window{ sf::VideoMode(screenWidth, screenHeight), applicationName }
    , m_StateMachine{}
    , m_ResourceHolder{}
    , m_BoardDimensions{ 4, 4 }
{
    m_Window.setFramerateLimit(60);
    m_ResourceHolder.setRepeatPlaying("music");
    m_ResourceHolder.play("music");
}

sf::RenderWindow& GameData::window()
{
    return m_Window;
}

::machine::StateMachine& GameData::machine()
{
    return m_StateMachine;
}

void GameData::switchState(::machine::StateType stateType)
{
    m_StateMachine.addState(StateFactory::getState(stateType, *this));
}

void GameData::insertPlayer(std::string playerName)
{
    m_Players.push_back(std::make_unique<Player>(std::move(playerName), m_ResourceHolder.font("MyFont")));
}

void GameData::setBoardDimensions(const std::pair<std::uint32_t, std::uint32_t>& dimension)
{
    m_BoardDimensions = dimension;
}

Players& GameData::players()
{
    return m_Players;
}

std::pair<std::uint32_t, std::uint32_t> const& GameData::boardDimensions() const
{
    return m_BoardDimensions;
}

ResourceHolder& GameData::resource()
{
    return m_ResourceHolder;
}

}  // namespace common
