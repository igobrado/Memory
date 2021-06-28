//
// Created by Igor Obradovic.
//
#include <SFML/Graphics.hpp>
#include <common/ScreenSize.hpp>
#include <game/state/impl/IntroState.hpp>
#include <resource/gui/GUILoader.hpp>
#include <resource/gui/impl/TextboxImpl.hpp>
namespace machine
{

namespace
{

constexpr char const* sOkButton          = "OKButton";
constexpr char const* sInserter          = "InsertPlayer";
constexpr char const* sPlayerNameTextbox = "PlayerName";

constexpr char const* sBoardWidthLabel        = "BoardWidthCount";
constexpr char const* sBoardHeightLabel       = "BoardHeightCount";
constexpr char const* sOnePlayerError         = "OnePLayerError";
constexpr char const* sIncompatibleBoardError = "BoardIncompatibleError";

}  // namespace

IntroState::IntroState(common::GameData& gameData)  //
    : State{}
    , m_GameData{ gameData }
    , m_Background{ gameData.resource().texture("Background") }
    , m_GuiComponents{ GUILoader::instance().components(
              "../resource/xml/state/StateConfig.xml",
              "Intro",
              m_GameData.window(),
              m_GameData.resource().font("MyFont")) }
    , m_Timeout{ nullptr, 0.5 }
{
    for (auto const& component : m_GuiComponents)
    {
        if (component->type() == ComponentType::kCounter)
        {
            auto& counter   = dynamic_cast<Counter&>(*component);
            auto  labelName = counter.referencedLabelName();

            if (!labelName.empty())
            {
                for (const auto& guiComponent : m_GuiComponents)
                {
                    if (guiComponent->type() == ComponentType::kLabel)
                    {
                        if (guiComponent->name() == labelName)
                        {
                            auto& label = dynamic_cast<LabelImpl&>(*guiComponent);
                            counter.setReferencedLabel(label);
                            counter += [&]() { m_GameData.resource().play("click"); };
                        }
                        else if (guiComponent->name() == sOnePlayerError)
                        {
                            auto& label = dynamic_cast<LabelImpl&>(*guiComponent);
                            label.setVisibility(false);
                        }
                        else if (guiComponent->name() == sIncompatibleBoardError)
                        {
                            auto& label = dynamic_cast<LabelImpl&>(*guiComponent);
                            label.setVisibility(false);
                        }
                    }
                }
            }
        }
    }

    populateCallbacks();
    m_GameData.players().clear();
}

void IntroState::update(float const deltaTime)
{
    for (auto const& guiComponents : m_GuiComponents)
    {
        guiComponents->update(deltaTime);
    }
    m_Timeout.update(deltaTime);
}

void IntroState::handleInput()
{
    sf::Event         eventToProcess{};
    sf::RenderWindow& window = m_GameData.window();
    while (window.pollEvent(eventToProcess))
    {
        if (eventToProcess.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }

        for (auto const& guiComponent : m_GuiComponents)
        {
            guiComponent->handleInput(eventToProcess);
        }
    }
}

std::string IntroState::textLocatedInTextbox(char const* textboxName)
{
    for (auto& component : m_GuiComponents)
    {
        if (component->type() == ComponentType::kTextbox)
        {
            if (component->name() == textboxName)
            {
                auto& textbox     = dynamic_cast<TextboxImpl&>(*component);
                auto  textboxText = textbox.text();
                textbox.clear();
                return textboxText;
            }
        }
    }
    return "";
}

std::uint32_t IntroState::numberLocatedInLabel(char const* labelName)
{
    for (auto& component : m_GuiComponents)
    {
        if (component->type() == ComponentType::kLabel)
        {
            if (component->name() == labelName)
            {
                auto& label = dynamic_cast<LabelImpl&>(*component);
                return stoi(label.text());
            }
        }
    }
    return 0;
}

void IntroState::draw()
{
    auto& window = m_GameData.window();
    window.clear();
    window.draw(m_Background);
    for (auto const& guiComponent : m_GuiComponents)
    {
        window.draw(*guiComponent);
    }

    window.display();
}

void IntroState::toggleLabelVisibility(const char* labelName, bool visibility)
{
    for (auto& component : m_GuiComponents)
    {
        if (component->type() == ComponentType::kLabel)
        {
            if (component->name() == labelName)
            {
                auto& label = dynamic_cast<LabelImpl&>(*component);
                label.setVisibility(visibility);
            }
        }
    }
}

void IntroState::populateCallbacks()
{
    OnClickCheckCallback okClickableCallback = [this]() {  //
        auto boardWidth  = numberLocatedInLabel(sBoardWidthLabel);
        auto boardHeight = numberLocatedInLabel(sBoardHeightLabel);
        if (((boardWidth * boardHeight) % 2) == 0)
        {
            m_GameData.setBoardDimensions({ boardWidth, boardHeight });
            if (m_GameData.players().empty())
            {
                toggleLabelVisibility(sOnePlayerError, true);
                m_Timeout.reset([this]() { toggleLabelVisibility(sOnePlayerError, false); }, 1.f);
            }
            else
            {
                m_GameData.resource().play("click");
                m_GameData.switchState(::machine::StateType::GAME);
            }
        }
        else
        {
            toggleLabelVisibility(sIncompatibleBoardError, true);
            m_Timeout.reset([this]() { toggleLabelVisibility(sIncompatibleBoardError, false); }, 1.f);
        }

    };
    OnClickCheckCallback inserterClickableCallback = [this]() {
        std::string playerName = textLocatedInTextbox(sPlayerNameTextbox);
        if (!playerName.empty())
        {
            m_GameData.insertPlayer(playerName);
            m_GameData.resource().play("click");
            toggleLabelVisibility(sOnePlayerError, false);
            m_Timeout.reset([this]() { toggleLabelVisibility(sOnePlayerError, false); }, 1.f);
        }
    };

    for (const auto& comp : m_GuiComponents)
    {
        if (comp->type() == ComponentType::kButton)
        {
            // downcast is tricky, in this case we are sure that
            // certain type is button so, "nothing" can happen.
            auto& button = dynamic_cast<IButton&>(*comp);
            if (button.name() == sOkButton)
            {
                button += std::move(okClickableCallback);
            }
            else if (button.name() == sInserter)
            {
                button += std::move(inserterClickableCallback);
            }
        }
    }
}

}  // namespace machine
