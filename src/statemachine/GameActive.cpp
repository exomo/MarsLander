#include <statemachine/GameActive.h>

#include <iostream>
#include <sstream>
#include <string>

#include <statemachine/GamePaused.h>
#include <statemachine/GameOver.h>

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

    // TODO: Parameter sind im Moment fest, sollten von außen kommen
    transformation = CoordinateTransformation(800, 600, 4000000, 3000000);

    // Initialisiere Raumschiff und Landschaft
    surface.Initialize(sim.getSurface(), transformation);
    ship.initialize();

    // Zeige Kollisionsmodelle an, nur für debugging
    showCollisionModel = true;
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

        //TODO: Bewegunstasten sinnvoller auswerten.
        if((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
        {
            // Schiff gegen den Uhrzeigersinn drehen
            sim.Rotate(SpaceSimulation::Rotation::CounterClockwise);
        }
        if((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
        {
            // move ship to the right
            sim.Rotate(SpaceSimulation::Rotation::Clockwise);
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
        if((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
        {
            // Schiff nicht mehr drehen
            sim.Rotate(SpaceSimulation::Rotation::None);
        }
        if((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
        {
            // Schiff nicht mehr drehen
            sim.Rotate(SpaceSimulation::Rotation::None);
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

    /* Wenn das Spiel pausiert war (hier kommt man erst hin wenn der Pausenmodus verlassen wurde), wird die Zeitmessung
     * bis zur nächsten Bewegung neu gestartet. */
    if(paused)
    {
        paused = false;
        lastMoveTime = elapsed;
    }

    auto elapsedSinceMove = (elapsed - lastMoveTime).asMilliseconds();
    sim.SimulationStep(elapsedSinceMove);

    lastMoveTime = elapsed;

    auto shipState = sim.GetShipState();

    if(shipState.hasLanded)
    {
        return std::make_shared<GameOver>(1);
    }

    if(!shipState.isAlive)
    {
        return std::make_shared<GameOver>(0);
    }

    // Simulationskoordinaten in Anzeigekoordinaten umrechnen
    ship.setPosition(transformation.ToDisplayX(shipState.horizontalPosition), transformation.ToDisplayY(shipState.altitude));
    ship.setRotation(transformation.ToDisplayAngle(shipState.rotation));

    return nullptr;
}

void GameActive::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(25,50,0, 255));

    surface.drawTo(window);
    ship.drawTo(window);

    if(showCollisionModel)
    {
        window.draw(sim.getCollisionOverlay());
    }

    sf::Text scoreText;

    scoreText.setFont(textFont);
    std::wostringstream text;
    text << L"Völlig losgelöst von der Erde";
    scoreText.setString(text.str());
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Blue);
    scoreText.setPosition(15, 5);
    window.draw(scoreText);
}
