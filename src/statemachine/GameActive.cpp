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
    , background(sf::Vector2f(800, 600))
    , showCollisionModel(false)
{
    InitializeLevel();

    background.setTexture(&globalResources.GetSpace());
    planet.setSize(sf::Vector2f(200, 200));
    planet.setTexture(&globalResources.GetPlanet());
    planet.setPosition(50, 100);

    pauseRequested = false;
}

GameActive::~GameActive()
{
    //dtor
}


void GameActive::InitializeLevel()
{
    
    // TODO: Parameter sind im Moment fest, sollten von außen kommen
    transformation = CoordinateTransformation(800, 600, 4000000, 3000000);

    sim.Initialize();

    // Initialisiere Raumschiff und Landschaft
    surface.Initialize(sim.getSurface(), transformation);
    ship.initialize();

    hud.initialize();

    // Zeige Kollisionsmodelle an, nur für debugging
    showCollisionModel = false;

    forwardPushed = false;
    rotateClockwisePushed = false;
    rotateCounterClockwisePushed = false;
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
            // Schiff gegen den Uhrzeigersinn drehen
            rotateCounterClockwisePushed = true;
        }
        if((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
        {
            // Schiff im Uhrzeigersinn drehen
            rotateClockwisePushed = true;
        }
        if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
        {
            // Schiff nach vorne/oben bewegen
            forwardPushed = true;
        }
        if((event.key.code == sf::Keyboard::H))
        {
            showCollisionModel = !showCollisionModel;
        }
        break;

    case sf::Event::KeyReleased:
        if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
        {
            forwardPushed = false;
        }
        if((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
        {
            // Schiff nicht mehr drehen
            rotateCounterClockwisePushed = false;
        }
        if((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
        {
            // Schiff nicht mehr drehen
            rotateClockwisePushed = false;
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
        
        forwardPushed = false;
        rotateClockwisePushed = false;
        rotateCounterClockwisePushed = false;
    }

    auto elapsedSinceMove = (elapsed - lastMoveTime).asMilliseconds();
    sim.SimulationStep(elapsedSinceMove);

    lastMoveTime = elapsed;

    if((rotateClockwisePushed && rotateCounterClockwisePushed) || (!rotateClockwisePushed && !rotateCounterClockwisePushed))
    {
        sim.Rotate(SpaceSimulation::Rotation::None);
    } 
    else if(rotateClockwisePushed)
    {
        sim.Rotate(SpaceSimulation::Rotation::Clockwise);
    }
    else if(rotateCounterClockwisePushed)
    {
        sim.Rotate(SpaceSimulation::Rotation::CounterClockwise);
    }
    sim.EnableThrust(forwardPushed);

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
    ship.enableFlame(shipState.fuel > 0 && forwardPushed);

    hud.setFuel(shipState.fuel);
    hud.setAltitude(shipState.altitude);

    return nullptr;
}

void GameActive::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(0,0,0, 255));
    window.draw(background);
    window.draw(planet);

    surface.drawTo(window);
    ship.drawTo(window);

    if(showCollisionModel)
    {
        window.draw(sim.getCollisionOverlay());
    }

    hud.drawTo(window);
}
