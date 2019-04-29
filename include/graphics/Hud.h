#ifndef HUD_H
#define HUD_H

#include <GlobalResources.h>
#include <graphics/CoordinateTransformation.h>
#include <simulation/ShipCollisionModel.h>

#include <SFML/Graphics.hpp>

namespace ExomoMarsLander
{
    /**
     * Statusanzeige
     * */
    class Hud
    {
        public:
            Hud();

            /** Initialisiere das HUD */
            void initialize();

            /** Setze Höhe des Raumschiffs über dem 0 Level */
            void setAltitude(double altitude);

            /** Setze Füllstand des Tanks (in %) */
            void setFuel(double fuel);

            /** Zeichne das HUD auf das Zeichenfenster */
            void drawTo(sf::RenderTarget& target);

        private:
            /* Referenz auf den Resourcen Manager */
            const GlobalResources& globalResources;

            /* Resourcen für Grafik und Text */
            const sf::Font& textFont;

            sf::Text altitudeText;
            sf::Text fuelText;
            sf::RectangleShape fuelBorder;
            sf::RectangleShape fuelLevelShape;

            double altitude;
            double fuelLevel;
    };
}

#endif //HUD_H