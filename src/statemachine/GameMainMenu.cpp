#include <statemachine/GameMainMenu.h>
#include <statemachine/GameState.h>
#include <statemachine/GameActive.h>
#include <GlobalResources.h>

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace ExomoMarsLander;

GameMainMenu::GameMainMenu()
    : textFont(GlobalResources::GetInstance().GetFont())
    , backgroundShape(sf::Vector2f(800, 600))
    , ship()
{
    backgroundShape.setTexture(&GlobalResources::GetInstance().GetSpace());
    backgroundShape.setTextureRect(sf::IntRect(0, 0, 1600, 1200));

    ship.initialize();
    ship.setPosition(500, 300);
    ship.setRotation(-20);
}

GameMainMenu::~GameMainMenu()
{
    //dtor
}

void GameMainMenu::handleEvent(const sf::Event& event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Escape)
        {
            exitRequested = true;
        }

        if(event.key.code == sf::Keyboard::Return)
        {
            startRequested = true;
        }
        break;

    default:
        break;
    }
}

GameStatePtr GameMainMenu::updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState)
{
    const double moveSpeed = 0.02;

    auto elapsedSinceLastUpdate = (elapsed - lastUpdateTime).asMilliseconds();
    lastUpdateTime = elapsed;

    if(startRequested)
    {
        return std::make_shared<GameActive>();
    }

    offsetX += moveSpeed * elapsedSinceLastUpdate;
    offsetY += moveSpeed * elapsedSinceLastUpdate;
    backgroundShape.setTextureRect(sf::IntRect(static_cast<int>(offsetX), static_cast<int>(offsetY), 1600, 1200));

    return nullptr;
}

void GameMainMenu::render(sf::RenderWindow& window)
{
    if(exitRequested)
    {
        window.close();
        return;
    }

    window.clear(sf::Color::Black);
    window.draw(backgroundShape);

    ship.drawTo(window);

    sf::Text menuText;
    menuText.setFont(textFont);
    menuText.setFillColor(sf::Color::Yellow);
    menuText.setString(L"Exomo Mars Lander");
    menuText.setCharacterSize(50);
    menuText.setPosition(50, 20);
    window.draw(menuText);

    menuText.setString(L"<Enter> Spiel starten\n<Esc> Beenden");
    menuText.setCharacterSize(40);
    menuText.setPosition(60, 80);
    window.draw(menuText);

}
