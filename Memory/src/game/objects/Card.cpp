//
// Created by Igor Obradovic.
//
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Mouse.hpp>
#include <game/objects/Card.hpp>

Card::Card(const sf::Texture& cardBackground, const sf::Texture& cardForeground, CardType type)
    : m_CardBackground{ cardBackground }
    , m_CardForeground{ cardForeground }
    , m_ActiveSprite{ &m_CardBackground }
    , m_CardAnimation{ m_ActiveSprite, 0.6f, m_CardBackground.getTexture(), m_CardForeground.getTexture() }
    , m_RevealStatus{ RevealStatus::kNotRevealed }
    , m_Type{ type }
    , m_ShouldFlip{ false }
{
}

void Card::update(float const deltaTime)
{
    m_CardAnimation.updateAnimation(deltaTime);
}

bool Card::handleInput(sf::Vector2i mousePosition, std::function<void()> onFlipCallback)
{
    if ((isRevealed()) || (!isAnimationOver()))
    {
        return false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (m_ActiveSprite->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
        {
            m_CardAnimation.startAnimation();
            onFlipCallback();
            return true;
        }
    }

    return false;
}

void Card::setPosition(sf::Vector2f pos)
{
    sf::Vector2f backgroundSize = (sf::Vector2f) m_CardBackground.getTexture()->getSize();
    sf::Vector2f foregroundSize = (sf::Vector2f) m_CardForeground.getTexture()->getSize();

    m_CardForeground.setOrigin({ foregroundSize.x / 2, foregroundSize.y / 2 });
    m_CardBackground.setOrigin({ backgroundSize.x / 2, backgroundSize.y / 2 });

    float posX{ pos.x * backgroundSize.x + 10.f * pos.x + backgroundSize.x / 2 };
    float posY{ pos.y * backgroundSize.y + 10.f * pos.y + backgroundSize.y / 2 };

    m_CardBackground.setPosition({ posX, posY });
    m_CardForeground.setPosition({ posX, posY });
}

void Card::reveal()
{
    m_RevealStatus = RevealStatus::kRevealed;
}

void Card::flipCard(std::function<void()> onFlipCallback)
{
    m_RevealStatus = RevealStatus::kNotRevealed;
    m_CardAnimation.startAnimation();
    onFlipCallback();
}

bool Card::isRevealed() const
{
    return m_RevealStatus == RevealStatus::kRevealed;
}

bool Card::isAnimationOver() const
{
    return m_CardAnimation.isOver();
}

sf::Vector2u Card::getSize() const
{
    return m_CardBackground.getTexture()->getSize();
}

Card::operator sf::Sprite&()
{
    return *m_ActiveSprite;
}

bool Card::operator==(const Card& other) const
{
    return m_Type == other.m_Type;
}

bool Card::operator!=(const Card& other) const
{
    return !(*this == other);
}
