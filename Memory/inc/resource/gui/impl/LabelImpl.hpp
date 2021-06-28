//
// Created by Igor Obradovic.
//
#pragma once

#include <resource/gui/components/ILabel.hpp>

class LabelImpl final : public ILabel
{
public:
    LabelImpl(
            sf::Font const&     font,
            std::string         labelName,
            std::string         text,
            std::uint32_t const fontSize,
            std::uint32_t const positionX,
            std::uint32_t const positionY);

    void                changeText(std::string const& textToSet) override;
    std::string const&  name() const override;
    std::string         text() const override;
    sf::RectangleShape& rect();

    void setVisibility(bool visiblity);
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape m_RectangleShape;
    sf::Text           m_Text;
    std::string        m_LabelName;
    bool               m_ShouldDraw;
};
