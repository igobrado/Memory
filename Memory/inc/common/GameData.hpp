//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <game/objects/Player.hpp>
#include <game/state/StateMachine.hpp>
#include <list>
#include <resource/managers/ResourceHolder.hpp>

namespace common
{

using Players = std::vector<std::unique_ptr<Player>>;

class GameData
{
public:
    explicit GameData(char const* applicationName);

    sf::RenderWindow&        window();
    ::machine::StateMachine& machine();
    ResourceHolder&          resource();
    void                     switchState(::machine::StateType stateType);
    void                     insertPlayer(std::string playerName);
    void                     setBoardDimensions(const std::pair<std::uint32_t, std::uint32_t>& dimension);
    Players&                 players();

    std::pair<std::uint32_t, std::uint32_t> const& boardDimensions() const;

private:
    sf::RenderWindow        m_Window;
    ::machine::StateMachine m_StateMachine;
    ResourceHolder          m_ResourceHolder;
    Players                 m_Players;

    std::pair<std::uint32_t, std::uint32_t> m_BoardDimensions;
};

}  // namespace common
