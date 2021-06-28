//
// Created by Igor Obradovic.
//
#include <game/state/impl/EndgameState.hpp>

namespace machine
{

namespace
{

static constexpr char const* sRestartGame = "RestartGame";

}

EndgameState::EndgameState(common::GameData& gameData)  //
    : State{}
    , m_GameData{ gameData }
    , m_Background{ m_GameData.resource().texture("Background") }
    , m_GuiComponents{ GUILoader::instance().components(
              "../resource/xml/state/StateConfig.xml",
              "End",
              m_GameData.window(),
              m_GameData.resource().font("MyFont")) }
{
    if (m_GameData.players().size() > 1)
    {
        std::sort(m_GameData.players().begin(), m_GameData.players().end(), [](auto const& lhs, auto const& rhs) {
            return lhs->score() > rhs->score();
        });
    }
    initializeScoreboard();
    populateCallbacks();
}

void EndgameState::update(float const deltaTime)
{
}

void EndgameState::handleInput()
{
    sf::Event         eventToProcess{};
    sf::RenderWindow& window = m_GameData.window();
    while (window.pollEvent(eventToProcess))
    {
        if (eventToProcess.type == sf::Event::Closed)
        {
            window.close();
        }

        for (auto const& guiComponent : m_GuiComponents)
        {
            guiComponent->handleInput(eventToProcess);
        }
    }
}

void EndgameState::draw()
{
    auto& window = m_GameData.window();
    window.setView(window.getDefaultView());

    window.draw(m_Background);
    for (auto const& player : m_GameData.players())
    {
        player->drawPlayerName(window);
        player->drawPlayerScore(window);
    }

    for (auto const& guiComponent : m_GuiComponents)
    {
        window.draw(*guiComponent);
    }
    window.display();
}

void EndgameState::initializeScoreboard()
{
    auto&         players = m_GameData.players();
    std::uint64_t i       = 0;

    for (auto const& player : players)
    {
        player->setFontSize(48);
        // in case that it's first iteration, then next player is actually is second index of the vector
        auto next = (i == 0) ? players.begin() + 1 : players.begin() + i;

        if (next == std::end(players))  // in case that there is no players left
        {
            break;
        }

        if ((*next)->score() < player->score())  // if next player has smaller score then we should break
        {
            break;
        }
        ++i;
    }
    positionPlayers();
}

void EndgameState::positionPlayers()
{
    auto& players          = m_GameData.players();
    float playerListHeight = 100.f;
    float playerListIndent = 200.f;

    for (auto& player : players)
    {
        player->reset();
        player->setPlayerNameRotation(0);
        player->setPlayerNamePosition({ playerListIndent, playerListHeight }, false);
        player->setPlayerScorePosition({ playerListIndent + 200.f, playerListHeight });
        playerListHeight += static_cast<float>(player->fontSize() + 16);

        if (playerListHeight > 700.f)
        {
            playerListHeight = 100.f;
            playerListIndent += 400.f;
            if (playerListIndent > 700.f)
            {
                break;
            }
        }
    }
}
void EndgameState::populateCallbacks()
{
    OnClickCheckCallback okClickableCallback = [this]() {  //
        m_GameData.switchState(::machine::StateType::INTRO);
    };

    for (const auto& comp : m_GuiComponents)
    {
        if (comp->type() == ComponentType::kButton)
        {
            if (comp->name() == sRestartGame)
            {
                // in this case downcast is "ok" ( big emphasis on ok )
                // because we know the type, and the name of the component,
                // and we are 99% sure that it's an actual object we need.
                auto& button = dynamic_cast<IButton&>(*comp);
                button += std::move(okClickableCallback);
            }
        }
    }
}

}  // namespace machine
