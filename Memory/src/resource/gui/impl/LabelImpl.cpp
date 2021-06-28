//
// Created by Igor Obradovic.
//
#include <resource/gui/impl/LabelImpl.hpp>

LabelImpl::LabelImpl(
        sf::Font const&     font,
        std::string         labelName,
        std::string         text,
        std::uint32_t const fontSize,
        std::uint32_t const positionX,
        std::uint32_t const positionY)
    : m_Text{ text, font }
    , m_LabelName{ std::move(labelName) }
    , m_ShouldDraw{ true }
{
    m_Text.setFillColor(sf::Color::White);
    m_Text.setOutlineColor(sf::Color::Black);
    m_Text.setOutlineThickness(1);
    m_Text.setCharacterSize(fontSize);
    m_Text.setPosition({ (float) positionX, (float) positionY });
}

void LabelImpl::changeText(std::string const& textToSet)
{
    m_Text.setString(sf::String{ textToSet.c_str() });
}

std::string const& LabelImpl::name() const
{
    return m_LabelName;
}

std::string LabelImpl::text() const
{
    return m_Text.getString();
}

sf::RectangleShape& LabelImpl::rect()
{
    return m_RectangleShape;
}

void LabelImpl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_ShouldDraw)
    {
        target.draw(m_RectangleShape, states);
        target.draw(m_Text, states);
    }
}

void LabelImpl::setVisibility(bool visiblity)
{
    m_ShouldDraw = visiblity;
}
