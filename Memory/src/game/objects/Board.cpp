//
// Created by Igor Obradovic.
//
#include <common/Math.hpp>
#include <common/ScreenSize.hpp>
#include <game/objects/Board.hpp>
#include <random>

Board::Board(
        std::uint32_t    boardWidth,
        std::uint32_t    boardHeight,
        ResourceHolder&  resourceHolder,
        common::Players& players)
    : m_Deck{}
    , m_TableHud{ players }
    , m_BoardView{}
    , m_Timeout{ 0.0f }
    , m_FlipSoundCallback{ [&resourceHolder] { resourceHolder.play("flip"); } }
{
    initialize(boardWidth, boardHeight, resourceHolder);
    if (!m_Deck.empty())
    {
        // Magic numbers description
        // 10.0f is offset between cards
        // 0.07 and 0.875 tweaked numbers for positioning the view
        auto size       = (*m_Deck.begin())->getSize();
        auto boardSizeX = boardHeight * (size.x + 10.f);
        auto boardSizeY = boardWidth * (size.y + 10.f);

        sf::Vector2f playingFieldSize(screenWidth - (sHudPieceHeight * 2), screenHeight - (sHudPieceHeight * 2));

        if (boardSizeX > playingFieldSize.x)
        {
            playingFieldSize.x = boardSizeX;
        }

        if (boardSizeY > playingFieldSize.y)
        {
            playingFieldSize.y = boardSizeY;
        }

        m_BoardView.setSize(playingFieldSize);
        m_BoardView.setCenter(half(boardSizeX), half(boardSizeY));
        m_BoardView.setViewport(sf::FloatRect(0.07f, 0.07f, 0.875f, 0.875f));
    }

    m_RevealedCard = std::end(m_Deck);
}

void Board::update(float const deltaTime)
{
    m_TableHud.update(deltaTime);
    m_Timeout.update(deltaTime);
    for (auto const& card : m_Deck)
    {
        card->update(deltaTime);
    }
}

void Board::handleInput(sf::Vector2i const mousePos)
{
    if ((m_RevealedCard != std::end(m_Deck)) && (!(*m_RevealedCard)->isAnimationOver())
        || (!m_TableHud.isRotationOver()))
    {
        return;
    }

    auto it = std::find_if(std::begin(m_Deck), std::end(m_Deck), [&mousePos, this](auto& card) {
        return card->handleInput(mousePos, m_FlipSoundCallback);
    });

    if (it != std::end(m_Deck))  // no card was clicked
    {

        if (m_RevealedCard == std::end(m_Deck))  // no previously selected card
        {
            m_RevealedCard = it;
            (*m_RevealedCard)->reveal();
        }
        else
        {
            if (*(*m_RevealedCard) == *(*it))  // in case that cards have same suit,
                                               // reveal them and null iterators
            {
                m_Timeout.reset(
                        [this, it]() {
                            (*m_RevealedCard)->reveal();
                            (*it)->reveal();

                            m_TableHud.currentPlayer().increaseScore();
                            m_RevealedCard = std::end(m_Deck);
                        },
                        0.f);
            }
            else  // in case that cards are not the same
            {
                m_Timeout.reset(
                        [this, it]() {
                            (*m_RevealedCard)->flipCard(m_FlipSoundCallback);
                            (*it)->flipCard(m_FlipSoundCallback);

                            m_TableHud.nextPlayer();
                            m_RevealedCard = std::end(m_Deck);
                        },
                        0.7f);
            }
        }
    }
}

void Board::draw(sf::RenderWindow& window)
{
    m_TableHud.draw(window);
    window.setView(m_BoardView);
    for (auto const& card : m_Deck)
    {
        window.draw(*card);
    }
}

bool Board::isGameOver()
{
    return std::all_of(std::begin(m_Deck), std::end(m_Deck), [](auto& card) { return card->isRevealed(); });
}

void Board::initialize(std::uint32_t boardWidth, std::uint32_t boardHeight, ResourceHolder& resourceHolder)
{
    std::uint64_t const deckSize         = boardWidth * boardHeight;
    std::uint64_t       pairsPerCardType = deckSize / 2 / static_cast<std::uint64_t>(CardType::kSize);

    auto& background = resourceHolder.texture("CardBackground");

    for (auto cardType : { CardType::kJack, CardType::kQueen, CardType::kKing, CardType::kAce })
    {
        for (std::uint64_t column = 0; column < pairsPerCardType * 2; ++column)
        {
            m_Deck.push_back(
                    std::make_unique<Card>(background, resourceHolder.texture(cardTypeToString(cardType)), cardType));
        }
    }
    // in case that first loop haven't inserted all cards
    if ((deckSize / 2) % static_cast<std::uint32_t>(CardType::kSize))
    {
        for (std::uint32_t i = 0; i < (deckSize / 2) % static_cast<std::uint32_t>(CardType::kSize); ++i)
        {
            auto cardType = static_cast<CardType>(i);
            for (std::uint8_t j = 0; j < 2; ++j)
            {
                m_Deck.push_back(std::make_unique<Card>(
                        background,
                        resourceHolder.texture(cardTypeToString(cardType)),
                        cardType));
            }
        }
    }

    std::random_device randomDevice{};
    std::mt19937       twisterEngine{ randomDevice() };
    std::shuffle(std::begin(m_Deck), std::end(m_Deck), twisterEngine);

    int pos = 0;
    for (std::uint32_t i = 0; i < boardHeight; ++i)
    {
        for (std::uint32_t j = 0; j < boardWidth; ++j)
        {
            m_Deck[pos]->setPosition(sf::Vector2f{ (float) i, (float) j });
            ++pos;
        }
    }
}
