//
// Created by Igor Obradovic.
//
#include <tinyxml2.h>

#include <common/GUIUtils.hpp>
#include <resource/gui/ComponentFactory.hpp>
#include <resource/gui/GUILoader.hpp>
#include <resource/gui/impl/TextboxImpl.hpp>

namespace
{
constexpr char const* sConfig           = "Config";
constexpr char const* sComponent        = "Component";
constexpr char const* sType             = "Type";
constexpr char const* sPosX             = "PosX";
constexpr char const* sPosY             = "PosY";
constexpr char const* sWidth            = "Width";
constexpr char const* sHeight           = "Height";
constexpr char const* sOutlineThickness = "OutlineThickness";
constexpr char const* sText             = "Text";
constexpr char const* sFontSize         = "FontSize";
constexpr char const* sName             = "Name";
constexpr char const* sCounter          = "Counters";
constexpr char const* sResponsibleLabel = "ResponsibleLabelName";

}  // namespace

std::vector<std::unique_ptr<IGuiComponent>> GUILoader::components(
        std::string const&      cfgPath,
        std::string const&      partToLoad,
        sf::RenderWindow const& parent,
        sf::Font const&         font)
{
    tinyxml2::XMLDocument doc;

    if (doc.LoadFile(cfgPath.c_str()) == tinyxml2::XMLError::XML_SUCCESS)
    {
        auto startPos{ doc.FirstChildElement(sConfig) };
        return readByComponent(startPos, partToLoad, parent, font);
    }
    return {};
}

std::vector<std::unique_ptr<IGuiComponent>> GUILoader::readByComponent(
        tinyxml2::XMLElement*   element,
        std::string const&      partToLoad,
        sf::RenderWindow const& parent,
        sf::Font const&         font) const
{
    tinyxml2::XMLElement* startEl{ element->FirstChildElement(partToLoad.c_str())->FirstChildElement(sComponent) };
    std::vector<std::unique_ptr<IGuiComponent>> components{};

    for (; startEl; startEl = startEl->NextSiblingElement(sComponent))
    {
        const char* type = "";
        startEl->QueryStringAttribute(sType, &type);

        switch (toComponentType(type))
        {
            case ComponentType::kButton:
            {
                auto&& button = readButton(startEl, parent, font);
                if (button)
                {
                    components.emplace_back(std::move(button));
                }
                break;
            }
            case ComponentType::kLabel:
            {
                auto&& label = readLabel(startEl, font);
                if (label)
                {
                    components.emplace_back(std::move(label));
                }
                break;
            }
            case ComponentType::kTextbox:
            {
                auto&& textbox = readTextbox(startEl, parent, font);
                if (textbox)
                {
                    components.emplace_back(std::move(textbox));
                }
                break;
            }
            case ComponentType::kCounter:
            {
                auto&& counter = readCounter(startEl, parent, font);
                if (counter)
                {
                    components.push_back(std::move(counter));
                }
                break;
            }
        }
    }
    return components;
}

template <typename... Args>
bool GUILoader::validateReadingResult(Args&&... args) const
{
    std::vector<tinyxml2::XMLError> results{ args... };
    return std::all_of(std::begin(results), std::end(results), [](const auto result) {
        return result != tinyxml2::XMLError::XML_SUCCESS;
    });
}

std::unique_ptr<ITextbox> GUILoader::readTextbox(
        tinyxml2::XMLElement*   textbox,
        sf::RenderWindow const& parent,
        sf::Font const&         font) const
{
    auto globalDataResult = extractGlobalComponentData(textbox);
    if (!globalDataResult)
    {
        return {};
    }
    GUILoader::ComponentDefinition const& globalData = globalDataResult.getValue();

    return makeGuiComponent<TextboxImpl>(
            globalData.name,
            globalData.fontSize,
            globalData.width,
            globalData.height,
            globalData.posX,
            globalData.posY,
            globalData.outlineThickness,
            font,
            parent);
}

std::unique_ptr<ILabel> GUILoader::readLabel(
        tinyxml2::XMLElement* label,  //
        sf::Font const&       font) const
{
    const char* labelText{ "" };
    auto        labelNameResult  = label->QueryStringAttribute(sText, &labelText);
    auto        globalDataResult = extractGlobalComponentData(label);

    if (validateReadingResult(labelNameResult) || !globalDataResult)
    {
        return {};
    }

    const GUILoader::ComponentDefinition& globalData = globalDataResult.getValue();

    return makeGuiComponent<LabelImpl>(
            font,
            globalData.name,
            labelText,
            globalData.fontSize,
            globalData.posX,
            globalData.posY);
}

std::unique_ptr<IButton> GUILoader::readButton(
        tinyxml2::XMLElement*   button,  //
        sf::RenderWindow const& parent,
        sf::Font const&         font) const
{
    const char* buttonText{ "" };
    auto        globalDataResult = extractGlobalComponentData(button);

    auto textResult = button->QueryStringAttribute(sText, &buttonText);
    if (validateReadingResult(textResult) || (!globalDataResult))
    {
        return {};
    }

    GUILoader::ComponentDefinition const& globalData = globalDataResult.getValue();

    return makeGuiComponent<ButtonImpl>(  //
            globalData.name,
            buttonText,
            font,
            parent,
            globalData.posX,
            globalData.posY,
            globalData.width,
            globalData.height,
            globalData.fontSize,
            globalData.outlineThickness);
}

std::unique_ptr<IButton> GUILoader::readCounter(
        tinyxml2::XMLElement*   counter,
        sf::RenderWindow const& parent,
        sf::Font const&         font) const
{
    const char* text{ "" };
    const char* responsibleLabelName{ "" };

    auto textResult             = counter->QueryStringAttribute(sText, &text);
    auto responsibleLabelResult = counter->QueryStringAttribute(sResponsibleLabel, &responsibleLabelName);
    auto globalDataResult       = extractGlobalComponentData(counter);

    if (validateReadingResult(textResult, responsibleLabelResult) || (!globalDataResult))
    {
        return {};
    }

    GUILoader::ComponentDefinition const& globalData = globalDataResult.getValue();

    return std::make_unique<Counter>(
            globalData.name,
            text,
            font,
            parent,
            globalData.posX,
            globalData.posY,
            globalData.width,
            globalData.height,
            globalData.fontSize,
            globalData.outlineThickness,
            responsibleLabelName);
}

Result<GUILoader::ComponentDefinition> GUILoader::extractGlobalComponentData(tinyxml2::XMLElement* el) const
{
    GUILoader::ComponentDefinition componentDefinition{};

    // clang-format off
    auto posXResult             = el->QueryUnsigned64Attribute(sPosX, &componentDefinition.posX);
    auto posYResult             = el->QueryUnsigned64Attribute(sPosY, &componentDefinition.posY);
    auto widthResult            = el->QueryUnsigned64Attribute(sWidth, &componentDefinition.width);
    auto heightResult           = el->QueryUnsigned64Attribute(sHeight, &componentDefinition.height);
    auto outlineThicknessResult = el->QueryUnsigned64Attribute(sOutlineThickness, &componentDefinition.outlineThickness);
    auto characterSizeResult    = el->QueryUnsigned64Attribute(sFontSize, &componentDefinition.fontSize);
    auto nameResult             = el->QueryStringAttribute(sName, &componentDefinition.name);
    // clang-format on

    if (validateReadingResult(
                posXResult,
                posYResult,
                widthResult,
                heightResult,
                outlineThicknessResult,
                characterSizeResult,
                nameResult))
    {
        return {};
    }

    return componentDefinition;
}
