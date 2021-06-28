//
// Created by Igor Obradovic.
//
#pragma once

#include <tinyxml2.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <game/animations/SfinaeHelpers.hpp>
#include <iostream>
#include <map>
#include <memory>

template <typename T, typename Derived>
class Manager
{
public:
    using ValueType = T;
    using ValueRef  = T&;

    Manager()  //
        : mData{}
    {
        static_assert(
                ::traits::HasLoad<Derived>::value,
                "Derived class shall implement "
                "method with signature: "
                "void Load(tinyxml2::XMLElement*, char const*, char const*)");
    }

    ValueRef getProperty(std::string const& targetID)
    {
        auto found = mData.find(tolower(targetID.c_str()));
        if (found == std::end(mData))
        {
            throw std::out_of_range("No data in map with key: " + std::string{ tolower(targetID.c_str()) } + "\n");
        }
        return found->second;
    }

    std::string tolower(char const* str)
    {
        std::string t{ str };
        std::transform(t.begin(), t.end(), t.begin(), ::tolower);
        return t;
    }

protected:
    template <typename... Args>
    decltype(auto) emplace(Args&&... args)
    {
        return mData.emplace(std::forward<Args>(args)...);
    }

    std::map<std::string, ValueType> const& data() const
    {
        return mData;
    }

private:
    std::map<std::string, ValueType> mData;
};

class TextureManager : public Manager<sf::Texture, TextureManager>
{
public:
    explicit TextureManager(const char* xmlPath)  //
        : Manager<sf::Texture, TextureManager>{}
    {
        tinyxml2::XMLDocument document;
        if (document.LoadFile(xmlPath) == tinyxml2::XMLError::XML_SUCCESS)
        {
            auto startPos{ document.FirstChildElement("Textures") };
            Load(startPos, "Cards", "Card");
            Load(startPos, "Backgrounds", "Background");
        }
    }

    void Load(tinyxml2::XMLElement* startPos, char const* moduleName, char const* componentName)
    {
        tinyxml2::XMLElement* element{ startPos->FirstChildElement(moduleName)->FirstChildElement(componentName) };
        char const*           path = "";
        char const*           name = "";

        for (;         //
             element;  //
             element = element->NextSiblingElement(componentName))
        {
            element->QueryStringAttribute("Texture", &path);
            element->QueryStringAttribute("Name", &name);
            sf::Texture texture{};
            if (texture.loadFromFile(path))
            {
                (void) emplace(
                        std::piecewise_construct,              //
                        std::forward_as_tuple(tolower(name)),  //
                        std::forward_as_tuple(std::move(texture)));
            }
        }
    }
};

using SoundPair = std::pair<std::unique_ptr<sf::SoundBuffer>, std::shared_ptr<sf::Sound>>;
class SoundManager : public Manager<SoundPair, SoundManager>
{
public:
    explicit SoundManager(const char* xmlPath)  //
        : Manager<SoundPair, SoundManager>{}
    {
        tinyxml2::XMLDocument document;
        if (document.LoadFile(xmlPath) == tinyxml2::XMLError::XML_SUCCESS)
        {
            auto startPos{ document.FirstChildElement("Sounds") };
            Load(startPos, "Game", "Sound");
        }
    }

    void Load(tinyxml2::XMLElement* startPos, char const* moduleName, char const* componentName)
    {
        tinyxml2::XMLElement* element{ startPos->FirstChildElement(moduleName)->FirstChildElement(componentName) };
        char const*           path = "";
        char const*           name = "";

        for (;         //
             element;  //
             element = element->NextSiblingElement(componentName))
        {
            std::unique_ptr<sf::SoundBuffer> soundBuffer{ std::make_unique<sf::SoundBuffer>() };
            element->QueryStringAttribute("Buffer", &path);
            element->QueryStringAttribute("Name", &name);

            if (soundBuffer->loadFromFile(path))
            {
                std::shared_ptr<sf::Sound> sound{ std::make_shared<sf::Sound>() };
                sound->setBuffer(*soundBuffer);
                sound->setVolume(10.0f);

                (void) emplace(
                        std::piecewise_construct,              //
                        std::forward_as_tuple(tolower(name)),  //
                        std::forward_as_tuple(std::move(soundBuffer), std::move(sound)));
            }
        }
    }

    void play(std::string const& music)
    {
        try
        {
            auto& it = getProperty(music).second;
            it->play();
        }
        catch (std::out_of_range& excp)
        {
            std::ofstream ostr{ "ErrorLog.txt", std::ios::out };
            ostr << "Playing music failed with: " << excp.what() << std::endl;
        }
    }

    void setRepeating(std::string const& sound)
    {
        try
        {
            auto& it = getProperty(sound).second;
            it->setLoop(true);
        }
        catch (std::out_of_range& excp)
        {
            std::ofstream ostr{ "ErrorLog.txt", std::ios::out };
            ostr << "Playing music failed with: " << excp.what() << std::endl;
        }
    }
};

class FontManager : public Manager<sf::Font, FontManager>
{
public:
    explicit FontManager(const char* xmlFile)  //
        : Manager<sf::Font, FontManager>{}
    {
        tinyxml2::XMLDocument document;
        if (document.LoadFile(xmlFile) == tinyxml2::XML_SUCCESS)
        {
            auto startPos{ document.FirstChildElement("Fonts") };
            Load(startPos, "Classic", "FontID");
        }
    }

    void Load(tinyxml2::XMLElement* startPos, char const* moduleName, char const* componentName)
    {
        tinyxml2::XMLElement* element{ startPos->FirstChildElement(moduleName)->FirstChildElement(componentName) };
        char const*           path = "";
        char const*           name = "";

        for (;         //
             element;  //
             element = element->NextSiblingElement(componentName))
        {
            element->QueryStringAttribute("Font", &path);
            element->QueryStringAttribute("Name", &name);
            sf::Font font;
            if (font.loadFromFile(path))
            {

                (void) emplace(
                        std::piecewise_construct,
                        std::forward_as_tuple(tolower(name)),
                        std::forward_as_tuple(font));
            }
        }
    }
};
