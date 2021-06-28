//
// Created by Igor Obradovic.
//
#include <common/Math.hpp>
#include <common/ScreenSize.hpp>
#include <game/objects/TableHud.hpp>

static sf::Color const sInactiveHudColor{ 0, 0, 0, 10 };  // NOLINT: No constexpr.
static sf::Color const sActiveHudColor{ 0, 0, 0, 100 };   // NOLINT: No constexpr.

// clang-format off
const PlayerPositions  TableHud::sPlayersPositions
{
    sf::Vector2f{ half(screenWidth)                   , screenHeight - half(sHudPieceHeight) },
    sf::Vector2f{ screenWidth - half(sHudPieceHeight) , half(screenHeight ) },
    sf::Vector2f{ half(screenWidth)                   , half(sHudPieceHeight) },
    sf::Vector2f{ half(sHudPieceHeight)               , half(screenWidth) }
};
// clang-format on

const Rotations TableHud::sRotations{ 0.f, 270.f, 180.f, 90.f };

TableHud::TableHud(common::Players& players)  //
    : m_Players{ players }
    , m_TableView{ sf::FloatRect(0.f, 0.f, screenWidth, screenHeight) }
    , m_Animation{ &m_TableView, 0.3f }
    , m_NextPlayerIndex{ 0 }
    , m_CurrentPlayersIndex{ 0 }
{
    for (int i = 0; i < sBorderQuantity; ++i)
    {
        m_Hud[i] = getHudPiece(
                sf::Vector2f{ half(screenWidth), half(sHudPieceHeight) },
                screenWidth,
                sRotations[i],
                sPlayersPositions[i]);
    }

    alignPlayersWithHud();
}

void TableHud::update(float const deltaTime)
{
    m_Animation.updateAnimation(deltaTime);
    if (m_Animation.isOver())
    {
        for (auto& hud : m_Hud)
        {
            hud.setFillColor(sInactiveHudColor);
        }
    }
}

void TableHud::rotate(float const rotationAngle, float const duration)
{
    m_Animation.setRotationDuration(duration);
    m_Animation.setRotationAngle(rotationAngle);

    for (auto& hud : m_Hud)
    {
        hud.setFillColor(sActiveHudColor);
    }

    m_Animation.startAnimation();
}

void TableHud::draw(sf::RenderWindow& window)
{
    window.setView(m_TableView);

    for (const auto& hud : m_Hud)
    {
        window.draw(hud);
    }

    for (auto const& playerName : m_Players)
    {
        playerName->drawPlayerName(window);
    }
}

void TableHud::nextPlayer()
{
    if (m_Players.size() == 1)
    {
        return;
    }

    if ((m_Players.size() == 2) || ((m_Players.size() == 3) && (m_CurrentPlayersIndex == 2)))
    {
        rotate(180, 3.f);
    }
    else
    {
        rotate(90, 1.9f);
    }

    if (m_Players.size() > 4)
    {
        m_Players[m_CurrentPlayersIndex]->setColor(sf::Color::Transparent);
        int newPlayer = m_CurrentPlayersIndex + 4;
        if (newPlayer < m_Players.size())
        {
            setPlayerLocationAndRotation(m_Players[newPlayer], m_NextPlayerIndex % 4);
            m_Players[newPlayer]->setColor(sf::Color::White);
        }
        else
        {
            setPlayerLocationAndRotation(m_Players[newPlayer - m_Players.size()], m_NextPlayerIndex % 4);
            m_Players[newPlayer - m_Players.size()]->setColor(sf::Color::White);
        }
        ++m_NextPlayerIndex;
    }

    m_CurrentPlayersIndex = (m_CurrentPlayersIndex + 1 < m_Players.size()) ? ++m_CurrentPlayersIndex : 0;
}

bool TableHud::isRotationOver()
{
    return m_Animation.isOver();
}

Player& TableHud::currentPlayer()
{
    return *m_Players[m_CurrentPlayersIndex];
}

void TableHud::alignPlayersWithHud()
{
    if (m_Players.size() == 2)
    {
        initializeTwoPlayerBoard();
    }
    else
    {
        initializeBoard();  // will be called when there is only one player, but that is ok.
    }
}

void TableHud::initializeTwoPlayerBoard()
{
    // 0 - 2 index, players shall be on the opposite side, so 0 - 180
    m_Players[0]->setPlayerNamePosition(sPlayersPositions[0]);
    m_Players[0]->setPlayerNameRotation(sRotations[0]);

    m_Players[1]->setPlayerNamePosition(sPlayersPositions[2]);
    m_Players[1]->setPlayerNameRotation(sRotations[2]);
}

void TableHud::initializeBoard()
{
    int i = 0;
    for (auto& player : m_Players)
    {
        if (i < 4)
        {
            setPlayerLocationAndRotation(player, i);
        }
        else
        {
            player->setColor(sf::Color::Transparent);
        }

        ++i;
    }
}

sf::RectangleShape TableHud::getHudPiece(
        sf::Vector2f const& origin,  //
        float const         width,
        float const         rotation,
        sf::Vector2f const& pos)
{
    sf::RectangleShape hud{ { width, sHudPieceHeight } };

    hud.setFillColor(sInactiveHudColor);
    hud.setOrigin(origin);
    hud.setPosition(pos);
    hud.setRotation(rotation);

    return hud;
}

void TableHud::setPlayerLocationAndRotation(std::unique_ptr<Player>& player, int playerIndex)
{
    player->setPlayerNamePosition(sPlayersPositions[playerIndex]);
    player->setPlayerNameRotation(sRotations[playerIndex]);
}
