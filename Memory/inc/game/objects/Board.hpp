//
// Created by Igor Obradovic.
//
#pragma once

#include <cinttypes>
#include <common/GameData.hpp>
#include <game/animations/Timeout.hpp>
#include <game/objects/Card.hpp>
#include <game/objects/Player.hpp>
#include <game/objects/TableHud.hpp>
#include <list>
#include <memory>
#include <resource/managers/ResourceHolder.hpp>
#include <vector>

class Board
{
public:
    Board(std::uint32_t    boardWidth,
          std::uint32_t    boardHeight,
          ResourceHolder&  resourceHolder,
          common::Players& players);

    void update(float const deltaTime);
    void handleInput(sf::Vector2i const mousePos);
    void draw(sf::RenderWindow& window);
    bool isGameOver();

protected:
    void initialize(std::uint32_t boardWidth, std::uint32_t boardHeight, ResourceHolder& resourceHolder);

private:
    using Deck       = std::vector<std::unique_ptr<Card>>;
    using DeckCardIt = Deck::iterator;

    Deck     m_Deck;
    TableHud m_TableHud;
    sf::View m_BoardView;
    Timeout  m_Timeout;

    DeckCardIt      m_RevealedCard;

    std::function<void()> m_FlipSoundCallback;
};