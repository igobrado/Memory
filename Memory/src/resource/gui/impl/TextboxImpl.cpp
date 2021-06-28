//
// Created by Igor Obradovic.
//
#include <common/ComponentBackgroundColorConstants.hpp>
#include <resource/gui/impl/TextboxImpl.hpp>

TextboxImpl::TextboxImpl(
        const char*             name,
        unsigned int const      characterSize,
        std::uint32_t const     textboxWidth,
        std::uint32_t const     textboxHeight,
        std::uint32_t const     textboxPositionX,
        std::uint32_t const     textboxPositionY,
        std::uint32_t const     outlineThickness,
        sf::Font const&         font,
        sf::RenderWindow const& parent)
    : m_Name{ name }
    , m_Rectangle{}
    , m_Font{ font }
    , m_Focused{ false }
    , m_Parent{ parent }
{
    m_Text.setFont(font);
    m_Text.setCharacterSize(characterSize);
    m_Text.setPosition(textboxPositionX, textboxPositionY);

    m_Rectangle.setSize(sf::Vector2f(textboxWidth, textboxHeight));
    m_Rectangle.setPosition(sf::Vector2f(textboxPositionX, textboxPositionY));
    m_Rectangle.setFillColor(sBackgroundColor);
    m_Rectangle.setOutlineColor(sOutlineColor);
    m_Rectangle.setOutlineThickness(outlineThickness);
}

void TextboxImpl::clear()
{
    m_Text.setString("");
}

std::string TextboxImpl::text() const
{
    return m_Text.getString();
}

void TextboxImpl::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        onClick();
    }
    else if (event.type == sf::Event::TextEntered)
    {
        checkTextChanged(event.text.unicode);
    }
}

std::string const& TextboxImpl::name() const
{
    return m_Name;
}

void TextboxImpl::onClick()
{
    bool isInBounds = isClickInBounds();

    if ((isInBounds) && (!m_Focused))
    {
        m_Focused = true;
        m_Rectangle.setOutlineColor(sActiveOutlineColor);
    }
    else if ((!isInBounds) && (m_Focused))
    {
        m_Rectangle.setOutlineColor(sOutlineColor);
        m_Focused = false;
    }
}

bool TextboxImpl::isClickInBounds()
{
    auto const& pos = sf::Mouse::getPosition(m_Parent);
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (m_Rectangle.getGlobalBounds().contains(pos.x, pos.y)))
    {
        return true;
    }

    return false;
};

void TextboxImpl::checkTextChanged(sf::Uint64 const unicode)
{
    if (m_Focused)
    {
        auto changedText = processTextChanged(m_Text, unicode);
        m_Text.setString(changedText);
    }
}

std::string TextboxImpl::processTextChanged(sf::Text& currentText, const sf::Uint32 unicode)
{
    sf::String playerText         = currentText.getString();
    bool       isBackspacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace);

    if (isInTextbox(currentText, unicode))
    {
        if ((isBackspacePressed) && (playerText.getSize()))
        {
            playerText.erase(playerText.getSize() - 1);
        }
        else if (!isBackspacePressed)
        {
            playerText += unicode;
        }
    }

    return { playerText.begin(), playerText.end() };
}

bool TextboxImpl::isInTextbox(sf::Text const& currentText, sf::Uint32 const unicode)
{
    sf::String const& playerText = currentText.getString();
    sf::Text          tex{ currentText };
    tex.setString(playerText + unicode);
    if (tex.getGlobalBounds().width > m_Rectangle.getGlobalBounds().width)
    {
        return false;
    }
    return true;
}

void TextboxImpl::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const
{
    target.draw(m_Rectangle);
    target.draw(m_Text);
}
