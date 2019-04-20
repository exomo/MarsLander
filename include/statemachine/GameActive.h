#ifndef GAMEACTIVE_H
#define GAMEACTIVE_H

#include <graphics/CoordinateTransformation.h>
#include <statemachine/GameState.h>
#include <GlobalResources.h>
#include <simulation/Simulation.h>
#include <graphics/Spaceship.h>
#include <graphics/Surface.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ExomoMarsLander
{

    /*
     * Zustand in dem das Spiel läuft. Hier läuft das eigentliche Spiel.
     */
    class GameActive : public GameState
    {
    public:
        /** Default constructor */
        GameActive();
        /** Default destructor */
        virtual ~GameActive();

        void handleEvent(const sf::Event& event) override;
        GameStatePtr updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState) override;
        void render(sf::RenderWindow& window) override;
    protected:
    private:
        void InitializeLevel();

        /* Referenz auf den Resourcen Manager */
        const GlobalResources& globalResources;

        /* Zeitpunkt (vergangene Zeit seit Spielstart), an dem die Schlange das letzte mal einen Schritt bewegt wurde. */
        sf::Time lastMoveTime = sf::Time::Zero;

        Spaceship ship;
        Surface surface;
        SpaceSimulation sim;
        CoordinateTransformation transformation;

        /* Resourcen für Grafik und Text */
        const sf::Font& textFont;

        bool pauseRequested = false;
        bool paused = true;
        
        int score = 0;
        int levelScore = 0;
    };

}


#endif // GAMEACTIVE_H
