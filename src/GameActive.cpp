#include <GameActive.h>

#include <iostream>
#include <sstream>
#include <string>

#include <GamePaused.h>
#include <GameOver.h>

using namespace ExomoMarsLander;

GameActive::GameActive()
    : globalResources(GlobalResources::GetInstance())
    , textFont(globalResources.GetFont())
{
    InitializeLevel();

    pauseRequested = false;
}

GameActive::~GameActive()
{
    //dtor
}


void GameActive::InitializeLevel()
{
    sim.Initialize();
}

void GameActive::handleEvent(const sf::Event& event)
{
    switch(event.type)
    {
    case sf::Event::LostFocus:
        /* Hauptfenster hat den Fokus verloren, das Spiel wird pausiert. */
        pauseRequested = true;
        break;

    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Pause)
        {
            /*
             * Hier wird nur gespeichert dass die P Taste gedrückt wurde und in den Pausenbildschirm gewechselt werden soll.
             * Der Zustandswechsel nach "Pause" wird erst im updateGame() Schritt durchgeführt.
             */
            pauseRequested = true;
        }

        if((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
        {
            // move ship to the left
        }
        if((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
        {
            // move ship to the right
        }
        if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
        {
            // move ship up
            sim.EnableThrust(true);
            ship.enableFlame(true);
        }
        if((event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S))
        {
            // move ship down (maybe not possible)
        }
        break;

    case sf::Event::KeyReleased:
        if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
        {
            sim.EnableThrust(false);
            ship.enableFlame(false);
        }
        break;

    default:
        break;
    }
}

GameStatePtr GameActive::updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState)
{
    /* Wenn die Pause-Taste gedrückt wurde, wird sofort in den Pause-Bildschirm gewechselt,
     * ohne die Schlange zu bewegen. */
    if(pauseRequested)
    {
        /* Die Pausenanforderung wird zurückgesetz, dafür wird gespeichert dass das Spiel gerade pausiert ist. */
        pauseRequested = false;
        paused = true;
        return std::make_shared<GamePaused>(currentState);
    }

    /* Wenn ein Level beendet wurde, wird sofort in den LevelClear-Bildschirm gewechselt,
     * ohne weitere Bewegungen zu berechnen. */
    if(completedRequested)
    {
        completedRequested = false;
        levelCompleted = true;

        // TODO: Replace with real state for winning
        return std::make_shared<GamePaused>(currentState);
    }

    /* Wenn das Spiel pausiert war (hier kommt man erst hin wenn der Pausenmodus verlassen wurde), wird die Zeitmessung
     * bis zur nächsten Bewegung neu gestartet. */
    if(paused)
    {
        paused = false;
        lastMoveTime = elapsed;
    }

    // TODO: move the space ship
    auto elapsedSinceMove = (elapsed - lastMoveTime).asMilliseconds();
    sim.SimulationStep(elapsedSinceMove);

    lastMoveTime = elapsed;

    ship.setPosition(400 + sim.GetShipX() / 10000, 530 - sim.GetShipY() / 10000);

    return nullptr;
}

void GameActive::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(25,50,0, 255));

    surface.drawTo(window);
    ship.drawTo(window);

    sf::Text scoreText;

    scoreText.setFont(textFont);
    std::wostringstream text;
    text << L"Völlig losgelöst von der Erde";
    scoreText.setString(text.str());
    scoreText.setCharacterSize(24);
    scoreText.setColor(sf::Color::Blue);
    scoreText.setPosition(15, 5);
    window.draw(scoreText);
}
