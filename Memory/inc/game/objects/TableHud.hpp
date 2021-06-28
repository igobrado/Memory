//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <common/GameData.hpp>
#include <common/HudUtil.hpp>
#include <game/animations/TableRotationAnimation.hpp>

class TableHud
{
public:
    TableHud(common::Players& players);
    void update(float const deltaTime);
    void draw(sf::RenderWindow& window);
    void nextPlayer();
    bool isRotationOver();

    Player& currentPlayer();

protected:
    void rotate(float const rotationAngle, float const duration);
    void alignPlayersWithHud();
    void initializeTwoPlayerBoard();
    void initializeBoard();

    sf::RectangleShape getHudPiece(
            sf::Vector2f const& origin,  //
            float const         width,
            float const         rotation,
            sf::Vector2f const& pos);

    void setPlayerLocationAndRotation(std::unique_ptr<Player>& player, int playerIndex);
private:
    static const PlayerPositions sPlayersPositions;
    static const Rotations       sRotations;

    common::Players&       m_Players;
    sf::View               m_TableView;
    Hud                    m_Hud;
    TableRotationAnimation m_Animation;
    std::uint32_t          m_NextPlayerIndex;
    std::uint32_t          m_CurrentPlayersIndex;
};