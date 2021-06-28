//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Player
{
public:
    Player(std::string playerName, sf::Font const& font);

    void reset();
    void increaseScore();
    void drawPlayerName(sf::RenderWindow& window);
    void drawPlayerScore(sf::RenderWindow& window);

    void setColor(sf::Color color);
    void setPlayerNamePosition(sf::Vector2f const playerNamePosition, bool setOrigin = true);
    void setPlayerNameRotation(float const playerNameRotation);
    void setPlayerScorePosition(sf::Vector2f const scorePosition);
    void setFontSize(std::uint16_t const size);

    std::uint16_t       fontSize();
    std::uint64_t const score() const;

private:
    std::uint64_t   m_Score;
    sf::Font const& m_Font;
    sf::Text        m_PlayerName;
    sf::Text        m_PlayerScore;
};
