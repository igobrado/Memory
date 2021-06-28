//
// Created by Igor Obradovic.
//
#pragma once

#include <tinyxml2.h>

#include <SFML/Graphics.hpp>
#include <common/Result.hpp>
#include <memory>
#include <resource/gui/components/ITextbox.hpp>
#include <resource/gui/impl/Counter.hpp>
#include <vector>

class GUILoader
{
public:
    GUILoader(GUILoader const&) = delete;
    GUILoader(GUILoader&&)      = delete;

    GUILoader& operator=(GUILoader const&) = delete;
    GUILoader& operator=(GUILoader&&) = delete;

    static GUILoader& instance()
    {
        static GUILoader instance;
        return instance;
    }

    std::vector<std::unique_ptr<IGuiComponent>> components(
            std::string const&      cfgPath,
            std::string const&      partToLoad,
            sf::RenderWindow const& parent,
            sf::Font const&         font);

private:
    GUILoader() = default;

    template <typename... Args>
    bool validateReadingResult(Args&&... args) const;

    std::vector<std::unique_ptr<IGuiComponent>> readByComponent(
            tinyxml2::XMLElement*   element,
            std::string const&      partToLoad,
            sf::RenderWindow const& parent,
            sf::Font const&         font) const;

    std::unique_ptr<ITextbox> readTextbox(
            tinyxml2::XMLElement*   startEl,  //
            sf::RenderWindow const& parent,
            sf::Font const&         font) const;

    std::unique_ptr<ILabel> readLabel(
            tinyxml2::XMLElement* startEl,  //
            sf::Font const&       font) const;

    std::unique_ptr<IButton> readButton(
            tinyxml2::XMLElement*   startEl,  //
            sf::RenderWindow const& parent,
            sf::Font const&         font) const;

    std::unique_ptr<IButton> readCounter(
            tinyxml2::XMLElement*   startEl,  //
            sf::RenderWindow const& parent,
            sf::Font const&         font) const;

    struct ComponentDefinition
    {
        char const*   name{};
        std::uint64_t posX{};
        std::uint64_t posY{};
        std::uint64_t width{};
        std::uint64_t height{};
        std::uint64_t fontSize{};
        std::uint64_t outlineThickness{};
    };

    Result<ComponentDefinition> extractGlobalComponentData(tinyxml2::XMLElement* el) const;
};
