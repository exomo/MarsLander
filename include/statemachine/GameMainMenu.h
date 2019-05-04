#ifndef GAMEMAINMENU_H
#define GAMEMAINMENU_H

#include <graphics/Spaceship.h>
#include <statemachine/GameState.h>

namespace ExomoMarsLander
{

    class GameMainMenu : public GameState
    {
    public:
        /** Default constructor */
        GameMainMenu();
        /** Default destructor */
        virtual ~GameMainMenu();

        void handleEvent(const sf::Event& event) override;
        GameStatePtr updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState) override;
        void render(sf::RenderWindow& window) override;
    protected:
    private:
        /* Resourcen für Grafik und Text */
        const sf::Font& textFont;
        sf::RectangleShape backgroundShape;

        Spaceship ship;

        sf::Time lastUpdateTime;

        double offsetX;
        double offsetY;

        bool exitRequested = false;
        bool startRequested = false;
    };

}
#endif // GAMEMAINMENU_H
