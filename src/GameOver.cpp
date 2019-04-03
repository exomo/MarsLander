#include <GameState.h>
#include <GameActive.h>
#include <GameMainMenu.h>
#include <GameOver.h>

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace ExomoMarsLander;

GameOver::GameOver(int score)
    : score(score)
    , textFont(GlobalResources::GetInstance().GetFont())
{

}

GameOver::~GameOver()
{
    //dtor
}

void GameOver::handleEvent(const sf::Event& event)
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

GameStatePtr GameOver::updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState)
{
    if(startRequested)
    {
        return std::make_shared<GameActive>();
    }
    if(exitRequested)
    {
        return std::make_shared<GameMainMenu>();
    }
    return nullptr;
}

void GameOver::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(125,50,0, 255));

    sf::Text menuText;

    std::wostringstream gameOverText;
    if(score > 0)
    {
        gameOverText << L"Spiel vorbei\n"
                     << L"Sicher gelandet \n";
    } 
    else
    {
        gameOverText << L"Spiel vorbei\n"
                     << L"Abgestürzt \n";
    }
    

    menuText.setFont(textFont);
    menuText.setString(gameOverText.str());
    menuText.setCharacterSize(50);
    menuText.setFillColor(sf::Color::Blue);
    menuText.setPosition(50, 20);
    window.draw(menuText);

    menuText.setString(L"<Enter> Neues Spiel - <Esc> Hauptmenü");
    menuText.setPosition(50, 520);
    menuText.setCharacterSize(40);
    window.draw(menuText);

}
