//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <cinttypes>
#include <common/CardUtil.hpp>
#include <game/animations/CardFlipAnimation.hpp>

class Card
{
public:
    Card(const sf::Texture& cardBackground, const sf::Texture& cardForeground, CardType type);

    void update(float const deltaTime);
    bool handleInput(sf::Vector2i mousePosition, std::function<void()> onFlipCallback);
    void setPosition(sf::Vector2f pos);
    void reveal();
    void flipCard(std::function<void()> onFlipCallback);
    bool isRevealed() const;
    bool isAnimationOver() const;

    sf::Vector2u getSize() const;

         operator sf::Sprite&();
    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;

private:
    sf::Sprite m_CardBackground;
    sf::Sprite m_CardForeground;

    sf::Sprite*       m_ActiveSprite;
    CardFlipAnimation m_CardAnimation;
    RevealStatus      m_RevealStatus;
    CardType          m_Type;
    bool              m_ShouldFlip;
};