//
// Created by Igor Obradovic.
//
#include <cstring>
#include <resource/gui/impl/Counter.hpp>

Counter::Counter(
        char const*             name,
        char const*             text,
        sf::Font const&         font,
        sf::RenderWindow const& parent,
        std::uint32_t           posX,
        std::uint32_t           posY,
        std::uint32_t           width,
        std::uint32_t           height,
        unsigned int            fontSize,
        std::uint16_t           outlineThickness,
        const char*             referencedLabelName)
    : ButtonImpl{ name,  //
                  text, font, parent, posX, posY, posX + 2, posY - 1, width, height, fontSize, outlineThickness }
    , m_ReferencedLabel{ nullptr }
    , m_ReferencedLabelName{ referencedLabelName }
    , m_IsIncreaser{ strcmp(text, "+") == 0 }
    , m_IncreaseCount{ 1 }
{
    *this += [this]() {
        if (m_IsIncreaser)
        {
            increase();
        }
        else
        {
            decrease();
        }
    };
}

std::string const& Counter::referencedLabelName() const
{
    return m_ReferencedLabelName;
}

void Counter::setReferencedLabel(LabelImpl& referencedLabel)
{
    m_ReferencedLabel = &referencedLabel;
}

std::string Counter::text() const
{
    if (m_ReferencedLabel)
    {
        return m_ReferencedLabel->text();
    }
    return "";
}

void Counter::increase()
{
    if (m_ReferencedLabel)
    {
        auto rawValue = extractCount<sf::String>(m_ReferencedLabel->text());
        if (rawValue != std::numeric_limits<std::uint32_t>::max())
        {
            m_ReferencedLabel->changeText(std::to_string(rawValue += m_IncreaseCount));
        }
    }
}

void Counter::decrease()
{
    if (m_ReferencedLabel)
    {
        auto rawValue = extractCount<sf::String>(m_ReferencedLabel->text());
        if (rawValue != std::numeric_limits<std::uint32_t>::max())
        {
            m_ReferencedLabel->changeText((rawValue == 0) ? "0" : std::to_string(rawValue -= m_IncreaseCount));
        }
    }
}

ComponentType Counter::type()
{
    return ComponentType::kCounter;
}

template <typename T>
std::uint32_t Counter::extractCount(const T& rawString)
{
    try
    {
        return std::stoi(std::string{ rawString.begin(), rawString.end() });
    }
    catch (const std::invalid_argument&)  // not likely but still ..
    {
        return -1;
    }
}
