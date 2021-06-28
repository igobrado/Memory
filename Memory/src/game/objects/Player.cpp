//
// Created by Igor Obradovic.
//
#include <common/Math.hpp>
#include <game/objects/Player.hpp>

Player::Player(std::string playerName, sf::Font const& font)
    : m_Score{ 0u }
    , m_Font{ font }
    , m_PlayerName{ playerName, font }
    , m_PlayerScore{ std::to_string(m_Score), font }
{
}

void Player::reset()
{
    m_PlayerScore.setFillColor(sf::Color::White);
    m_PlayerName.setFillColor(sf::Color::White);
    m_PlayerScore.setPosition({ 0.0f, 0.0f });
    m_PlayerName.setPosition({ 0.0f, 0.0f });
    m_PlayerName.setOrigin({ 0, 0 });
    m_PlayerScore.setOrigin({ 0, 0 });
}

void Player::increaseScore()
{
    m_PlayerScore.setString(std::to_string(++m_Score));
}

void Player::drawPlayerName(sf::RenderWindow& window)
{
    window.draw(m_PlayerName);
}

void Player::drawPlayerScore(sf::RenderWindow& window)
{
    window.draw(m_PlayerScore);
}

void Player::setColor(sf::Color color)
{
    m_PlayerName.setFillColor(color);
}

void Player::setPlayerNamePosition(sf::Vector2f const playerNamePosition, bool setOrigin)
{
    auto width  = setOrigin ? m_PlayerName.getLocalBounds().width : 0;
    auto height = setOrigin ? m_PlayerName.getCharacterSize() : 0;

    m_PlayerName.setOrigin(half(width), half(height));
    m_PlayerName.setPosition(playerNamePosition);
}

void Player::setPlayerNameRotation(float const playerNameRotation)
{
    m_PlayerName.setRotation(playerNameRotation);
}

void Player::setPlayerScorePosition(sf::Vector2f const scorePosition)
{
    m_PlayerScore.setPosition(scorePosition);
}

void Player::setFontSize(std::uint16_t const size)
{
    m_PlayerScore.setCharacterSize(size);
    m_PlayerName.setCharacterSize(size);
}

std::uint16_t Player::fontSize()
{
    return m_PlayerName.getCharacterSize();
}

std::uint64_t const Player::score() const
{
    return m_Score;
}
