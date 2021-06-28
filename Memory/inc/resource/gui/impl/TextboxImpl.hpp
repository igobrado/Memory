//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <resource/gui/components/ITextbox.hpp>

class TextboxImpl final : public ITextbox
{
public:
    TextboxImpl(
            const char*             name,
            unsigned int const      characterSize,
            std::uint32_t const     textboxWidth,
            std::uint32_t const     textboxHeight,
            std::uint32_t const     textboxPositionX,
            std::uint32_t const     textboxPositionY,
            std::uint32_t const     outlineThickness,
            sf::Font const&         font,
            sf::RenderWindow const& parent);

    void               clear();
    std::string        text() const override;
    void               handleInput(sf::Event& event) override;
    std::string const& name() const override;

protected:
    void onClick() override;
    void checkTextChanged(sf::Uint64 const unicode) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool        isClickInBounds();
    std::string processTextChanged(sf::Text& currentText, sf::Uint32 const unicode);

    bool isInTextbox(sf::Text const& currentText, sf::Uint32 const unicode);

private:
    std::string const       m_Name;
    sf::RectangleShape      m_Rectangle;
    sf::Font const&         m_Font;
    bool                    m_Focused;
    sf::Text                m_Text;
    sf::RenderWindow const& m_Parent;
};
