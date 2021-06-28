//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <game/animations/Timeout.hpp>
#include <resource/gui/components/IButton.hpp>

class ButtonImpl : public IButton
{
public:
    ButtonImpl(
            char const*             name,
            char const*             text,
            sf::Font const&         font,
            sf::RenderWindow const& parent,
            std::uint32_t           posX,
            std::uint32_t           posY,
            std::uint32_t           width,
            std::uint32_t           height,
            unsigned int            fontSize,
            std::uint16_t           outlineThickness);

    ButtonImpl(
            char const*             name,
            char const*             text,
            sf::Font const&         font,
            sf::RenderWindow const& parent,
            std::uint32_t           boxPosX,
            std::uint32_t           boxPosY,
            std::uint32_t           textPosX,
            std::uint32_t           textPosY,
            std::uint32_t           width,
            std::uint32_t           height,
            unsigned int            fontSize,
            std::uint16_t           outlineThickness);


    void               update(float const deltaTime) override;
    void               handleInput(sf::Event& event) override;
    std::string const& name() const override;
    std::string        text() const override;

    void operator+=(OnClickCheckCallback callback) override;

protected:
    void onClick() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool isInBounds();

private:
    sf::RenderWindow const& m_Parent;
    std::string const       m_Name;
    sf::Text                m_Text;
    sf::RectangleShape      m_Button;
    Timeout                 m_Timeout;

    std::vector<OnClickCheckCallback> m_OnClickCallbacks;
};
