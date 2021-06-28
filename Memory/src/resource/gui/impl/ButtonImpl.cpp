//
// Created by Igor Obradovic.
//
#include <common/ComponentBackgroundColorConstants.hpp>
#include <resource/gui/impl/ButtonImpl.hpp>

ButtonImpl::ButtonImpl(
        char const*             name,
        char const*             text,
        sf::Font const&         font,
        sf::RenderWindow const& parent,
        std::uint32_t           posX,
        std::uint32_t           posY,
        std::uint32_t           width,
        std::uint32_t           height,
        unsigned int            fontSize,
        std::uint16_t           outlineThickness)
    : m_Parent{ parent }
    , m_Name{ name }
    , m_Text{ text, font, fontSize }
    , m_Timeout{ nullptr, 0.0f }
{
    m_Text.setPosition(posX, posY);

    auto textBounds = m_Text.getLocalBounds();
    m_Button.setSize({ textBounds.width + 20.f, textBounds.height + 20.f });

    m_Button.setPosition(posX - 7, posY);
    m_Button.setSize(sf::Vector2f(width, height));

    m_Button.setOutlineThickness(outlineThickness);

    m_Button.setFillColor(sBackgroundColor);
    m_Button.setOutlineColor(sOutlineColor);
    m_Text.setFillColor(sOutlineColor);
}

ButtonImpl::ButtonImpl(
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
        std::uint16_t           outlineThickness)
    : ButtonImpl{ name, text, font, parent, boxPosX, boxPosY, width, height, fontSize, outlineThickness }
{
    m_Text.setPosition(textPosX, textPosY);
}

void ButtonImpl::update(const float deltaTime)
{
    m_Timeout.update(deltaTime);
}

void ButtonImpl::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        onClick();
    }
}

std::string const& ButtonImpl::name() const
{
    return m_Name;
}

std::string ButtonImpl::text() const
{
    return m_Text.getString();
}

void ButtonImpl::operator+=(OnClickCheckCallback callback)
{
    if (callback)
    {
        m_OnClickCallbacks.push_back(std::move(callback));
    }
}

void ButtonImpl::onClick()
{
    if (isInBounds())
    {
        m_Button.setOutlineColor(sActiveOutlineColor);
        m_Text.setFillColor(sActiveOutlineColor);

        m_Timeout.reset(
                [this]() {
                    m_Button.setOutlineColor(sOutlineColor);
                    m_Text.setFillColor(sOutlineColor);
                },
                0.2f);
        for (auto const& callback : m_OnClickCallbacks)
        {
            callback();  // no need to check is callback valid, because bad callbacks are discarded while inserting
        }
    }
}

void ButtonImpl::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const
{
    target.draw(m_Text);
    target.draw(m_Button);
}
bool ButtonImpl::isInBounds()
{
    auto const& pos = sf::Mouse::getPosition(m_Parent);
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (m_Button.getGlobalBounds().contains(pos.x, pos.y)))
    {
        return true;
    }

    return false;
}
