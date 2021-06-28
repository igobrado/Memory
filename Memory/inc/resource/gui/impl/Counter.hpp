//
// Created by Igor Obradovic.
//
#pragma once

#include <resource/gui/impl/ButtonImpl.hpp>
#include <resource/gui/impl/LabelImpl.hpp>

class Counter : public ButtonImpl
{
public:
    Counter(char const*             name,
            char const*             text,
            sf::Font const&         font,
            sf::RenderWindow const& parent,
            std::uint32_t           posX,
            std::uint32_t           posY,
            std::uint32_t           width,
            std::uint32_t           height,
            unsigned int            fontSize,
            std::uint16_t           outlineThickness,
            const char*             referencedLabelName);

    std::string const& referencedLabelName() const;
    void               setReferencedLabel(LabelImpl& referencedLabel);
    std::string        text() const override;

    void increase();
    void decrease();

    ComponentType type() override;

protected:
    template <typename T = sf::String>
    std::uint32_t extractCount(const T& rawString);

private:
    LabelImpl*    m_ReferencedLabel;
    std::string   m_ReferencedLabelName;
    bool          m_IsIncreaser;
    std::uint32_t m_IncreaseCount;
};